#include "xx_uv.h"
#include "xx_helpers.h"
#include "pkg\PKG_class.h"
#include "db\DB_sqlite.h"
#include <mutex>
#include <thread>

struct Peer;
struct Service;
struct Listener;
struct TaskManager;
struct Dispacher;

/******************************************************************************/

struct Peer : xx::UVServerPeer
{
	Service* service;

	Peer(Listener* listener, Service* service);
	virtual void OnReceivePackage(xx::BBuffer & bb) override;
	virtual void OnDisconnect() override;
};

struct Listener : xx::UVListener
{
	Service* service;

	Listener(xx::UV* uv, int port, int backlog, Service* service);
	virtual xx::UVServerPeer * OnCreatePeer() override;
};

struct TaskManager : xx::Object
{
	Service* service;
	Dispacher* dispacher = nullptr;
	std::mutex tasksMutex;
	std::mutex resultsMutex;
	xx::Queue_v<std::function<void()>> tasks;
	xx::Queue_v<std::function<void()>> results;
	void AddTask(std::function<void()>&& f);
	void AddTask(std::function<void()> const& f);
	void AddResult(std::function<void()>&& f);
	void AddResult(std::function<void()> const& f);

	TaskManager(Service* service);
	~TaskManager();
	volatile bool running = true;
	volatile bool stoped = false;
	void ThreadProcess();
};
using TaskManager_v = xx::Dock<TaskManager>;

struct Service : xx::Object
{
	xx::MemPool sqlmp;		// 给 SQLite 及其工作线程使用的 mp
	xx::SQLite_v sqldb;		// SQLite 走独立的内存池, 和主线程的分离

	xx::UV_v uv;
	Listener* listener = nullptr;
	TaskManager_v tm;

	Service();
	int Run();
};

struct Dispacher : xx::UVAsync
{
	TaskManager* tm;

	Dispacher(xx::UV* uv, TaskManager* tm);
	virtual void OnFire() override;
};


/******************************************************************************/

Listener::Listener(xx::UV* uv, int port, int backlog, Service* service)
	: xx::UVListener(uv, port, backlog)
	, service(service)
{
}

xx::UVServerPeer* Listener::OnCreatePeer()
{
	return mempool().Create<Peer>(this, service);
}


/******************************************************************************/


Dispacher::Dispacher(xx::UV* uv, TaskManager* tm)
	: xx::UVAsync(uv)
	, tm(tm)
{
}

void Dispacher::OnFire()
{
	while (!tm->results->Empty())
	{
		tm->results->Top()();
		tm->results->Pop();
	}
}

/******************************************************************************/

TaskManager::TaskManager(Service* service)
	: service(service)
	, tasks(mempool())
	, results(mempool())
{
	this->dispacher = service->uv->CreateAsync<Dispacher>(this);
	if (!this->dispacher) throw nullptr;
	std::thread t([this] { ThreadProcess(); });
	t.detach();
}

TaskManager::~TaskManager()
{
	running = false;
	while (!stoped) Sleep(1);
}

void TaskManager::AddTask(std::function<void()>&& f)
{
	std::lock_guard<std::mutex> lock(tasksMutex);
	tasks->Push(std::move(f));
}

void TaskManager::AddTask(std::function<void()> const& f)
{
	std::lock_guard<std::mutex> lock(tasksMutex);
	tasks->Push(std::move(f));
}

void TaskManager::AddResult(std::function<void()>&& f)
{
	{
		std::lock_guard<std::mutex> lock(resultsMutex);
		results->Push(std::move(f));
	}
	dispacher->Fire();
}

void TaskManager::AddResult(std::function<void()> const& f)
{
	{
		std::lock_guard<std::mutex> lock(resultsMutex);
		results->Push(std::move(f));
	}
	dispacher->Fire();
}

void TaskManager::ThreadProcess()
{
	std::function<void()> func;
	while (running)
	{
		bool gotFunc = false;
		{
			std::lock_guard<std::mutex> lock(tasksMutex);
			gotFunc = tasks->TryPop(func);
		}
		if (gotFunc) func();
		else Sleep(1);
	}
	stoped = true;
}

/******************************************************************************/

Service::Service()
	: sqldb(sqlmp, "data.db")
	, uv(mempool())
	, tm(mempool(), this)
{
	sqldb->Attach("log", "log.db");
	sqldb->SetPragmaJournalMode(xx::SQLiteJournalModes::WAL);
	sqldb->SetPragmaForeignKeys(true);
}

int Service::Run()
{
	// todo: 检查 db 看是不是新建的, 是就执行建表脚本

	listener = uv->CreateListener<Listener>(12345, 128, this);
	if (!listener) return -1;
	uv->Run();
	return 0;
}

/******************************************************************************/

Peer::Peer(Listener* listener, Service* service)
	: xx::UVServerPeer(listener)
	, service(service)
{
}

void Peer::OnDisconnect() {}

void Peer::OnReceivePackage(xx::BBuffer& bb)
{
	// todo: 收到包, 解析, 向任务容器压函数, 转到后台线程执行
	// SQLite 走独立的内存池, 和主线程的分离

	// 内存分配 & 回收流程( 基于 SQLite 只占 1 线, 使用 自己的 mp 的情况 ): 
	// 1. uv线程 用 uvmp 分配 SQL线程 需要的数据, 后将处理函数压入 tasks
	// 2. SQL线程 执行期间, 用 sqlmp 分配供 uv线程 处理结果所需数据, 后将处理函数压入 results
	// 3. uv线程 读取结果数据并处理, 回收 第1步分配的内存, 后将 第2步的内存回收函数压入 tasks
	// 4. tasks 执行第2步分配的内存回收

	service->tm->AddTask([service = this->service, peer = xx::Ref<Peer>(this)/*, args*/]	// 转到 SQL 线程
	{
		// 执行 SQL 语句, 得到结果
		DB::SQLiteManageFuncs fs(*service->sqldb);
	// auto rtv = fs.execxxxxx( args... )

	service->tm->AddResult([service, peer/*, args, rtv */]	// 转到 uv 线程
	{
		// args->Release();
		// handle( rtv )
		if (peer && peer->state == xx::UVPeerStates::Connected)	// 如果 peer 还活着, 做一些回发功能
		{
			//mp->SendPackages
		}
		// service->tm->AddTask([rtv]{ rtv->Release(); })	// 转到 SQL 线程
	});
	});
}

/******************************************************************************/



// 测试结果, UV_THREADPOOL_SIZE=1 的情况下, 每秒能执行 100 万次

struct MyUV : xx::UV
{
	MyUV() : UV() 
	{
		Cout("MyUV()\n");
	}
	~MyUV()
	{
		Cout("~MyUV()\n");
	}
};

struct Worker : xx::UVWorker
{
	int i1 = 0, i2 = 0;
	Worker(xx::UV* uv) : UVWorker(uv)
	{
		Cout("Worker()\n");
	}
	~Worker() 
	{
		Cout("~Worker()\n");
	}
	virtual void OnWork() override
	{
		Cout("OnWork before sleep\n");
		++i1;
		Sleep(2000000);
		Cout("OnWork sleeped\n");
	}
	virtual void OnAfterWork(int status) override
	{
		Cout("OnAfterWork\n");
		++i2;
		if (i2 < 10000000) Start();
	}
};

struct Timer : xx::UVTimer
{
	Worker& w;
	Timer(xx::UV* uv, Worker& w) : UVTimer(uv), w(w)
	{
		Start(1000, 1000);
	}
	virtual void OnFire() override
	{
		Cout("i1 = ", w.i1, ", i2 = ", w.i2, "\n");
		uv->Stop();
	}
};

int main()
{
	// todo: 用 Worker 改造上面的代码
	xx::MemPool mp;
	{
		xx::Dock<MyUV> uv(mp);
		auto w = uv->CreateWorker<Worker>();
		w->Start();
		auto t = uv->CreateTimer<Timer>(*w);
		uv->Run();
		mp.Cout("uv stoped.\n");
	}
	std::cin.get();
	return 0;
}











// todo: 收到包, 解析, 向任务容器压函数, 转到后台线程执行
// SQLite 走独立的内存池, 和主线程的分离

// 内存分配 & 回收流程( 基于 SQLite 只占 1 线, 使用 mempool 的情况 ): 
// 1. uv线程 分配 SQL线程 需要的数据, 后将处理函数压入 tasks
// 2. SQL线程 执行期间, 分配供 uv线程 处理结果所需数据, 后将处理函数压入 results
// 3. uv线程 读取结果数据, 回收 第1步分配的内存, 后将 第2步的内存回收函数压入 tasks
// 4. tasks 执行第2步分配的内存回收

// 上述流程的 多 work thread 的补充:
// 1. 做一个线程私有 tasks 队列及 mempool, 标记为 TLS
// 2. 上述流程第 2 步 记录私有 tasks 指针 并向下传递
// 3. 上述流程第 3 步 向 私有 tasks 压内存回收函数
// 4. 工作线程除了扫公共 tasks 以外, 还扫私有 tasks, 扫到就执行

// 这套方案的问题在于, 多线内存池会损耗比较大, 复用率低下. 


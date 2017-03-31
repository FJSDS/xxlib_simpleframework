struct Scene : MP
{
	// 上下文中用到的一个简易 udp 通讯库( 主用于向显示系统发送显示数据 )
	xx::MemHeaderBox<UdpClient> udp;

	// 帧控制相关
	static const int64_t msPerFrame = 1000 / 20;
	int64_t ticks = 0;
	xx::Size<float> mapSize = { 45.0f, 45.0f };			// 模拟一个地图大小
	
	// 整个 scene 用到的随机数发生器
	xx::Random_v rnd;

	// 对象容器区
	xx::List_v<xx::MPObject*> deadMonsters;		// 用于放技能过程中打死的怪的指针记录, 以便在正确的生命周期批量删
	xx::List_v<MonsterBase*> monsters;

	// 更新机制区
	int Update();				// call by Run
	int Run();

	// misc
	Scene();
	~Scene();

	/****************************************************************/
	// lua 附加区
	/****************************************************************/

	void LoadLuaFile(char const* fn);
	lua_State* L = nullptr;
	lua_State* co = nullptr;		// SceneManager 自己的脚本( 执行优先于 objs 之 Updates )
	xx::String_v err;

	// 以类名来创建怪类实例
	xx::MPtr<MonsterBase> CreateMonster(char const* classname);

	// for lua
	XY CreateXY(float x, float y);

	// 方便在 lua 中随机
	int NextInteger(int min, int max);
	double NextDouble(double min, double max);

	// 方便在 lua 中扫 monsters
	uint32_t Monsters_Count();
	xx::MPtr<MonsterBase> Monsters_At(uint32_t index);
};

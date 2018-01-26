﻿#include "xx_uv.h"

class Service : public xx::Object
{
public:
	xx::UvLoop& loop;
	explicit Service(xx::MemPool* mp, xx::UvLoop& loop)
		: Object(mp)
		, loop(loop)
	{
	}
	void Run()
	{
		loop.Run();
	}
};

int main()
{
	xx::MemPool mp;
	xx::UvLoop loop(&mp);
	auto service = mp.Create<Service>(loop);
	service->Run();
	return 0;
}

#include "play.h"
#include <cstdio>


play::play()
{
	std::printf("start\n");
	start();
	int size = _v.size();
	int cap = _v.capacity();
	std::printf("%d\n", size);
	std::printf("%d\n", cap);
}


play::~play()
{
}


void play::print()
{
	std::printf("start\n");
	int size = _v.size();
	int cap = _v.capacity();
	std::printf("%d\n", size);
	std::printf("%d\n", cap);
	for (int i = 0; i < _v.size(); i++)
	{
		printf("%d", _v[i]);
	}
}

void play::start()
{
	for (int i = 0; i < _v.capacity(); i++)
	{
		_v.push_back(0);
	}
}

void play::change_v()
{
	_v[0] = 2;
}
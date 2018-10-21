#pragma once
#include <vector>
class play
{
public:
	play();
	~play();
	void change_v();
	void print();
	void start();
private:
	std::vector<int> _v;
};


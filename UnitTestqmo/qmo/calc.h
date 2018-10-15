#pragma once
#include <vector>

class calculator
{
public:
	calculator();
	~calculator();
	float accrate();
	float accrate(float);
	float begining();
	float data_i(int);
	float* data_all();
	float ds(float x_min, float x_plu, float x_old, float x_new);
	float expE();
	float expE2();
	float h_evol();
	void loop(int n_times);
	bool metropolis(float ds, float rnd);
	int next(float rnd);
	float rnd();
	int size();
	float x_evol(float x, float rnd);

private:
	float _accrate;
	float _acpt_rt;
	float _h;
	float _m;
	const int _N = 5;
	float* _path;
	float _w;
};

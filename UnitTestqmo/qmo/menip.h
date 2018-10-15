#pragma once

class menipulator
{
public:
	menipulator();
	~menipulator();
	float accrate();
	float accrate(float);
	float begining();
	float ds(float x_min, float x_plu, float x_old, float x_new);
	float expE(float x, int i);
	float expE2(float x, int i);
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
	int _N = 5;
	float _w;
	float _sum;
};

#pragma once

class path_
{
public:
	path_();
	~path_();
	float* path();
	float* path(float*);
	int size();
	void metropolis();
	int next();
	float rnd();
	float calc_h();
	float calc_x();
	float calc_accrate();
	float calc_delta_s();
	float calc_mean();
	float calc_mean2();
	void thermolise();
	void loop();
	float* data();
	float* _data;

	int len(float* list)
	{
		int len = sizeof(list) / sizeof(list);
		return len;
	}

	int len(int* list)
	{
		int len = sizeof(list) / sizeof(list);
		return len;
	}

private:
	int _i;
	const int _N = 5;
	float* _path;
	float _prob;
	float* _probs;
	float _h;
	float _accrate;
	float _idrate;
	float _m;
	float _w;
	float _ds;
	float _x_old;
	float _x_new;
	float _x_plu;
	float _x_min;
	float _rnd;
};
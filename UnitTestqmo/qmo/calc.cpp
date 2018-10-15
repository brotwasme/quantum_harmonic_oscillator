#include "calc.h"
#include <cmath>
#include <ctime>
#include <vector>

calculator::calculator()
{
	int time;
	if (false)
	{
		//time = (int)std::ctime;
	}
	else
	{
		time = 0;
	}
	srand(time);
	_accrate = 0;
	_acpt_rt = (float) 0.8;
	_h = 1;
	_m = 1;
	_w = 1;
	std::vector<float> _path(_N, 0);
}

calculator::~calculator()
{
}

float calculator::accrate()
{
	_accrate += (1 / ((float)_N));
	return _accrate;
}

float calculator::accrate(float accrate)
{
	_accrate = accrate;
	return _accrate;
}

float calculator::begining()
{
	for (int i = 0; i < _N; i++)
	{
		_path[i] = (float) 0;
	}
	return 0;
}

float calculator::ds(float x_m, float x_p, float x_o, float x_n)
{
	float ds = (float) 0.5*_m*(x_n*(_w*_w*x_n + 2 * (x_n - x_p - x_m)
		- x_o * (_w*_w*x_o + 2 * (x_o - x_p - x_m))));
	return ds;
}

float calculator::data_i(int i)
{
	return _path[i];
}
float* calculator::data_all()
{
	return _path;
}

float calculator::expE()
{
	float mean;
	float sum = 0;
	for (int i = 0; i < _N; i++)
	{
		sum += _path[i];
	}
	mean = sum / (float)_N;
	return mean;
}

float calculator::expE2()
{
	float mean2;
	float sum2 = 0;
	for (int i = 0; i < _N; i++)
	{
		sum2 += _path[i] * _path[i];
	}
	mean2 = sum2 / (float)_N;
	return mean2;
}

float calculator::h_evol()
{
	_h = (_h*_accrate) / _acpt_rt;
	return _h;
}

void calculator::loop(int n_times)
{
	float rnd_n;
	int t;
	int t_min;
	int t_plu;
	float x_old;
	float x_min;
	float x_plu;
	float x_new;
	float ds_;
	for (int i = 0; i < _N; i++)
	{
		rnd_n = rnd();
		t = next(rnd_n);
		t_min = (t + _N - 1) % _N;
		t_plu = (t + 1) % _N;
		rnd_n = rnd();
		x_old = _path[t];
		x_new = x_evol(x_old, rnd_n);
		x_min = _path[t_min];
		x_plu = _path[t_plu];
		ds_ = ds(x_min, x_plu, x_old, x_new);
		rnd_n = rnd();
		bool check = metropolis(ds_, rnd_n);
		if (check)
		{
			_path[t] = x_new;
		}
	}
	h_evol();
}

bool calculator::metropolis(float ds, float rnd)
{
	bool keep_x = true;
	if (ds < 0)
	{
		float comp = 0.5;
		float prob = exp(-ds);
		if (comp > prob)
		{
			keep_x = false;
			accrate();
		}
	}
	return keep_x;
}

int calculator::next(float rnd)
{
	int next = (int)rnd * _N;
	return next;
}

float calculator::rnd()
{
	float rnd = (float)rand() / (RAND_MAX + 1);
	return rnd;
}

int calculator::size()
{
	return _N;
}

float calculator::x_evol(float x, float rnd)
{
	float x_new = (float)(x + _h * (rnd - 0.5));
	return x_new;
}

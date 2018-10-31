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
	_acpt_rt = (double) 0.8;
	_h = 1;
	_m = 1;
	_w = 1;
	std::vector<double> _path(_N, 0);
}

calculator::~calculator()
{
}

double calculator::accrate()
{
	_accrate += (1 / ((double)_N));
	return _accrate;
}

double calculator::accrate(double accrate)
{
	_accrate = accrate;
	return _accrate;
}

double calculator::begining()
{
	for (int i = 0; i < _N; i++)
	{
		_path[i] = (double) 0;
	}
	return 0;
}

double calculator::ds(double x_m, double x_p, double x_o, double x_n)
{
	double ds = (double) 0.5*_m*(x_n*(_w*_w*x_n + 2 * (x_n - x_p - x_m)
		- x_o * (_w*_w*x_o + 2 * (x_o - x_p - x_m))));
	return ds;
}

double calculator::data_i(int i)
{
	return _path[i];
}
double* calculator::data_all()
{
	return _path;
}

double calculator::expE()
{
	double mean;
	double sum = 0;
	for (int i = 0; i < _N; i++)
	{
		sum += _path[i];
	}
	mean = sum / (double)_N;
	return mean;
}

double calculator::expE2()
{
	double mean2;
	double sum2 = 0;
	for (int i = 0; i < _N; i++)
	{
		sum2 += _path[i] * _path[i];
	}
	mean2 = sum2 / (double)_N;
	return mean2;
}

double calculator::h_evol()
{
	_h = (_h*_accrate) / _acpt_rt;
	return _h;
}

void calculator::loop(int n_times)
{
	double rnd_n;
	int t;
	int t_min;
	int t_plu;
	double x_old;
	double x_min;
	double x_plu;
	double x_new;
	double ds_;
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

bool calculator::metropolis(double ds, double rnd)
{
	bool keep_x = true;
	if (ds < 0)
	{
		double comp = 0.5;
		double prob = exp(-ds);
		if (comp > prob)
		{
			keep_x = false;
			accrate();
		}
	}
	return keep_x;
}

int calculator::next(double rnd)
{
	int next = (int)rnd * _N;
	return next;
}

double calculator::rnd()
{
	double rnd = (double)rand() / (RAND_MAX + 1);
	return rnd;
}

int calculator::size()
{
	return _N;
}

double calculator::x_evol(double x, double rnd)
{
	double x_new = (double)(x + _h * (rnd - 0.5));
	return x_new;
}

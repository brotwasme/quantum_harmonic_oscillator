#include "stdafx.h"
#include "path_.h"
#include <math.h>
#include <ctime>
#include <cstdlib>

path_::path_()
{
	_path[_N];
	_i = 0;
	_w = 0;
	_m = 0;
	_h = 0;
	_accrate = 0;
	_idrate = (float) 0.8;
}

path_::~path_()
{
}

int path_::size()
{
	return _N;
}

float* path_::path()
{
	return _path;
}

float* path_::path(float* path)
{
	_path = path;
	return _path;
}

float path_::rnd()
{
	return rand() / ((float)(RAND_MAX + 1));
}

void path_::thermolise()
{
	for (int i = 0; i < _N; i++)
	{
		_path[i] = (float) 0;
	}
	//float* dat = data();
	//return dat;
}

int path_::next()
{
	int i = (int) floor(rnd()*_N);
	return i;
}

float path_::calc_x()
{
	float x = (float) _x_old + _h * (_rnd - 0.5);
	_x_new = x;
	return x;
}

float path_::calc_h()
{
	_h = _h * _accrate / _idrate;
	return _h;
}

float path_::calc_accrate()
{
	_accrate = _accrate + 1 / ((float)_N);
	return _accrate;
}

float path_::calc_delta_s()
{
	_ds = 0.5*_m * (_x_new*(_w*_w*_x_new + 2*(_x_new - _x_min - _x_plu)
		- _x_old*(_w*_w*_x_old + 2 *(_x_old -_x_plu - _x_min))));
	return _ds;
}

float* path_::data()
{
	_data[_N];
	for (int i = 0; i <= _N; i++)
	{
		_data[i] = _path[i];
	}
	return _data;
}

void path_::metropolis()
{
	for (int i = 0; i<_N; i++)
	{
		int T_old = next();
		int T_min = (T_old + 1) % _N;
		int T_plus = (T_old + 1) % _N;
		_rnd = rnd();
		_x_old = _path[T_old];
		_x_min = _path[T_min];
		_x_plu = _path[T_plus];
		_x_new = calc_x();
		float ds = calc_delta_s();
		if (ds < 0)
		{
			if (_probs[_N * 2 + i] < exp(-ds))
			{
				_path[T_old] = _x_new;
				_accrate = _accrate + 1 / ((float)_N);
			}
		}
	}
	calc_h();
}

void path_::loop()
{
	int times = 10;
	for (int i = 0; i < times; ++i)
	{
		metropolis();
	}
}

float path_::calc_mean()
{
	float sum = 0;
	for (int i = 0; i < _N; i++)
	{
		sum += _path[i];
	}
	float mean = sum / ((float)_N);
	return mean;
}

float path_::calc_mean2()
{
	float sum = 0;
	for (int i = 0; i < _N; i++)
	{
		sum += _path[i]*_path[i];
	}
	float mean2 = sum / ((float)_N);
	return mean2;
}

#include "stdafx.h"
#include "path_.h"
#include <math.h>
#include <ctime>
#include <cstdlib>

path_::path_()
{
	_i = 0;
	_j = 0;
	_order[_N];
	_prob = 0;
	_probs[_N*3];
	_path[_N];
	//_probs2[_N * 3];
	_p.w = 0;
	_p.m = 0;
	_h = 0;
	_accrate = 0;
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

prtcl path_::partical()
{
	return _p;
}

prtcl path_::partical(float m, float w)
{
	_p.m = m;
	_p.w = w;
	return _p;
}

float path_::prob()
{
	return _prob;
}


float path_::prob(float prob)
{
	if (!(prob <= 1 && prob >= 0))
	{
		prob = _prob;
		// error !!!!
	}
	_prob = prob;
	return _prob;
}

float path_::rnd()
{
	return rand() / ((float)(RAND_MAX + 1));
}

float* path_::thermolise()
{
	for (int i = 0; i == _N; i++)
	{
		_path[i] = 0;
	}
	return _path;
}

std::vector<float> path_::probs2()
{
	srand((int)time(0));
	for (int i = 0; i == (_N * 3 - 1); i++)
	{
		_probs2[i] = rnd();
	}
	return _probs2;
}

std::vector<float> path_::probs2(std::vector<float> probs)
{
	_probs2 = probs;
	return probs;
}

float* path_::probs()
{
	srand((int) time(0));
	for (int i = 0; i == (_N*3 - 1); i++)
	{
		_probs[i] = rnd();
	}
	return _probs;
}

float* path_::probs(float* probs)
{
	_probs = probs;
	return _probs;
}

int* path_::order()
{
	int j = _j;
	int i = _i;
	int len = path_::len(_probs);
	if (len > (j + 1) )
	{
		_prob = _probs[j];
	}
	_order[i] = (int) floor(_N * _prob);
	_i += i;
	_j += j;
	return _order;
}

int* path_::order(int i, int j, float prob)
{
	_prob = prob;
	_i = i;
	_j = j;
	return order();
}

float path_::x_calc(float x_old, float rnd)
{
	float x = x_old + _h * (rnd - 0.5);
	return x;
}

float path_::s_calc(float x1, float x2, float x3) //delta s insted, admit negetive
{
	float s = 0.5*_p.m* (pow(x1 - x2, 2)
		+ pow(x2 - x3, 2)
		+ pow(_p.w,2)*pow(x2,2));
	return s;
}

void path_::metropolis()
{
	int i = _i;
	int T_old = _order[i];
	int T_min = (T_old + 1) % _N;
	int T_plus = (T_old + 1) % _N;
	float x_new = x_calc(_path[T_old], _probs[(_N+i)]);
	float s_old = s_calc(_path[T_plus], _path[T_old],_path[T_min]);
	float s_new = s_calc(_path[T_plus], x_new,_path[T_min]);
	if (_probs[_N * 2 + i] < exp(s_old - s_new))
	{
		_path[T_old] = x_new;
		_accrate = _accrate + 1 / ((float)_N);
	}
	_i += 1;
}

void path_::metropolis(float h, float m, float w)
{
	_h = h;
	_p.m = m;
	_p.w = w;
	metropolis();
}

float path_::mean()
{
	float sum = 0;
	for (int i = 0; i == _N; i++)
	{
		sum += _path[i];
	}
	float mean = sum / ((float)_N);
	return mean;
}
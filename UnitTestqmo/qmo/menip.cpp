#include "menip.h"
#include <cmath>
#include <vector>
#include <time.h>
#include <iostream>

menipulator::menipulator()
{
	int time_;
	if (true)
	{
		time_ = time(NULL);
	}
	else
	{
		time_ = 0;
	}
	srand(time_);
	_accrate = 0;
	_acpt_rt = (float) 0.8;
	_h = 1;
	_m = 0.1;
	_w = 0.1;
}

menipulator::~menipulator()
{
}

void menipulator::accepted()
{
	_accepted += 1;
}

float menipulator::accepted_rate(int n_times)
{
	return (float)_accepted/(float)n_times;
}

float menipulator::accrate()
{
	_accrate += (1 / ((float) _N));
	return _accrate;
}

std::vector<float> menipulator::begining(std::vector<float> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		path[i] = (float) 0;
	}
	return path;
}

float menipulator::ds(float x_m, float x_p, float x_o, float x_n)
{
	float ds = (float) 0.5*_m*(x_n*(_w*_w*x_n + 2 * (x_n - x_p - x_m)
		- x_o * (_w*_w*x_o + 2 * (x_o - x_p - x_m))));
	return ds;
}

float menipulator::Ex(std::vector<float> path)
{
	float sum_ = sum(path);
	int N = path.size();
	return Ex(sum_, N);
}

float menipulator::Ex(float sumx, int N)
{
	return sumx / N;
}

float menipulator::Ex2(float sumsum, int N)
{
	return sumsum / N;
}

float menipulator::Ex2(std::vector<float> path)
{
	int N =  path.size();
	path = xx(path);
	float sumxx = sum(path);

	return Ex2(sumxx, N);
}

float menipulator::h_evol()
{
	_h = (_h*_accrate) / _acpt_rt;
	return _h;
}

float menipulator::jack_knife(std::vector<float> path, int B)
{
	path = jack_knife_edit(path, B);
	float sum_ = sum(path);
	std::vector<float> estm = jack_knife_estim(path, B, sum_);
	float mean = Ex(path);
	float var = jack_knife_var(estm, B, path.size(), mean);
	return sqrt(var);
}

std::vector<float> menipulator::jack_knife_edit(std::vector<float> path, int B)
{
	int N = path.size();
	int rem = N % B;
	if (rem != 0) {
		path.erase(path.begin(), path.begin() + rem);
	}
	return path;
}

std::vector<float> menipulator::jack_knife_estim(std::vector<float> path, int B, float sum)
{
	int N = path.size();
	std::vector<float> estemator(N/B, 0);
	float elim;
	for (int i = 0; i < N / B; i++)
	{
		elim = 0;
		for (int j = 0; j < i*B +B; j++)
		{
			elim += path[j];
		}
		estemator[i] = (sum - elim)/(N-B);
	}
	return estemator;
}

float menipulator::jack_knife_var(std::vector<float> estim, int B, int N, float mean)
{
	float var = 0;
	for (int i = 0; i < N / B; i++)
	{
		float x = (estim[i] - mean);
		var += x * x*(N / B - 1) / (N - B);
	}
	return var;
}

std::vector<float> menipulator::loop(std::vector<float> path, int n_times)
{
	_accepted = 0;
	float rnd_n;
	int t;
	int t_min;
	int t_plu;
	float x_old;
	float x_min;
	float x_plu;
	float x_new;
	float ds_;
	_N = path.size();
	for (int j = 0; j < n_times; j++)
	{
		for (int i = 0; i < _N; i++)
		{
			rnd_n = rnd();
			t = next(rnd_n);
			//printf("%d", t);
			t_min = (t + _N - 1) % _N;
			t_plu = (t + 1) % _N;
			rnd_n = rnd();
			x_old = path[t];
			x_new = x_evol(x_old, rnd_n);
			x_min = path[t_min];
			x_plu = path[t_plu];
			ds_ = ds(x_min, x_plu, x_old, x_new);
			rnd_n = rnd();
			bool keep_x = metropolis(ds_, rnd_n);
			if (!keep_x)
			{
				path[t] = x_new; // <- change here
			}
		}
		h_evol();
	}
	return path;
}

bool menipulator::metropolis(float ds, float rnd)
{
	bool keep_x = true;
	if (ds > 0)
	{
		float comp = rnd;
		double prob = exp(-ds);
		if (comp < prob)
		{
			keep_x = false;
			accrate();
			accepted();
		}
	}
	return keep_x;
}

int menipulator::next(float rnd)
{
	int next = (int)floor(rnd * (float)_N);
	//printf("  %d  ", next);
	return next;
}

float menipulator::rnd()
{
	float rnd = (float)rand() / ((float) (RAND_MAX + 1));
	//printf("  %f  ", rnd);
	return rnd;
}

float menipulator::sigma2(std::vector<float> v)
{
	float E_x = Ex(v);
	return sigma2(v, E_x);
}

float menipulator::sigma2(std::vector<float> v, float mean)
{
	float val;
	float E_x = mean;
	float sum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		val = v[i] - E_x;
		sum += val * val;
	}
	float sig2 = sum / (v.size() - 1);
	return sig2;
}

float menipulator::sum(std::vector<float> x)
{
	float sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		sum += x[i];
	}
	return sum;
}

void menipulator::test()
{
	test_Ex();
	test_Ex2();
	test_h_evol();
	test_rnd();
	test_x_evol();
}

void menipulator::test_Ex()
{
	float mean = 0;
	std::vector<float> v = { 1,2,3,4,5 };
	try
	{
		float mean = Ex(v);
		printf("mean %f %s\n", mean, mean == 15 / 5 ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

void menipulator::test_Ex2()
{
	float mean = 0;
	std::vector<float> v = { 1,2,3,4,5 };
	try
	{
		float mean = Ex2(v);
		printf("x^2 mean %f %s\n", mean, mean == (1 + 4 + 9 + 16 + 25) / 5 ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

void menipulator::test_rnd()
{
	const int N = 3;
	srand(1);
	int result = 0;
	for (int i = 0; i < N; i++)
	{
		float rn = rnd();
		result += (0 <= rn && 1 >= rn);
	}
	printf("%d rnd %s\n", result, result == 3 ? "true" : "false");
}

void menipulator::test_x_evol()
{
	_h = 1;
	float x = x_evol(1, 1);
	printf("%d  x_evo %s\n", x, x == 1 ? "true": "false");
}

void menipulator::test_h_evol()
{
	_accrate = 1;
	_acpt_rt = 0.8;
	float h = h_evol();
	printf("%d h evol %s \n", h, (h == 1.0 / 0.8) ? "true" : "false");
}

std::vector<float> menipulator::to_vector(float * array, int N)
{
	std::vector<float> v(N);
	for (int i = 0; i < N; i++)
	{
		v[i] = array[i];
	}
	return v;
}

float menipulator::to_array(std::vector<float> v, int i)
{
	return v[i];
}

float menipulator::x_evol(float x, float rnd)
{
	float x_new = (float)(x - _h * 2*(rnd - 0.5));
	return x_new;
}

std::vector<float> menipulator::xx(std::vector<float> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		float  x = path[i];
		path[i] = x * x;
	}
	return path;
}

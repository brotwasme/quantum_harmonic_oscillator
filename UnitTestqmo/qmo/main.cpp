#include "menip.h"
#include "calc.h"

int main()
{/*
	calculator cal;
	float p = cal.begining();
	cal.loop(1);
	int N = cal.size();
	float* data_;
	data_ = new float[N];
	for (int i = 0; i < N; i++)
	{
		data_[i] = cal.data_i(i);
	}
	data_;
	*/
	menipulator menip;
	int N = menip.size();
	float *path;
	float rnd_n;
	int t;
	int t_min;
	int t_plu;
	float x_old;
	float x_min;
	float x_plu;
	float x_new;
	float ds_;
	for (int i = 0; i < N; i++)
	{

	}
	for (int i = 0; i < N; i++)
	{
		rnd_n = menip.rnd();
		t = menip.next(rnd_n);
		t_min = (t + N - 1) % N;
		t_plu = (t + 1) % N;
		rnd_n = menip.rnd();
		x_old = path[t];
		x_new = menip.x_evol(x_old, rnd_n);
		x_min = path[t_min];
		x_plu = path[t_plu];
		ds_ = menip.ds(x_min, x_plu, x_old, x_new);
		rnd_n = menip.rnd();
		bool check = menip.metropolis(ds_, rnd_n);
		if (check)
		{
			path[t] = x_new;
		}
	}
	menip.h_evol();
	return 0;
}

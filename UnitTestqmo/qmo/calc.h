#pragma once
#include <vector>

class calculator
{
public:
	calculator();
	~calculator();
	double accrate();
	double accrate(double);
	double begining();
	double data_i(int);
	double* data_all();
	double ds(double x_min, double x_plu, double x_old, double x_new);
	double expE();
	double expE2();
	double h_evol();
	void loop(int n_times);
	bool metropolis(double ds, double rnd);
	int next(double rnd);
	double rnd();
	int size();
	double x_evol(double x, double rnd);

private:
	double _accrate;
	double _acpt_rt;
	double _h;
	double _m;
	const int _N = 5;
	double* _path;
	double _w;
};

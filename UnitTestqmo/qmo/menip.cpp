#include "menip.h"
#include <cmath>
#include <vector>
#include <time.h>
#include <iostream>
#include <fstream>

menipulator::menipulator()
{
	_no_chance_accepted = 0;
	_accepted = 0;
	_accrate = 0;
	_acpt_rt = (double) 0.5;
	_h = _acpt_rt;
	_m = 1;
	_w = 1;
}

menipulator::~menipulator()
{
}

void menipulator::accepted()
{
	_accepted += 1;
}

double menipulator::accepted_rate()
{
	return (double)_accepted/((double) _no_chance_accepted);
}

double menipulator::accrate()
{
	_accrate += ((double) 1 / (_N));
	return _accrate;
}

std::vector<double> menipulator::begining(std::vector<double> path, double mw)
{
	_m = mw;
	_w = mw;
	for (int i = 0; i < path.size(); i++)
	{
		path[i] = (double) 0;
	}
	return path;
}

std::vector<double> menipulator::corralation(std::vector<double> cor, std::vector<double> path)
{
	double mean;
	for (int i = 0; i < path.size(); i++)
	{
		mean = 0;
		for (int j = 0; j < path.size(); j++)
		{
			mean += path[j] * path[j+((j - i) % path.size())]/(double)path.size();
		}
		cor[i] += mean;
	}

	return std::vector<double>();
}



double menipulator::ds(double x_m, double x_p, double x_o, double x_n)
{
	double ds = (double) 0.5*_m*(x_n*(_w*_w*x_n + 2 * (x_n - x_p - x_m)
		- x_o * (_w*_w*x_o + 2 * (x_o - x_p - x_m))));
	return ds;
}

double menipulator::ds_comp(double x_min, double x_plu, double x_old, double x_new)
{
	double s_o = pow(x_plu - x_old,2) + pow(x_old - x_min,2)+ pow(_w*x_old, 2);
	double s_n = pow(x_plu - x_new, 2) + pow(x_new - x_min,2)+pow(_w*x_new, 2);
	//printf("o: %f, n: %f", s_o*_m/2, s_n*_m/2);
	double ds = 0.5*_m*(s_n - s_o);
	return ds;
}

double menipulator::Ex(std::vector<double> path)
{
	double sum_ = sum(path);
	int N = path.size();
	return Ex(sum_, N);
}

double menipulator::Ex(double sumx, int N)
{
	return sumx / N;
}

double menipulator::Ex(std::vector<double> path, int pow)
{
	double sum = 0;
	for (int i = 0; i < path.size(); i++)
	{
		sum += std::pow(path[i], pow);
	}
	//if (sum < 0 && pow % 2 == 0)
	//{
	//	printf("negetive %f with power %d", sum, pow);
	//}
	return  sum/ ((double) path.size());
}

double menipulator::Ex2(double sumsum, int N)
{
	return sumsum / N;
}

double menipulator::Ex2(std::vector<double> path)
{
	int N =  path.size();
	path = xx(path);
	double sumxx = sum(path);

	return Ex2(sumxx, N);
}

void menipulator::file(std::string file_d, std::string file_x, double path_size, double N_configs, double drops_per, double n)
{
	file(file_d, path_size, N_configs, drops_per);
	file(file_x, path_size, N_configs, drops_per, n);
}

void menipulator::file(std::string file_x, double path_size, double N_configs, double drops_per, double n)
{
	std::ofstream myfile_x;
	myfile_x.open(file_x);
	myfile_x << path_size << ' ' << N_configs << ' ' << drops_per << ' ' << _m << ' ' << n << ' ';// << std::endl;
	myfile_x.close();
}

void menipulator::file(std::string file_d, double path_size, double N_configs, double drops_per)
{
	std::ofstream myfile_d;
	myfile_d.open(file_d);
	myfile_d << path_size << ' ' << N_configs << ' ' << drops_per << ' ' << _m << ' ';// << std::endl;
	myfile_d.close();
}

void menipulator::file(std::string file_d, std::string file_x, std::vector<double> path, double Ex, double Ex2, double Ex3, double Ex4)
{
	std::ofstream myfile_d;
	myfile_d.open(file_d, std::ios_base::app);
	for (int i = 0; i < path.size(); i++)
	{
		myfile_d << path[i] << ' ';
	}
	myfile_d.close();
	std::ofstream myfile_x;
	myfile_x.open(file_x, std::ios_base::app);
	myfile_x << Ex << ' ' << Ex2 << ' ' << Ex3 << ' ' << Ex4 << ' ';// << std::endl;
	myfile_x.close();
}
void menipulator::file( std::string file_x, std::vector<double> path, std::vector<double> Exn)
{
	std::ofstream myfile_x;
	myfile_x.open(file_x, std::ios_base::app);
	for (int i = 0; i < Exn.size(); i++)
	{
		myfile_x << Exn[i] << ' ';
		//if ((i + 1) % 2 == 0 && Exn[i] < 0)
		//{
		//	printf("negative %f pow %d", Exn[i], i + 1);
		//}
	}
	myfile_x.close();
}


std::vector<double> menipulator::full(const int path_len, std::string file_name_d, std::string file_name_x, double drop_per, double N_configs, double m, double acpt_rt)
{
	_acpt_rt = acpt_rt;
	std::vector<double> path(path_len);
	rn_set();
	path = begining(path, m);
	double Ex_, Ex2_, Ex3_, Ex4_;
	int pow_;
	file(file_name_d, file_name_x, path.size(), N_configs, drop_per, 4);
	for (int i = 0; i < N_configs; i++)
	{
		pow_ = 1;
		path = loop(path, drop_per);
		Ex_ = Ex(path, pow_);
		pow_ = 2;
		Ex2_ = Ex(path, pow_);
		pow_ = 3;
		Ex3_ = Ex(path, pow_);
		pow_ = 4;
		Ex4_ = Ex(path, pow_);
		file(file_name_d, file_name_x, path, Ex_, Ex2_, Ex3_, Ex4_);
	}
	return path;
}
std::vector<double> menipulator::full(const int path_len, std::string file_name_x, double drop_per, double N_configs, double m, double acpt_rt)
{
	const int n = 4;
	_acpt_rt = acpt_rt;
	std::vector<double> path(path_len);
	std::vector<double> Exn(n);
	rn_set();
	path = begining(path, m);
	file(file_name_x, path.size(), N_configs, drop_per, n);
	for (int i = 0; i < N_configs; i++)
	{
		path = loop(path, drop_per);
		for (int j = 0; j < n; j++)
		{
			Exn[j] = Ex(path, j+1);
		}
		file(file_name_x, path, Exn);
	}
	return path;
}


double menipulator::h_evol()
{
	_h = (_h*_accrate) / _acpt_rt;
	return _h;
}

double menipulator::jack_knife(std::vector<double> path, int B)
{
	path = jack_knife_edit(path, B);
	double sum_ = sum(path);
	std::vector<double> estm = jack_knife_estim(path, B, sum_);
	double mean = Ex(path);
	double var = jack_knife_var(estm, B, path.size(), mean);
	return sqrt(var);
}

std::vector<double> menipulator::jack_knife_edit(std::vector<double> path, int B)
{
	int N = path.size();
	int rem = N % B;
	if (rem != 0) {
		path.erase(path.begin(), path.begin() + rem);
	}
	return path;
}

std::vector<double> menipulator::jack_knife_estim(std::vector<double> path, int B, double sum)
{
	int N = path.size();
	std::vector<double> estemator(N/B, 0);
	double elim;
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

double menipulator::jack_knife_var(std::vector<double> estim, int B, int N, double mean)
{
	double var = 0;
	for (int i = 0; i < N / B; i++)
	{
		double x = (estim[i] - mean);
		var += x * x*(N / B - 1) / (N - B);
	}
	return var;
}

std::vector<double> menipulator::loop(std::vector<double> path, int n_times)
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
	_N = path.size();
	for (int j = 0; j < n_times; j++)
	{
		_accrate = 0;
		for (int i = 0; i < _N; i++)
		{
			rnd_n = rnd();
			t = next(rnd_n);
			//printf("%f", rnd_n);
			//printf("%d", t);
			t_min = (t + _N - 1) % _N;
			t_plu = (t + 1) % _N;
			rnd_n = rnd();
			//printf("%f", rnd_n);
			x_old = path[t];
			x_new = x_evol(x_old, rnd_n);
			x_min = path[t_min];
			x_plu = path[t_plu];
			ds_ = ds_comp(x_min, x_plu, x_old, x_new);
			rnd_n = rnd();
			bool keep_x = metropolis(ds_, rnd_n);
			//printf("%f: %d\n", ds_, keep_x);
			_no_chance_accepted += 1;
			//printf("%f\n", rnd_n);
			//printf("h:%f - x new:%f -accrate:%f - keep x:%d\n", _h, x_new, _accrate, keep_x);
			if (!keep_x)
			{
				path[t] = x_new; // <- change here
				accrate();
				accepted();
			}
		}
		//printf("%f", _accrate);
		h_evol();
	}
	return path;
}

bool menipulator::metropolis(double ds, double rnd)
{
	double prob = ds;
	bool keep_x = false;
	if (ds > 0)
	{
		prob = exp(-ds);
		if (rnd > prob)
		{
			keep_x = true;
		}
	}
	return keep_x;
}

int menipulator::next(double rnd)
{
	int next = (int)floor(rnd * (double)_N);
	//printf("  %d  ", next);
	return next;
}

double menipulator::rnd()
{
	double rnd = (double)rand() / ((double)(RAND_MAX + 1.0));
	//printf("  %f  ", rnd);
	return rnd;
}

void menipulator::rn_set()
{
	int time_;
	if (false)
	{
		time_ = time(NULL);
	}
	else
	{
		time_ = 0;
	}
	srand(time_);
}

double menipulator::sigma2(std::vector<double> v)
{
	double E_x = Ex(v);
	return sigma2(v, E_x);
}

double menipulator::sigma2(std::vector<double> v, double mean)
{
	double val;
	double E_x = mean;
	double sum = 0;
	for (int i = 0; i < v.size(); i++)
	{
		val = v[i] - E_x;
		sum += val * val;
	}
	double sig2 = sum / (v.size() - 1);
	return sig2;
}

double menipulator::sum(std::vector<double> x)
{
	double sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		sum += x[i];
	}
	return sum;
}

void menipulator::test()
{
	test_ds();
	test_Ex();
	test_Ex2();
	test_h_evol();
	test_loop();
	test_metropolis();
	test_rnd();
	test_x_evol();
}

void menipulator::test_ds()
{
	try
	{
		_m = 1;
		_w = 1;
		double ds_a;
		ds_a = ds(-2, 5, -1, 6);
		//printf("ds %f %s\n", ds_a, ds_a == 31.5 ? "true" : "false");
		double ds_b = ds_comp(-2, 5, -1, 6);
		//printf("ds %f %s\n", ds_b, ds_a == 31.5 ? "true" : "false");
		//printf("ds %f %f %s\n", ds_a, ds_b, ds_a == ds_b ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		printf("\n\n\n\n\nhelloe\n\n\n\n");
	}

}

void menipulator::test_Ex()
{
	double mean = 0;
	std::vector<double> v = { -1,2,-3,4,-5 };
	try
	{
		mean = Ex(v, 1);
		double thing = -(double)3 / 5;
		printf("mean %f %f %s\n", mean, thing, mean <= (-(double)3 / 5) +0.05 && mean >= (-(float)3 / 5) - 0.05 ? "true" : "false");
		mean = Ex(v, 2);
		printf("mean %f %s\n", mean, mean <= (double)55 / 5 + 0.05 && mean >= (double)55 / 5 - 0.05 ? "true" : "false");
		mean = Ex(v, 3);
		printf("mean %f %s\n", mean, mean <= -(double)81 / 5 + 0.05 && mean >= -(double)81 / 5 - 0.05 ? "true" : "false");
		mean = Ex(v, 4);
		printf("mean %f %s\n", mean,  mean <= (double)979/ 5 +0.05 && mean >= (double)979 / 5 - 0.05 ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

void menipulator::test_Ex2()
{
	double mean = 0;
	std::vector<double> v = { 1,2,3,4,5 };
	try
	{
		double mean = Ex2(v);
		printf("x^2 mean^2 %f %s\n", mean, mean == (1 + 4 + 9 + 16 + 25) / 5 ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

}

void menipulator::test_loop()
{
	try
	{
		_h = 1;
		_m = 1;
		_w = 1;
		std::vector<double> v(5, 0);
		std::vector<double> v2 = loop(v, 5);
		int res = 0;
		int comp = 5;
		for (int i = 0; i < v.size(); i++)
		{
			res += v[i] == v2[2];
			printf("%f loop %f \n", v[i], v2[i]);
		}
		printf("%d test loop %s \n", res, (res < comp) ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

void menipulator::test_h_evol()
{
	try
	{
	_h = 1;
	_accrate = 1;
	_acpt_rt = 0.8;
	double h = h_evol();
	double comp = 1.0 / 0.8;
	printf("%f h evol %s \n", h, (h == comp) ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

void menipulator::test_metropolis()
{
	try
	{
	bool keep_x = metropolis(1, 0.5);
	bool comp = true;
	printf("%d metropolis %s \n", keep_x, (keep_x == comp) ? "true" : "false");
	keep_x = metropolis(-1, 0.5);
	comp = false;
	printf("%d metropolis %s \n", keep_x, (keep_x == comp) ? "true" : "false");
	keep_x = metropolis(1, 0.0);
	comp = false;
	printf("%d metropolis %s \n", keep_x, (keep_x == comp) ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

void menipulator::test_rnd()
{	try
	{
	const int N = 5000;
	srand(1);
	int result = 0;
	std::vector<double> avrg(N,1);
	double Ex_ = Ex(avrg);
	for (int i = 0; i < N; i++)
	{
		double rn = rnd();
		result += (0 <= rn && 1 >= rn);
		avrg[1] = rnd();
		//printf("%f rnd\n", rn);
	}
	printf("E(x) = %f\n", Ex_);
	printf("%d rnd %s, \n", result, result == N ? "true" : "false");
	Ex_ = Ex(avrg);
	printf("E(x) = %f\n", Ex_);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}


void menipulator::test_x_evol()
{
	try
	{
	_h = 1;
	double x = x_evol(2, 0.5);
	double comp = 2;
	printf("%f  x_evo %s\n", x, x == comp ? "true" : "false");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}

double menipulator::to_array(std::vector<double> v, int i)
{
	return v[i];
}


std::vector<double> menipulator::to_vector(double * array, int N)
{
	std::vector<double> v(N);
	for (int i = 0; i < N; i++)
	{
		v[i] = array[i];
	}
	return v;
}

double menipulator::x_evol(double x, double rnd)
{
	double x_new = (double)(x - _h * (rnd - 0.5));
	return x_new;
}

std::vector<double> menipulator::xx(std::vector<double> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		double  x = path[i];
		path[i] = x * x;
	}
	return path;
}

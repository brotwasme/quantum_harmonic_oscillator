#pragma once
#include <vector>

class menipulator
{
public:
	menipulator();
	~menipulator();
	void accepted();
	double accepted_rate();
	double accrate();
	std::vector<double> begining(std::vector<double>,double mw);
	double ds(double x_min, double x_plu, double x_old, double x_new);
	double ds_comp(double x_min, double x_plu, double x_old, double x_new);
	double Ex(std::vector<double> path);
	double Ex(double sumx, int N);
	double Ex2(double sumxx, int N);
	double Ex2(std::vector<double> path);
	double h_evol();
	double jack_knife(std::vector<double> path, int B);
	std::vector<double> jack_knife_edit(std::vector<double> path, int B);
	std::vector<double> jack_knife_estim(std::vector<double> path, int B, double sum);
	double jack_knife_var(std::vector<double> path, int B, int N, double mean);
	std::vector<double> loop(std::vector<double> path, int n_times);
	bool metropolis(double ds, double rnd);
	int next(double rnd);
	double rnd();
	void rn_set();
	double sigma2(std::vector<double> v);
	double sigma2(std::vector<double> v, double mean);
	double sum(std::vector<double> x);
	void test();
	void test_ds();
	void test_Ex();
	void test_Ex2();
	void test_loop();
	void test_rnd();
	void test_h_evol();
	void test_x_evol();
	void test_metropolis();
	double to_array(std::vector<double> v, int i);
	std::vector<double> to_vector(double * array, int N);
	double x_evol(double x, double rnd);
	std::vector<double> xx(std::vector<double> path);
	

private:
	int _accepted;
	int _no_chance_accepted;
	double _accrate;
	double _acpt_rt;
	double _h;
	double _m;
	int _N;
	double _sum;
	double _w;
};

#pragma once
#include <vector>

class menipulator
{
public:
	menipulator();
	~menipulator();
	void accepted();
	float accepted_rate(int n_times);
	float accrate();
	std::vector<float> begining(std::vector<float>);
	float ds(float x_min, float x_plu, float x_old, float x_new);
	float Ex(std::vector<float> path);
	float Ex(float sumx, int N);
	float Ex2(float sumxx, int N);
	float Ex2(std::vector<float> path);
	float h_evol();
	float jack_knife(std::vector<float> path, int B);
	std::vector<float> jack_knife_edit(std::vector<float> path, int B);
	std::vector<float> jack_knife_estim(std::vector<float> path, int B, float sum);
	float jack_knife_var(std::vector<float> path, int B, int N, float mean);
	std::vector<float> loop(std::vector<float> path, int n_times);
	bool metropolis(float ds, float rnd);
	int next(float rnd);
	float rnd();
	float sigma2(std::vector<float> v);
	float sigma2(std::vector<float> v, float mean);
	float sum(std::vector<float> x);
	void test();
	void test_Ex();
	void test_Ex2();
	void test_rnd();
	void test_h_evol();
	void test_x_evol();
	float to_array(std::vector<float> v, int i);
	std::vector<float> to_vector(float * array, int N);
	float x_evol(float x, float rnd);
	std::vector<float> xx(std::vector<float> path);
	

private:
	int _accepted;
	float _accrate;
	float _acpt_rt;
	float _h;
	float _m;
	int _N;
	float _sum;
	float _w;
};

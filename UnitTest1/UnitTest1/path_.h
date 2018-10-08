#pragma once
#include <vector>
struct prtcl
{
	float m;
	float w;
};

class path_
{
public:
	path_();
	~path_();
	float* path();
	float* path(float*);
	int size();
	float prob();
	float prob(float);
	// float* problem();
	// float* problem(float*);
	void metropolis();
	void metropolis(float, float, float);
	int* order();
	int* order(int, int, float);
	float* probs();
	float* probs(float*);
	std::vector<float> probs2();
	std::vector<float> probs2(std::vector<float>);
	prtcl partical();
	prtcl partical( float, float);
	float rnd();
	float x_calc(float, float);
	float s_calc(float, float, float);
	float mean();
	float* thermolise();

	int len(float* list)
	{
		int len = sizeof(list) / sizeof(list);
		return len;
	}
	int len(int* list)
	{
		int len = sizeof(list) / sizeof(list);
		return len;
	}

private:
	const int _N = 5;
	float* _path;
	float _prob;
	std::vector<float> _probs2;
	float* _probs;
	int* _order;
	int _i;
	int _j;
	float _h;
	float _accrate;
	prtcl _p;
};
#include "menip.h"
//#include "calc.h"
//#include "play.h"
#include <vector>

void p_v(std::vector<float> v)
{
	printf("vector: [");
	for (int i = 0; i < v.size()-1; i++)
	{
		printf("%f, ", v[i]);
	}
	printf("%f] \n", v[v.size()-1]);
}
int main()
{/**/
	int size = 100;
	int times = 500;
	std::vector<float> path(size);
	std::vector<float> path2(size);
	menipulator men;
	path = men.begining(path);
	path = men.loop(path, times);
	p_v(path);
	float x = men.Ex(path);
	float x2 = men.Ex2(path);
	printf("\nx: %f \nx^2: %f", x, x2);
	float rate = men.accepted_rate(size*times);
	printf("\naccept rate: %f \n", rate);
	float error_jacked = men.jack_knife(path, 10);
	printf("jacked error %f\n", error_jacked);
	path2 = men.xx(path);
		/*
	menipulator men;
	men.test();*/
	return 0;
}

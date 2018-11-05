#include "menip.h"
//#include "calc.h"
//#include "play.h"
#include <vector>

void p_v(std::vector<double> v)
{
	printf("vector: [");
	for (int i = 0; i < (int) v.size()-1; i++)
	{
		printf("%f, ", v[i]);
	}
	printf("%f] \n", v[v.size()-1]);
}
int main()
{/*
	double mw = 0.5;
	int size = 51;
	int times = 100;
	int drop = 100;
	double rate = 0.8;
	const int len = 100;
	std::vector<double> xs(len, 0);
	std::vector<double> x2s(len, 0);

	std::vector<double> path(size);
	menipulator men;
	men.rn_set();
	path = men.begining(path, mw);

	path = men.loop(path, 1);
	path = men.loop(path, 50);
	for (int i = 0; i < 100; i++) {
		path = men.loop(path, drop);
	}
	p_v(path);
	for (int i = 0; i<len; i++)
	{
		path = men.loop(path, drop);
		xs[i] = men.Ex(path);
		x2s[i] = men.Ex2(path);
		//printf("%f, %f\n", x, x2);
	}
	printf("xs: ");
	p_v(xs);
	printf("\nx2s: ");
	p_v(x2s);
	printf("\n");
	rate = men.accepted_rate();
	printf("\naccept rate: %f \n", rate);
	double errorx_jacked = men.jack_knife(xs, 10);
	double errorx2_jacked = men.jack_knife(x2s, 10);
	printf("jacked x error %f\n", errorx_jacked);
	printf("jacked x ^2 error %f\n", errorx2_jacked);
	double mean_x = men.Ex(xs);
	double mean_x2 = men.Ex(x2s);
	printf("mean: %f, mean sqr: %f", mean_x, mean_x2);
	*/
	menipulator men;
	double mw = 0.1;
	double acpt = 0.5;
	int Nconfigs = 1200;
	int drop = 120;
	double rate = 0.8;
	const int len = 1200;
	std::string file_name_x = "xn.txt";
	std::string file_name_d = "data.txt";
	std::vector<double> path(len, 0);
	men.full(len, file_name_d, file_name_x, drop, Nconfigs, mw, acpt);
	/*
	menipulator men;
	men.test();  */
	return 0;
}

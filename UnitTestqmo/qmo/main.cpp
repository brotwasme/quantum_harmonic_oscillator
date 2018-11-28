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
{
	if (false)
	{
		double mw = 0.2;
		int size = 600;
		int drop = 100;
		double rate = 0.5;
		const int len = 500;
		std::vector<double> xs(len, 0);
		std::vector<double> x2s(len, 0);

		std::vector<double> path(size);
		menipulator men;
		men.rn_set();
		path = men.begining(path, mw);
		double x22s;
		path = men.loop(path, 1);
		path = men.loop(path, 50);
		for (int i = 0; i < 100; i++) {
			path = men.loop(path, drop);
		}
		p_v(path);
		for (int i = 0; i < len; i++)
		{
			path = men.loop(path, drop);
			xs[i] = men.Ex(path);
			x2s[i] = men.Ex2(path);
			x22s = men.Ex(path, 2);
			if (x22s != x2s[i])
			{
				printf("fail %f, %f\n", x22s, x2s[i]);
			}
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
	}
	if (true)
	{
		menipulator men;
		double mw = 0.3;
		double acpt = 0.6;
		int Nconfigs = 10000;
		int drop = 20;
		const int len = 400;
		std::string file_name_x = "xn_20400.txt";
		std::string file_name_d = "data_20400.txt";
		std::vector<double> path(len, 0);
		path = men.full(len, file_name_d, file_name_x, drop, Nconfigs, mw, acpt);
		//path = men.full(len, file_name_x, drop, Nconfigs, mw, acpt);
		printf("done");
	}
	if (false)
	{
		menipulator men;
		men.test();
	}
	return 0;
}

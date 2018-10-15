#include "stdafx.h"
#include "CppUnitTest.h"
#include "path_.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD_INITIALIZE(methodName)
		{
			path_ first;
			first.thermolise();
			_len = first.size();
			_len_probs = first.len(_probs);
			_mean = first.calc_mean();
			_mean2 = first.calc_mean2();
			_rnd1 = first.rnd();
			_rnd2 = first.rnd();
			_rnd3 = first.rnd();
			_x = first.calc_x();
			_s = first.calc_delta_s();
			_ds = first.calc_delta_s();
			//_order = first.order();

		}
		TEST_METHOD(Test_)
		{
			// TODO: Your test code here
			//printf("int %d", _index);
			//Assert::IsTrue(_index >= 0 && _index <= _len);
		}
		TEST_METHOD(Test_rnd)
		{
			Assert::IsTrue(_rnd1 >= 0 && _rnd1 <= 1);
			Assert::IsTrue(_rnd2 >= 0 && _rnd2 <= 1);
			Assert::IsTrue(_rnd3 >= 0 && _rnd3 <= 1);
			Assert::IsTrue(_rnd1 != _rnd2 ||
				_rnd1 != _rnd3 ||
				_rnd2 != _rnd3);
		}

		TEST_METHOD(Test_thermolise)
		{
			int num = 1;
			int test_tot = 0;
			for (int i = 0; i < _len; i++)
			{
				num = 1;
				if (_beginging[i] == 0) {
					num = 0;
				}
				test_tot += num;
			}
			Assert::AreEqual(test_tot, 0);
		}
		TEST_METHOD(Test_mean)
		{
			Assert::AreEqual(_mean, (float)0);
		}

		TEST_METHOD(Test_mean2)
		{
			Assert::AreEqual(_mean2, (float)0);
		}

		TEST_METHOD(Test_x_calc)
		{
			Assert::AreEqual((float)1, _x);
		}

		TEST_METHOD(Test_s_calc)
		{
			Assert::AreEqual((float)0, _s);
		}

		TEST_METHOD(Test_delta_s_calc)
		{
			Assert::AreEqual((float)0, _ds);
		}

	private:
		int* _order;
		int _len;
		float* _beginging;
		float* _probs;
		float _mean;
		float _mean2;
		float _rnd1;
		float _rnd2;
		float _rnd3;
		float _x;
		float _s;
		float _ds;
		int _len_probs;
	};
}
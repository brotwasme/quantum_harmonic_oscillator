#include "stdafx.h"
#include "CppUnitTest.h"
#include "../qmo/menip.h"
#include <vector>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_CLASS_INITIALIZE(test_qmo)
		{
			menipulator men;
			double _rnd1 = men.rnd();
			double _rnd2 = men.rnd();
			double _rnd3 = men.rnd();
		}

		TEST_METHOD(TestMethod1)
		{
			Assert::AreNotEqual(_rnd1, _rnd2);
			Assert::AreNotEqual(_rnd2, _rnd3);
			Assert::AreNotEqual(_rnd1, _rnd3);
		}

	private:
		double _rnd1;
		double _rnd2;
		double _rnd3;
	};
}

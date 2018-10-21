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
			float _rnd1 = men.rnd();
			float _rnd2 = men.rnd();
			float _rnd3 = men.rnd();
		}

		TEST_METHOD(TestMethod1)
		{
			Assert::AreNotEqual(_rnd1, _rnd2);
			Assert::AreNotEqual(_rnd2, _rnd3);
			Assert::AreNotEqual(_rnd1, _rnd3);
		}

	private:
		float _rnd1;
		float _rnd2;
		float _rnd3;
	};
}

#include "stdafx.h"
#include "CppUnitTest.h"
#include "../qmo/calc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_CLASS_INITIALIZE(test_qmo)
		{
			calculator cal;
		}

		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
		}

	};
}

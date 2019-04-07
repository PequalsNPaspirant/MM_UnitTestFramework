//Goal
//Solve puzzles using dynamic programming

#include <iostream>
#include <array>
#include <vector>
using namespace std;

#include "MM_UnitTestFramework/MM_UnitTestFramework.h"

namespace mm {

	//This is a tag defined to group the test cases
	//All the test cases tagged with this flag are executed only if this flag is defined as true
	MM_DEFINE_FLAG(false, MM_UnitTestFramework_Testing)

	MM_UNIT_TEST(MM_UnitTestFramework_testcase_1, MM_UnitTestFramework_Testing)
	{
		//Test Unit Test Framework functions here
		int v1 = 10, v2 = 10, v3 = 15;
		string separator("\n      ===>");
		__PRINT_VARIABLES_AND_VALUES__4(separator, v1 == v2 && v2 != v3, v1, v2, v3)
	}

	MM_UNIT_TEST(MM_UnitTestFramework_testcase_2_success, MM_UnitTestFramework_Testing)
	{
		int amount1 = 10, amount2 = 15, amount3 = 30;
		MM_EXPECT_TRUE(amount1 <= amount2 && (2 * amount2) == amount3, amount1, amount2, amount3)
	}

	MM_UNIT_TEST(MM_UnitTestFramework_testcase_2_failure, MM_UnitTestFramework_Testing)
	{
		int amount1 = 10, amount2 = 15, amount3 = 30;
		MM_EXPECT_TRUE(amount1 <= amount2 && (5 * amount2) == amount3, amount1, amount2, amount3)
	}

/*
Output:

Executing unit tests...

==> MM_UNIT_TEST_RESULT : FAILED | Test Name: mm::MM_UnitTestFramework_testcase_1
	Validation Statement: amount1 <= amount2 && amount2 == (2 * amount3)
	Variables: amount1, amount2, amount3
	Values   : 10, 15, 20

Execution of unit tests is finished. All tests have passed unless any failure printed above!

*/
	
}

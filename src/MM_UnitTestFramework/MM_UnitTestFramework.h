//Goal
//Implement binary search

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

namespace mm {

// If you want to redirect the output to any other output destination (such as file)
// OR if you want to print something fancy (like printing Ok in green and FAILED in 
// red on screen), overwrite macro MM_COUT
#define MM_COUT std::cout

//---- Macro version 1 ---

// This macro can be called as:
//__PRINT_VARIABLES_AND_VALUES__1(amount1 == amount2 && amount2 != amount3, "%d %d %d", amount1, amount2, amount3)

#define __PRINT_VARIABLES_AND_VALUES__1(validationStatement, formatString, ...) \
	MM_COUT << "\n    Validation Statement: " << string(#validationStatement); \
	MM_COUT << "\n    Values: "; \
	printf(formatString, ##__VA_ARGS__);

//---- Macro version 2 ---
/*
This macro can be called as:
__PRINT_VARIABLES_AND_VALUES__2(amount1 == amount2 && amount2 != amount3, amount1, amount2, amount3)

Output:
Validation Statement: amount1 == amount2 && amount2 != amount3
Variables: amount1, amount2, amount3
Values   : 2, 2, 2,
*/

	template <class T>
	void printInitializerList(std::initializer_list<T> list)
	{
		for (auto elem : list)
			MM_COUT << elem << ", ";
	}

#define __PRINT_VARIABLES_AND_VALUES__2(validationStatement, ...) \
	MM_COUT << "\n    Validation Statement: " << string(#validationStatement); \
	MM_COUT << "\n    Variables: " << string(#__VA_ARGS__); \
	MM_COUT << "\n    Values   : "; \
	printInitializerList({##__VA_ARGS__});

//---- Macro version 3 ---

/*
This macro can be called as:
__PRINT_VARIABLES_AND_VALUES__(amount1 == amount2 && amount2 != amount3, amount1, amount2, amount3)

Output:
Validation Statement: amount1 == amount2 && amount2 != amount3
Variables: amount1, amount2, amount3
Values   : 2, 2, 2
*/

	// recursive variadic function
	template<typename... ZeroOrManyTypes>
	void printDifferentTypesOfVariables(ZeroOrManyTypes... args)  // Handle zero variables
	{
	}

	template <typename ExactlyOneType>
	void printDifferentTypesOfVariables(ExactlyOneType t)  // Handle exactly one variables
	{
		MM_COUT << t;
	}

	template<typename FirstType, typename... RestTypes>
	void printDifferentTypesOfVariables(FirstType t, RestTypes... args)  // used when at least one variable is provided
	{
		printDifferentTypesOfVariables(t);
		MM_COUT << ", ";
		printDifferentTypesOfVariables(args...);
	}

#define __PRINT_VARIABLES_AND_VALUES__3(validationStatement, ...) \
	MM_COUT << "\n    Validation Statement: " << string(#validationStatement); \
	if(string(#__VA_ARGS__) != "") \
	{ \
		MM_COUT << "\n    Variables: " << string(#__VA_ARGS__); \
		cout << std::boolalpha; \
		MM_COUT << "\n    Values   : "; \
		mm::printDifferentTypesOfVariables(##__VA_ARGS__); \
		MM_COUT << "\n"; \
	}

//---- Macro version 4 ---	
/*
This macro can be called as:
__PRINT_VARIABLES_AND_VALUES__(amount1 == amount2 && amount2 != amount3, amount1, amount2, amount3)

Output:

*/
#define MM_PRINT_TEST_CASE_NUMBER(boolFlag) printTestCaseNumber<void>(boolFlag);

	template<typename Type>
	bool printTestCaseNumber(bool boolFlag = true)
	{
		static bool printTestCaseNumberValue = boolFlag;
		return printTestCaseNumberValue;
	}

#define MM_SET_PAUSE_ON_ERROR(boolFlag) mm::pauseOnError<void>(boolFlag == false ? 1 : 2);

	template<typename Type>
	bool pauseOnError(int id = 0)
	{
		static bool pauseOnErrorValue = true;
		if (id == 1)
			pauseOnErrorValue = false;
		else if (id == 2)
			pauseOnErrorValue = true;
		return pauseOnErrorValue;
	}

	// recursive variadic function
	template<typename... ZeroOrManyTypes>
	void printDifferentTypesOfVariables(size_t width, string str, ZeroOrManyTypes... args)  // Handle zero variables
	{
	}

	template <typename ExactlyOneType>
	void printDifferentTypesOfVariables(size_t width, string str, ExactlyOneType t)  // Handle exactly one variables
	{
		MM_COUT << std::setw(width) << str << " : " << t;
	}

	template<typename FirstType, typename... RestTypes>
	void printDifferentTypesOfVariables(size_t width, string str, FirstType t, RestTypes... args)  // used when at least one variable is provided
	{
		int firstCommaPosition = str.find_first_of(',');
		printDifferentTypesOfVariables(width, str.substr(0, firstCommaPosition), t);
		MM_COUT << "\n";
		printDifferentTypesOfVariables(width, str.substr(firstCommaPosition + 1, string::npos), args...);
	}

#define __PRINT_VARIABLES_AND_VALUES__4(validationStatement, ...) \
	MM_COUT << "\n     Validation Statement : " << string(#validationStatement); \
	string variables = string(#__VA_ARGS__); \
	if (!variables.empty()) \
	{ \
		size_t width = 0; \
		size_t initialSpacing = 5; \
		size_t prevPos = 0; \
		size_t nextPos = 0; \
		while ((nextPos = variables.find(',', prevPos + 1)) != string::npos) \
		{ \
			if (width < (nextPos - prevPos + 1)) width = nextPos - prevPos + 1; \
			prevPos = nextPos; \
		} \
		width += initialSpacing; \
		MM_COUT << "\n" << std::setw(width) << "Variables" << " : Values\n"; \
		cout << std::boolalpha; \
		mm::printDifferentTypesOfVariables(width, variables, ##__VA_ARGS__); \
		MM_COUT << "\n"; \
	}

//---- END of Macro versions ---

	typedef void(*__testCaseFunPtr__)();

	//----------------- Global container to store unit test function pointers ----------------------
	template<typename dataType>
	std::vector<__testCaseFunPtr__>& getGlobalTestCasesVector()
	{
		static std::vector<__testCaseFunPtr__> globalTestCases;
		return globalTestCases;
	}

	template<typename dataType>
	dataType& getTestCaseCounter()
	{
		static dataType counter = 0;
		return counter;
	}

#define __MM_DECLARE_FUNCTION__(testcase) void testcase();
#define __MM_ADD_TEST_CASE__(testcase) mm::getGlobalTestCasesVector<void>().push_back(testcase);

#define __MM_EXPECT_TRUE_PRINT__(printSuccess, printFailure, printResults, validationStatement, ...) \
	{ \
		int lineNumber = __LINE__; \
		string fileName = __FILE__; \
		if(printTestCaseNumber<void>()) \
			MM_COUT << "\rExecuting test case no. : " << ++getTestCaseCounter<size_t>(); \
		bool __mm_unit_test_result__ = validationStatement; \
		string resultStr("FAILED"); \
		if (__mm_unit_test_result__ == true) \
		{ \
			resultStr = "OK"; \
		} \
		if((__mm_unit_test_result__ && printSuccess) || (!__mm_unit_test_result__ && printFailure)) \
		{ \
			MM_COUT << "\n===> MM_UNIT_TEST_RESULT : " << resultStr << " | Test Name: " << string(__FUNCTION__); \
			MM_COUT << "\n     File: " << fileName.substr(fileName.find_last_of('\\') + 1, string::npos) << " Line: " << lineNumber; \
			if(!__mm_unit_test_result__ || printResults) \
			{ \
				__PRINT_VARIABLES_AND_VALUES__4(validationStatement, ##__VA_ARGS__) \
				if(!__mm_unit_test_result__ && pauseOnError<void>()) \
				{ \
					MM_COUT << "\nPress any key to continue..."; \
					cin.get(); \
				} \
			} \
		} \
	}

#define MM_EXPECT_TRUE(validationStatement, ...) __MM_EXPECT_TRUE_PRINT__(false, true, false, validationStatement, ##__VA_ARGS__)
#define MM_EXPECT_TRUE_PRINT(printSuccess, printFailure, printResults, validationStatement, ...) __MM_EXPECT_TRUE_PRINT__(printSuccess, printFailure, printResults, validationStatement, ##__VA_ARGS__)

#define __MM_EXPECT_EQUAL_PRINT__(printSuccess, printFailure, printResults, expected, actual) \
	{ \
		auto tempExpected = expected; \
		auto tempActual = actual; \
		bool __mm_unit_test_result__ = false; \
		string resultStr("FAILED"); \
		if (tempExpected == tempActual) \
		{ \
			__mm_unit_test_result__ = true; \
			resultStr = "OK"; \
		} \
		if((__mm_unit_test_result__ && printSuccess) || (!__mm_unit_test_result__ && printFailure)) \
		{ \
			MM_COUT << "\n===> MM_UNIT_TEST_RESULT : "; \
			MM_COUT << resultStr; \
			MM_COUT << " | Test Name: " << string(__FUNCTION__); \
			if(!__mm_unit_test_result__ || printResults) \
			{ \
				MM_COUT << "\n  ----Expected value: " << tempExpected; \
				MM_COUT << "\n  ------Actual value: " << tempActual; \
			} \
		} \
	}

// Obsolete Macro. Use MM_EXPECT_TRUE instead.
#define MM_EXPECT_EQUAL(expected, actual) __MM_EXPECT_EQUAL_PRINT__(false, true, false, expected, actual)
#define MM_EXPECT_EQUAL_PRINT(printSuccess, printFailure, printResults, expected, actual) __MM_EXPECT_EQUAL_PRINT__(printSuccess, printFailure, printResults, expected, actual)

#define MM_DECLARE_FLAG(flagName) \
	bool mm_get_##flagName();

#define MM_DEFINE_FLAG(result, flagName) \
	bool mm_get_##flagName() \
	{ \
		return result; \
	}

#define __MM_UNIT_TEST__(functionName, flagName) \
	__MM_DECLARE_FUNCTION__(functionName) \
	class mm_class_##functionName \
	{ \
	public: \
		mm_class_##functionName() \
		{ \
			if(mm_get_##flagName()) \
				__MM_ADD_TEST_CASE__(functionName) \
		} \
	}; \
	mm_class_##functionName mm_global_object_##functionName; \
	void functionName()

	//----------------- this function is called from main() using the macro defined underline ----------------------
	template<typename dataType>
	void runTests()
	{
		MM_COUT << "\n\nExecuting unit tests...\n\n";
		size_t totalTests = getGlobalTestCasesVector<void>().size();
		size_t counter = 0;
		for (__testCaseFunPtr__ funptr : getGlobalTestCasesVector<void>())
		{
			//MM_COUT << "\rExecuting test " << ++counter << " of " << totalTests;
			(*funptr)();
		}
		MM_COUT << "\n\nExecution of unit tests is finished. All tests have passed unless any failure printed above!";
	}

#define MM_UNIT_TEST(functionName, flagName) \
	MM_DECLARE_FLAG(flagName) \
	__MM_UNIT_TEST__(functionName, flagName)

//#define MM_UNIT_TEST2(functionName, flagName, flagValue) \
//	MM_DEFINE_FLAG(flagValue, flagName) \
//	__MM_UNIT_TEST__(functionName, flagName)

#define MM_RUN_UNIT_TESTS mm::runTests<void>();

}

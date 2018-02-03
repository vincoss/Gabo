/*
*	MinUnit.h
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#ifndef MIN_UNIT_H_
#define MIN_UNIT_H_ 1

void MinUnitInitialize(void);
void UnitTestsRunAll();

#define MinUnitAssert(message, test) do { if (!(test)) return message; } while (0)
#define MinUnitRun(test) do { MinUnitInitialize(); char * message = test(); MinUnitTestsRun++;  if (message) { printf("%s\n", message); MinUnitTestsFail++; }else {MinUnitTestsSuccess++; }} while (0)

extern int MinUnitTestsRun;
extern int MinUnitTestsSuccess;
extern int MinUnitTestsFail;

/*
	EXAMPLE

	#include <stdio.h>
	#include "MinUnit.h"

	// These are required.
	int MinUnitTestsRun = 0;
	int MinUnitTestsSuccess = 0;
	int MinUnitTestsFail = 0;

	void MinUnitInitialize(void)
	{
		// Init here
	}

	static char * SampleTest()
	{
		MinUnitAssert("Error:, 1 + 1 = 2", (1 + 1) == 3);
		return 0;
	}

	static void RunAllTests()
	{
		MinUnitRun(SampleTest);
	}

	int UnitTestsMain()
	{
		RunAllTests();

		printf("Tests failed: %d, passed: %d, of tests: %d", MinUnitTestsFail, MinUnitTestsSuccess, MinUnitTestsRun);

		return MinUnitTestsRun - MinUnitTestsSuccess;
	}

*/

#endif
#include "UnitTests.h"
#include "MinUnit.h"

// These are required.
int MinUnitTestsRun = 0;
int MinUnitTestsSuccess = 0;
int MinUnitTestsFail = 0;

static char * SampleTest()
{
	MinUnitAssert("Error:, 1 + 1 = 2", (1 + 2) == 2);
	return 0;
}

static void UnitTestsRunAll()
{
	MinUnitRun(SampleTest);
}

int UnitTestsRun(void)
{
	UnitTestsRunAll();

	printf("Tests failed: %d, passed: %d, of tests: %d", MinUnitTestsFail, MinUnitTestsSuccess, MinUnitTestsRun);

	return MinUnitTestsRun - MinUnitTestsSuccess;
}
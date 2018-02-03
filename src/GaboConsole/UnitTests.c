/*
*	UnitTests.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#include "MinUnit.h"
#include "UnitTests.h"
#include "GaboCommand.h"
#include "GaboIo.h"

// These are required.
int MinUnitTestsRun = 0;
int MinUnitTestsSuccess = 0;
int MinUnitTestsFail = 0;

// Call form main.c
int UnitTestsRun(void)
{
	UnitTestsRunAll();

	printf("Tests failed: %d, passed: %d, of tests: %d", 1, 1, 1);

	return MinUnitTestsRun - MinUnitTestsSuccess;
}

// Initialize or reset values, called for each test
void MinUnitInitialize(void)
{
	data_count = 0;
	command_ready = 0;
	memset(data_in, 0, strlen(data_in));
}

char * GaboCommandReadReadyTest()
{
	command_ready = 1;

	char data[8] = "A=128";
	strcpy_s(data_in, 8, data);
	GaboCommandRead();
	MinUnitAssert("Error: GaboCommandReadReadyTest", powerCommand == 128);
	return 0;
}

char * GaboCommandReadNotReadyCommandTest()
{
	command_ready = 0;
	GaboCommandRead();
	MinUnitAssert("Error: GaboCommandReadNotReadyCommandTest", strlen(data_in) == 0);
	return 0;
}

char * GaboCommandParseTest()
{
	uint8_t result = GaboCommandParse("A=255", 0);
	MinUnitAssert("Error:, GaboCommandParseTest", result == 255);
	return 0;
}

char * GaboCommandParseDefaultTest()
{
	char *s = "";
	uint8_t result = GaboCommandParse(s, 0);
	MinUnitAssert("Error:, GaboCommandParseDefaultTest", result == 0);
	return 0;
}

char * GaboCommandCopyTest()
{
	char data[8] = "A=255\n";
	char command[8];

	GaboCommandCopy(data, command);
	
	MinUnitAssert("Error:, GaboCommandCopyTest data", strlen(data) == 0);
	MinUnitAssert("Error:, GaboCommandCopyTest command", strcmp("A=255\n", command) == 0);

	return 0;
}

char * GaboCommandCopyEmptyTest()
{
	char data[8] = "";
	char command[8] = "";

	GaboCommandCopy(data, command);

	MinUnitAssert("Error:, GaboCommandCopyEmptyTest", strlen(command) == 0);

	return 0;
}

char * GaboCommandReadUsartTest()
{
	GaboCommandReadUsart('A');

	MinUnitAssert("Error:, GaboCommandReadUsartTest data in", data_in[0] == 'A');
	MinUnitAssert("Error:, GabGaboCommandReadUsartTestoCommandCopyTest data count", data_count == 1);

	return 0;
}

char * GaboCommandReadUsartNewLineTest()
{
	GaboCommandReadUsart('A');
	GaboCommandReadUsart('B');
	GaboCommandReadUsart('\n');

	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", data_in[1] == 'B');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data count", data_count == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest command ready", command_ready == 1);

	return 0;
}

// Register all tests in here
void UnitTestsRunAll()
{
	MinUnitRun(GaboCommandParseTest);
	MinUnitRun(GaboCommandParseDefaultTest);
	MinUnitRun(GaboCommandCopyTest);
	MinUnitRun(GaboCommandCopyEmptyTest);
	MinUnitRun(GaboCommandReadUsartTest);
	MinUnitRun(GaboCommandReadUsartNewLineTest);
	MinUnitRun(GaboCommandReadReadyTest);
	MinUnitRun(GaboCommandReadNotReadyCommandTest);
}

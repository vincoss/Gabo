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

	printf("Tests failed: %d, passed: %d, of tests: %d", MinUnitTestsFail, MinUnitTestsSuccess, MinUnitTestsRun);

	return MinUnitTestsRun - MinUnitTestsSuccess;
}

// Initialize or reset values, called for each test
void MinUnitInitialize(void)
{
	rx_data_count = 0;
	command_ready = 0;
	memset(rx_data_in, 0, strlen(rx_data_in));
}

char * GaboCommandParse_Test()
{
	uint8_t result = GaboCommandParse("A=255", 0);
	MinUnitAssert("Error:, GaboCommandParse_Test", result == 255);
	return 0;
}

char * GaboCommandParse_DefaultTest()
{
	char *s = "";
	uint8_t result = GaboCommandParse(s, 0);
	MinUnitAssert("Error:, GaboCommandParse_DefaultTest", result == 0);
	return 0;
}

char * GaboCommand_CopyTest()
{
	char data[8] = "A=255\n";
	char command[8];

	GaboCommandCopy(data, command);
	
	MinUnitAssert("Error:, GaboCommand_CopyTest data", strlen(data) == 0);
	MinUnitAssert("Error:, GaboCommand_CopyTest command", strcmp("A=255\n", command) == 0);

	return 0;
}

char * GaboCommandCopy_EmptyTest()
{
	char data[8] = "";
	char command[8] = "";

	GaboCommandCopy(data, command);

	MinUnitAssert("Error:, GaboCommandCopy_EmptyTest", strlen(command) == 0);

	return 0;
}

#pragma region GaboCommandRead

char * GaboCommandRead_BufferOverflowTest()
{
	rx_buffer_overflow = 1;
	GaboCommandRead();
	MinUnitAssert("Error: GaboCommandRead_BufferOverflowTest", rx_buffer_overflow == 0);
	return 0;
}

char * GaboCommandRead_NotReadyCommandTest()
{
	command_ready = 0;
	GaboCommandRead();
	MinUnitAssert("Error: GaboCommandRead_NotReadyCommandTest", strlen(rx_data_in) == 0);
	return 0;
}

char * GaboCommandRead_CommandReadyTest()
{
	// Arrange
	command_ready = 1;

	char data[8] = "A=127";
	strcpy_s(rx_data_in, 8, data);
	
	// Act
	GaboCommandRead();

	// Assert

	// Command in shoud contain value from rx buffer
	MinUnitAssert("Error: GaboCommandRead_CommandReadyTest copy", strcmp("A=127", command_in) == 0);

	// rx buffer all values should be null
	for (int i = 0; i <= RX_BUFFER_SIZE; i++)
	{
		MinUnitAssert("Error: GaboCommandRead_CommandReadyTest clear", rx_data_in[0] == '\0');
	}

	// Command variable should be set
	MinUnitAssert("Error: GaboCommandRead_CommandReadyTest powerCommand", powerCommand == 127);
	MinUnitAssert("Error: GaboCommandRead_CommandReadyTest command_ready", command_ready == 0);

	return 0;
}

#pragma endregion

#pragma region GaboCommandReadUsart

char * GaboCommandReadUsartEmptyCharTest()
{
	GaboCommandReadUsart('\0');

	MinUnitAssert("Error:, GaboCommandReadUsartEmptyCharTest data in", rx_data_in[0] == '\0');
	MinUnitAssert("Error:, GaboCommandReadUsartEmptyCharTest data count", rx_data_count == 0);

	return 0;
}

char * GaboCommandReadUsartNewLineCharTest()
{
	GaboCommandReadUsart('\n');

	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest data in", rx_data_in[0] == '\n');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest data count", rx_data_count == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest command ready", command_ready == 1);
	
	return 0;
}

char * GaboCommandReadUsartTest()
{
	GaboCommandReadUsart('A');
	GaboCommandReadUsart('B');

	MinUnitAssert("Error:, GaboCommandReadUsartTest data in", rx_data_in[1] == 'B');
	MinUnitAssert("Error:, GaboCommandReadUsartTest data count", rx_data_count == 2);
	MinUnitAssert("Error:, GaboCommandReadUsartTest command ready", command_ready == 0);

	return 0;
}

char * GaboCommandReadUsartNewLineTest()
{
	GaboCommandReadUsart('A');
	GaboCommandReadUsart('B');
	GaboCommandReadUsart('\n');

	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", rx_data_in[1] == 'B');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data count", rx_data_count == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest command ready", command_ready == 1);

	return 0;
}

char * GaboCommandReadUsartOverflowTest()
{
	for (int i = 0; i <= RX_BUFFER_SIZE; i++)
	{
		GaboCommandReadUsart(i);
	}

	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest data count", rx_data_count == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest command ready", command_ready == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest buffer overflow", rx_buffer_overflow == 1);

	for (int i = 0; i <= RX_BUFFER_SIZE; i++)
	{
		MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", rx_data_in[i] == '\0');
	}

	return 0;
}

#pragma endregion

//char * ConvertUInt8Test()
//{
//	char ch[] = "2";
//	uint8_t value = ConvertUInt8(ch);
//
//	MinUnitAssert("Error:, ConvertUInt8Test data in", value == 123);
//
//	return 0;
//}


// Register all tests in here
void UnitTestsRunAll()
{
	//MinUnitRun(ConvertUInt8Test);

	MinUnitRun(GaboCommandRead_BufferOverflowTest);
	MinUnitRun(GaboCommandRead_NotReadyCommandTest);
	MinUnitRun(GaboCommandRead_CommandReadyTest);

	MinUnitRun(GaboCommandParse_Test);
	MinUnitRun(GaboCommandParse_DefaultTest);

	MinUnitRun(GaboCommand_CopyTest);
	MinUnitRun(GaboCommandCopy_EmptyTest);

	MinUnitRun(GaboCommandReadUsartEmptyCharTest);
	MinUnitRun(GaboCommandReadUsartNewLineCharTest);
	MinUnitRun(GaboCommandReadUsartTest);
	MinUnitRun(GaboCommandReadUsartNewLineTest);
	MinUnitRun(GaboCommandReadUsartOverflowTest);
}

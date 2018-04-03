/*
*	UnitTests.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/

#include <stdint.h>
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
	rx_data_index = 0;
	command_ready = 0;
	memset(rx_data_in, 0, strlen(rx_data_in));
}

#pragma region GaboCommandParse

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

char * GaboCommandParse_MissingEqualSignTest()
{
	char *s = "A";
	uint8_t result = GaboCommandParse(s, 1);
	MinUnitAssert("Error:, GaboCommandParse_MissingEqualSignTest", result == 1);
	return 0;
}

#pragma endregion

#pragma region GaboCommandCopy

char * GaboCommandCopy_Test()
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

#pragma endregion

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
	rx_buffer_overflow = 0;

	char data[RX_BUFFER_SIZE] = "A=127";
	strcpy_s(rx_data_in, RX_BUFFER_SIZE, data);
	
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
	MinUnitAssert("Error: GaboCommandRead_CommandReadyTest powerCommandTemp == 127", powerCommandTemp == 127);
	MinUnitAssert("Error: GaboCommandRead_CommandReadyTest command_ready == 0", command_ready == 0);

	return 0;
}

#pragma endregion

#pragma region GaboCommandReadUsart

char * GaboCommandReadUsartEmptyCharTest()
{
	GaboCommandReadUsart('\0');

	MinUnitAssert("Error:, GaboCommandReadUsartEmptyCharTest data in", rx_data_in[0] == '\0');
	MinUnitAssert("Error:, GaboCommandReadUsartEmptyCharTest data count", rx_data_index == 0);

	return 0;
}

char * GaboCommandReadUsartNewLineCharTest()
{
	GaboCommandReadUsart('\n');

	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest data in", rx_data_in[0] == '\n');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest data count", rx_data_index == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineCharTest command ready", command_ready == 1);
	
	return 0;
}

char * GaboCommandReadUsartTest()
{
	GaboCommandReadUsart('A');
	GaboCommandReadUsart('B');

	MinUnitAssert("Error:, GaboCommandReadUsartTest data in", rx_data_in[0] == 'A');
	MinUnitAssert("Error:, GaboCommandReadUsartTest data in", rx_data_in[1] == 'B');
	MinUnitAssert("Error:, GaboCommandReadUsartTest data count", rx_data_index == 2);
	MinUnitAssert("Error:, GaboCommandReadUsartTest command ready", command_ready == 0);

	return 0;
}

char * GaboCommandReadUsartNewLineTest()
{
	GaboCommandReadUsart('A');
	GaboCommandReadUsart('B');
	GaboCommandReadUsart('\n');

	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", rx_data_in[0] == 'A');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", rx_data_in[1] == 'B');
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data count", rx_data_index == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest command ready", command_ready == 1);

	return 0;
}

char * GaboCommandReadUsartOverflowTest()
{
	for (int i = 0; i <= RX_BUFFER_SIZE; i++)
	{
		GaboCommandReadUsart(i);
	}

	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest data count", rx_data_index == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest command ready", command_ready == 0);
	MinUnitAssert("Error:, GaboCommandReadUsartOverflowTest buffer overflow", rx_buffer_overflow == 1);

	for (int i = 0; i <= RX_BUFFER_SIZE; i++)
	{
		MinUnitAssert("Error:, GaboCommandReadUsartNewLineTest data in", rx_data_in[i] == '\0');
	}

	return 0;
}

#pragma endregion

#pragma region Utility.h tests

char * UtilityIsBitSetTest()
{
	uint8_t value = 0b00000010;

	MinUnitAssert("Error:, UtilityIsBitSetTest data true", UtilityIsBitSet(value, 1) == 1);
	MinUnitAssert("Error:, UtilityIsBitSetTest data false", UtilityIsBitSet(value, 0) == 0);

	return 0;
}

char * UtilitySetBitAsUsedTest()
{
	uint8_t value = 0b00000000;
	UtilitySetBitAsUsed(&value, 1);

	MinUnitAssert("Error:, UtilitySetBitAsUsedTest", UtilityIsBitSet(value, 1) == 1);

	return 0;
}

char * UtilitySetBitAsUnUsedTest()
{
	uint8_t value = 0b00000010;
	UtilitySetBitAsUnUsed(&value, 1);

	MinUnitAssert("Error:, UtilitySetBitAsUnUsedTest", UtilityIsBitSet(value, 1) == 0);

	return 0;
}

char * UtilityFlipBitTest()
{
	uint8_t value = 0b00000000;
	UtilityFlipBit(&value, 1);

	MinUnitAssert("Error:, UtilityFlipBitTest", UtilityIsBitSet(value, 1) == 1);

	return 0;
}

char * IsNullOrEmptyTest()
{
	MinUnitAssert("Error:, IsNullOrEmptyTest null", IsNullOrEmpty(NULL) == 1);
	MinUnitAssert("Error:, IsNullOrEmptyTest empty", IsNullOrEmpty("") == 1);
	MinUnitAssert("Error:, IsNullOrEmptyTest not empty", IsNullOrEmpty("test") == 0);

	return 0;
}

char * IntToStringAndConvertToInt32Test()
{
	char buffer[12];
	int expected = INT32_MAX;
	char * format = "%ld"; 

	IntToString(expected, format, buffer, sizeof(buffer));
	int actual = ConvertToInt32(buffer, format);

	MinUnitAssert("Error:, IntToStringAndConvertToInt32Test", expected == actual);

	return 0;
}

char * UnsignedIntToStringUnsignedAndConvertToInt32Test()
{
	char buffer[12];
	unsigned int expected = UINT32_MAX;
	char * format = "%lu";

	UnsignedIntToString(expected, format, buffer, sizeof(buffer));
	unsigned int actual = ConvertToUnsignedInt32(buffer, format);

	MinUnitAssert("Error:, UnsignedIntToStringUnsignedAndConvertToInt32Test", expected == actual);

	return 0;
}

char * ConvertToUInt8Test()
{
	char buffer[8];
	int expected = UINT8_MAX;
	char * format = "%hhu";

	UnsignedIntToString(expected, format, buffer, sizeof(buffer));
	uint8_t actual = ConvertToUInt8(buffer, format);

	MinUnitAssert("Error:, UnsignedIntToStringUnsignedAndConvertToInt32Test", expected == actual);

	return 0;
}

#pragma endregion


// Register all tests in here
void UnitTestsRunAll()
{
	MinUnitRun(GaboCommandRead_BufferOverflowTest);
	MinUnitRun(GaboCommandRead_NotReadyCommandTest);
	MinUnitRun(GaboCommandRead_CommandReadyTest);

	MinUnitRun(GaboCommandParse_Test);
	MinUnitRun(GaboCommandParse_DefaultTest);
	MinUnitRun(GaboCommandParse_MissingEqualSignTest);

	MinUnitRun(GaboCommandCopy_Test);
	MinUnitRun(GaboCommandCopy_EmptyTest);

	MinUnitRun(GaboCommandReadUsartEmptyCharTest);
	MinUnitRun(GaboCommandReadUsartNewLineCharTest);
	MinUnitRun(GaboCommandReadUsartTest);
	MinUnitRun(GaboCommandReadUsartNewLineTest);
	MinUnitRun(GaboCommandReadUsartOverflowTest);

	// Utility.h
	MinUnitRun(UtilityIsBitSetTest);
	MinUnitRun(UtilitySetBitAsUsedTest);
	MinUnitRun(UtilitySetBitAsUnUsedTest);
	MinUnitRun(UtilityFlipBitTest);
	MinUnitRun(IsNullOrEmptyTest);
	MinUnitRun(IntToStringAndConvertToInt32Test);
	MinUnitRun(UnsignedIntToStringUnsignedAndConvertToInt32Test);
	MinUnitRun(ConvertToUInt8Test);
}

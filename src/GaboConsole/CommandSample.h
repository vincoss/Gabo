#include<stdio.h>
#include<string.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>



// The inputted commands are never going to be
// more than 8 chars long. Volatile for the ISR.
volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile uint8_t command_ready;

volatile uint8_t commandPower;


unsigned char ReadCommand(void);
long ParseCommandLong(char * str, long defaultValue);
uint8_t ParseCommand(char * str, uint8_t defaultValue);
void print_value(char *id, int *value);
void CopyCommand();
void PrintValue(char *id, int *value);


/*
A	Powertrain		(power on off)
PowertakeOff	(power on/off)

# Example in/out
A=3
A?

Z	Signal activate commands
Z=255
Z?
*/
unsigned int tempCommandCounter = 0;
unsigned char tempcommand[64] = "A=3\nZ=255\n";

void SampleCommand_Main(void)
{
	while (1)
	{
		// Example read command from USART
		UsartInterruptEventLogic();

		if (command_ready == 1)
		{
			CopyCommand();
			//process_command();

			command_ready = 0;
			//usart_ok();
		}

		tempCommandCounter++;
	}
}

void UsartInterruptEventLogic()
{
	// Get data from the USART in register
	data_in[data_count] = ReadCommand(); //UDR0;

										 // End of line!
	if (data_in[data_count] == '\n')
	{
		command_ready = 1;

		// Reset to 0, ready to go again
		data_count = 0;
	}
	else
	{
		data_count++;
	}
}

void CopyCommand()
{
	// TODO: lock in here

	// Copy the contents of data_in into command_in
	memcpy(command_in, data_in, 8);

	//// Now clear data_in, the USART can reuse it now
	memset(data_in[0], 0, 8);

	//// The USART might interrupt this - don't let that happen!
	//ATOMIC_BLOCK(ATOMIC_FORCEON) {
	//	// Copy the contents of data_in into command_in
	//	memcpy(command_in, data_in, 8);

	//	// Now clear data_in, the USART can reuse it now
	//	memset(data_in[0], 0, 8);
	//}
}

uint8_t ParseCommand(char * str, uint8_t defaultValue)
{
	if (strlen(str) <= 0)
	{
		return defaultValue;
	}

	char *pch;
	char cmdValue[8];
	// Find the position the equals sign is
	// in the string, keep a pointer to it
	pch = strchr(str, '=');
	// Copy everything after that point into
	// the buffer variable
	strcpy_s(cmdValue, strlen(str), pch + 1);
	// Now turn this value into an integer and
	// return it to the caller.
	return atoi(cmdValue);
}

long ParseCommandLong(char * str, long defaultValue)
{
	return 0;
}

void ProcessCommand(char * command_in)
{
	switch (command_in[0])
	{
	case 'A': // Powertrain
	{
		if (command_in[1] == '?') // TODO: send response back if '?'
		{
			// Do the query action for S
			PrintValue('A', commandPower);
		}
		else if (command_in[1] == '=')
		{
			commandPower = ParseCommand(command_in, 0);
		}
		break;
	}
	case 'B': // Left Powertrain speed
		if (command_in[1] == '?') {
			// Do the query action for M
		}
		else if (command_in[1] == '=') {
			// Do the set action for M
		}
		break;
	case 'C': // Right Powertrain speed
	{
		if (command_in[1] == '?') {
			// Do the query action for M
		}
		else if (command_in[1] == '=') {
			// Do the set action for M
		}
		break;
	}
	default:
		//usart_puts("NOT RECOGNISED\r\n");
		break;
	}
}



unsigned char ReadCommand(void)
{
	return tempcommand[tempCommandCounter];
}

void PrintValue(char *id, int *value)
{
	printf("%c %d", id, value);
	//char buffer[8];
	//itoa(value, buffer, 10);
	//usart_putc(id);
	//usart_putc(':');
	//usart_puts(buffer);
	//usart_puts(RETURN_NEWLINE);
}

#pragma region Temp only
//
//
//#define TRUE 1
//#define FALSE 0
//
//#define CHAR_NEWLINE '\n'
//#define CHAR_RETURN '\r'
//#define RETURN_NEWLINE "\r\n"

//
//unsigned long parse_assignment()
//{
//	char *pch;
//	char cmdValue[16];
//	// Find the position the equals sign is
//	// in the string, keep a pointer to it
//	pch = strchr(command_in, '=');
//	// Copy everything after that point into
//	// the buffer variable
//	strcpy(cmdValue, pch + 1);
//	// Now turn this value into an integer and
//	// return it to the caller.
//	return atoi(cmdValue);
//}
//
//void process_command()
//{
//	switch (command_in[0])
//	{
//	case 'A': // Powertrain
//	{
//		if (command_in[1] == '?') // TODO: send response back if '?'
//		{
//			// Do the query action for S
//			print_value('A', sensitivityCommand);
//		}
//		else if (command_in[1] == '=')
//		{
//			sensitivityCommand = parse_assignment();
//		}
//		break;
//	}
//	case 'B': // Left Powertrain speed
//		if (command_in[1] == '?') {
//			// Do the query action for M
//		}
//		else if (command_in[1] == '=') {
//			// Do the set action for M
//		}
//		break;
//	case 'C': // Right Powertrain speed
//	{
//		if (command_in[1] == '?') {
//			// Do the query action for M
//		}
//		else if (command_in[1] == '=') {
//			// Do the set action for M
//		}
//		break;
//	}
//	default:
//		//usart_puts("NOT RECOGNISED\r\n");
//		break;
//	}
//}

#pragma endregion

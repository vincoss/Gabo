
#ifndef COMMANDSAMPLE_H
#define COMMANDSAMPLE_H

#include<stdio.h>
#include<string.h>
#include <inttypes.h>


void CopyCommand(char * data, char * command);
uint8_t ParseCommand(char * str, uint8_t defaultValue);
void ProcessCommand(char * command_in);

void print_value(char *id, int *value);
uint8_t speedCommand = 95;

void CommandSample_Main(void)
{
	// Show defaults
	printf("Current speed %i", speedCommand);

	// Example put command
	char dataInput[8] = "A=27";
	char command[8];

	CopyCommand(dataInput, command);

	uint8_t value = ParseCommand(command, 0);
	ProcessCommand(command);


	printf("\Speed command: %i", value);

	// Example push command value back

	char dataInput2[8] = "A?";

	CopyCommand(dataInput, command);
	ProcessCommand(command);
}


void CopyCommand(char * data, char * command)
{
	if (strlen(data) <= 0)
	{
		return;
	}

	// TODO: lock in here

	// Copy the contents of data_in into command_in
	memcpy(command, data, 8);

	//// Now clear data_in, the USART can reuse it now
	memset(data, 0, 8);

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

void ProcessCommand(char * command_in)
{
	if (strlen(command_in) <= 0)
	{
		return;
	}

	switch (command_in[0])
	{
	case 'A': // Power command
	{
		if (command_in[1] == '?') // Send response back if '?'
		{
			// Do the query action for S
			print_value('A', speedCommand);
		}
		else if (command_in[1] == '=')
		{
			speedCommand = ParseCommand(command_in, 0);
		}
		break;
	}
	default:
	{
		//usart_puts("NOT RECOGNISED\r\n");
		break;

	}
	}
}

void print_value(char *id, int *value)
{
	printf("%c %d", id, value);
	//char buffer[8];
	//itoa(value, buffer, 10);
	//usart_putc(id);
	//usart_putc(':');
	//usart_puts(buffer);
	//usart_puts(RETURN_NEWLINE);
}

#endif
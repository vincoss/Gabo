#ifndef GaboCommand_H
#define GaboCommand_H

#include <stdio.h>
#include <string>
#include "GaboIo.h"

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
			print_value('A', powerCommand);
		}
		else if (command_in[1] == '=')
		{
			powerCommand = ParseCommand(command_in, 0);
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

#pragma region Command specific

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


#pragma endregion


#endif
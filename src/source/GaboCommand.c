#include <stdio.h>
#include<string.h>
#include "GaboCommand.h"
#include "GaboIo.h"

void GaboCommandRead(void)
{
	if (command_ready == 0)
	{
		// No command to process
		return;
	}

	GaboCommandCopy(data_in, command_in);
	GaboCommandProcess(command_in);

	command_ready = 0;
	GaboCommandPrint("OK\r\n", 0); // TODO: does not need two parameters
}

void GaboCommandProcess(char * command)
{
	if (strlen(command) <= 0)
	{
		return;
	}

	switch (command[0])
	{
		case 'A': // Power
		{
			if (command[1] == '?') // Send response back if '?'
			{
				GaboCommandPrint('A', powerCommand);
			}
			else if (command[1] == '=')
			{
				powerCommand = GaboCommandParse(command, 0);
			}
			break;
		}
		case 'B': // Powertrain
		{
			if (command[1] == '?') // Send response back if '?'
			{
				GaboCommandPrint('B', powertrainCommand);
			}
			else if (command[1] == '=')
			{
				powertrainCommand = GaboCommandParse(command, 0);
			}
			break;
		}
		default:
		{
			GaboCommandPrint("Command not recognised.\r\n", 0); // TODO: no need two parameters
			break;
		}
	}
}

void GaboCommandPrint(char *id, int *value) // TODO:
{
	printf("%c %d", id, value);
	//char buffer[8];
	//itoa(value, buffer, 10);
	//usart_putc(id);
	//usart_putc(':');
	//usart_puts(buffer);
	//usart_puts(RETURN_NEWLINE);
}

#pragma region Command specific

uint8_t GaboCommandParse(char * str, uint8_t defaultValue)
{
	if (strlen(str) <= 0)
	{
		return defaultValue;
	}

	if (strchr(str, '=') == NULL)
	{
		return defaultValue;
	}

	char *pch = NULL;
	char cmdValue[8];
	// Find the position the equals sign is
	// in the string, keep a pointer to it
	pch = strchr(str, '=');
	// Copy everything after that point into
	// the buffer variable
	//strcpy_s(cmdValue, strlen(str), pch + 1); // TODO: fix this
	CopyString(pch + 1, cmdValue);
	// Now turn this value into an integer and
	// return it to the caller.
	return atoi(cmdValue);
}

void CopyString(char *source, char *destination)
{
	if (strlen(source) > strlen(destination))
	{
		return; // does not fit
	}

	while (*source != '\0')
	{
		*destination++ = *source++;
	}
	*destination = '\0';
	return;
}

void GaboCommandCopy(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// Copy the contents of data_in into command_in
	memcpy(destCommand, srcData, 8);

	//// Now clear data_in, the USART can reuse it now
	memset(srcData, 0, 8);

	// TODO: lock in here

	//// The USART might interrupt this - don't let that happen!
	//ATOMIC_BLOCK(ATOMIC_FORCEON) {
	//	// Copy the contents of data_in into command_in
	//	memcpy(command_in, data_in, 8);

	//	// Now clear data_in, the USART can reuse it now
	//	memset(data_in[0], 0, 8);
	//}
}

void GaboCommandReadUsart(unsigned char data)
{
	data_in[data_count] = data; //UDR0;

	if (data_in[data_count] == '\n')// End of line!
	{
		// Command ready to parse
		command_ready = 1;

		// Reset to 0, ready to go again
		data_count = 0;
	}
	else
	{
		data_count++;
	}
}

#pragma endregion

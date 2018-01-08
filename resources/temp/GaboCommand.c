#include "GaboCommand.h"
#include "GaboIo.h"


void GaboCommandProcess(char * command_in)
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
			GaboCommandPrint('A', powerCommand);
		}
		else if (command_in[1] == '=')
		{
			powerCommand = GaboCommandParse(command_in, 0);
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

void GaboCommandPrint(char *id, int *value)
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

void GaboCommandCopy(char * data, char * command)
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

void GaboCommandReadUsart(unsigned char data)
{
	data_in[data_count] = data; //UDR0;

	if (data_in[data_count] == '\n')// End of line!
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

#pragma endregion

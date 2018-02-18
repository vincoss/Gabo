/*
*	GaboCommand.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Utility.h"
#include "GaboCommand.h"
#include "GaboCommandImpl.h"

const unsigned char NULL_CHAR = '\0';
const unsigned char NEW_LINE_CHAR = '\n';

void GaboCommandRead(void)
{
	if (rx_buffer_overflow == 1)
	{
		GaboCommandWriteLog("Command overflow.");
		rx_buffer_overflow = 0;
		return;
	}

	if (command_ready == 0)
	{
		// No command to process
		return;
	}

	GaboCommandCopy(rx_data_in, command_in);
	GaboCommandProcess(command_in);

	GaboCommandWriteLog("OK");
	command_ready = 0;
}

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
	char cmdValue[RX_BUFFER_SIZE];
	
	// Find the position the equals sign is in the string, keep a pointer to it
	pch = strchr(str, '=');
	
	// Copy everything after that point into the buffer variable.
	strcpy(cmdValue, pch + 1);

	uint8_t output = ConvertToUInt8(cmdValue);
	
	return output;
}

void GaboCommandReadUsart(unsigned char usartData)
{
	if (usartData == NULL_CHAR)
	{
		return;
	}

	rx_data_in[rx_data_count] = usartData;

	if (rx_data_in[rx_data_count] == NEW_LINE_CHAR) // End of line!
	{
		// Command ready to parse
		command_ready = 1;

		// Reset to 0, ready to go again
		rx_data_count = 0;
		return;
	}

	// Buffer overflow.
	if (rx_data_count + 1 == RX_BUFFER_SIZE)
	{
		// Clear all rx buffer
		for (unsigned char i = 0; i < RX_BUFFER_SIZE; i++)
		{
			rx_data_in[i] = NULL_CHAR;
		}

		rx_data_count = 0;
		command_ready = 0;
		rx_buffer_overflow = 1;
		return;
	}

	rx_data_count++;
}
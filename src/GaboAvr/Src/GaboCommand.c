/*
*	GaboCommand.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "GaboCommand.h"
#include "GaboIo.h"



const unsigned char NULL_CHAR = '\0';
const unsigned char NEW_LINE_CHAR = '\n';

void GaboCommandPrintTelemetry(void);
void GaboCommandHelp(void);
void GaboCommandWriteLog(char * message);



void SampleLoop()
{
	// Example, each cycle check for input command
	while (1)
	{
		GaboCommandRead();
	}
}

void GaboCommandRead(void)
{
	if (rx_buffer_overflow == 1)
	{
		GaboCommandWriteLog("Command overflow\r\n");
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

	command_ready = 0;
	GaboCommandWriteLog("OK\r\n"); // TODO: does not work, prints some wrong chars
}

// TODO: refactor this
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
			// TODO: refactor in to methods so it can be called from telemery method
			GaboCommandWriteLog("Power");
			GaboCommandWriteLog(powerCommand);
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
			GaboCommandWriteLog("Powertrain");
			GaboCommandWriteLog(powertrainCommand);
		}
		else if (command[1] == '=')
		{
			powertrainCommand = GaboCommandParse(command, 0);
		}
		break;
	}
	case 'T': // Telemetry out only
	{
		if (command[1] == '?')
		{
			GaboCommandPrintTelemetry();
		}
		break;
	}
	default:
	{
		GaboCommandWriteLog("Command not recognised. Enter H? for help.\r\n");
		break;
	}
	}
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

	while (*source != NULL_CHAR)
	{
		*destination++ = *source++;
	}
	*destination = NULL_CHAR;
	return;
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

void GaboCommandPrintTelemetry(void)
{
	// TODO: here push out all system variables and values.

	GaboCommandWriteLog("Power");
	GaboCommandWriteLog(powerCommand);

	GaboCommandWriteLog("Powertrain");
	GaboCommandWriteLog(powertrainCommand);
}

void GaboCommandHelp(void)
{
	// TODO: here push all command info back to the USARD
	// H? for help
}

// TOOD: possible store commands int temp values and then apply those when command apply is send
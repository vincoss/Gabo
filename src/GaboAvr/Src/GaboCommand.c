/*
*	GaboCommand.c
*
*	Created: 29/01/2018 10:09:16 PM
*	Author: Ferdinand Lukasak
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "Utility.h"
#include "GaboCommand.h"
#include "GaboCommandImpl.h"
#include "GaboIo.h"


const unsigned char NULL_CHAR = '\0';
const unsigned char NEW_LINE_CHAR = '\n';


void GaboCommandPrintTelemetry(void);
void GaboCommandHelp(void);
void GaboCommandWriteLog(char * message);



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

// TODO: refactor this to return success or fail on parse check for '='
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
	strcpy(cmdValue, pch + 1); // TODO: fix this
	//strcpy_s(cmdValue, strlen(str), pch + 1);
	//CopyString(pch + 1, cmdValue);

	int output = ConvertToUInt8(cmdValue);
	
	return output;
}

void CopyString(const char *source, char *destination)
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

void GaboCommandPrintTelemetry(void)
{
	// TODO: here push out all system variables and values.

	char buffer[5];

	GaboCommandWriteLog("Power");
	GaboCommandWriteLog(IntToString(powerCommand, "%d", buffer, sizeof buffer));

	//memset(&buffer[0], 0, sizeof(buffer));
	//// Now clear data_in, the USART can reuse it now
	memset(buffer, 0, sizeof(buffer));

	GaboCommandWriteLog("Powertrain");
	GaboCommandWriteLog(IntToString(powertrainCommand, "%d", buffer, sizeof buffer));
}

// H? for help.
void GaboCommandHelp(void)
{
	char buffer[5];

	GaboCommandWriteLog("Enter H? for help.");
	GaboCommandWriteLog("Each command must end with newline char.");
	GaboCommandWriteLog("Command max size.");
	GaboCommandWriteLog(IntToString(RX_BUFFER_SIZE, "%d", buffer, sizeof buffer));
	GaboCommandWriteLog("A={PowerCommand} write value");
	GaboCommandWriteLog("A? print power command value.");
}

// Clear the left and right whitespace
// e.g. "  123 456  " -> "123 456"
//char * Trim(const char *str)
//{
	//while (*str == ' ' || *str == '\t')
		//str++;
//
	//char *start = str;
//
	//if (!(*str))
		//return str;
//
	//char *end = str;
//
	//while (*str) {
		//if (*str != ' ' && *str != '\t')
			//end = str;
		//str++;
	//}
//
	//*(end + 1) = 0;
//
	//return start;
//}


/*
Examples
12.345e3 = 12345
12e-2=0.12
-12.34=-12.34
-12.34e3=-12340
-12.34e-2=-0.1234

// return 1 on success
int convertType(const char* value, double *destination) {
char sentinel;
return sscanf(value,"%f %c", destination, &sentinel) == 1;
}

double x;
if (convertType(some_string, &x)) {
printf("%.17e\n", x);  // or whatever FP format you like
} else {
puts("Failed");
}
*/
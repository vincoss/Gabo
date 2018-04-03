/*
 * GaboCommandImpl.c
 *
 * Created: 16/02/2018 6:12:25 PM
 *  Author: Ferdinand Lukasak
 */ 

#include "GaboIo.h"
#include "GaboCommandImpl.h"
#include <string.h>

void GaboCommandNotRecognisedMessage(void);
void GaboCommandPrintTelemetry(void);
void GaboCommandHelp(void);

 /*
 TODO: refactor this. This method is Gabo specific possible to refactor into own file.
 Possible store commands int temp values and then apply those when command apply is send.

 */
void GaboCommandProcess(const char * command)
{
	if (strlen(command) <= 1)
	{
		GaboCommandNotRecognisedMessage();
		return;
	}

	if (command[1] != '=' && command[1] != '?')
	{
		GaboCommandWriteLog("Incomplete command, command must follow with '=' or '?' character. Enter H? for help.");
		return;
	}

	char key = command[0];

	switch (toupper(key))
	{
	case 'A': // Power
	{
		if (command[1] == '?') // Send response back if '?'
		{
			// TODO: refactor in to methods so it can be called from telemery method
			GaboCommandWriteLog("Power");
			char buffer[5];
			GaboCommandWriteLog(IntToString(powerCommandTemp, "%d", buffer, sizeof buffer));
		}
		else if (command[1] == '=')
		{
			powerCommandTemp = GaboCommandParse(command, 0);
		}
		break;
	}
	case 'B': // Powertrain
	{
		if (command[1] == '?') // Send response back if '?'
		{
			GaboCommandWriteLog("Powertrain");
			char buffer[5];
			GaboCommandWriteLog(IntToString(powertrainCommandTemp, "%d", buffer, sizeof buffer));
		}
		else if (command[1] == '=')
		{
			powertrainCommandTemp = GaboCommandParse(command, 0);
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
	case 'H':	// Help
	{
		if (command[1] == '?')
		{
			GaboCommandHelp();
		}
		break;
	}
	case 'Z': // Begin/End command write
	{
		if (command[1] == '=')
		{
			startWriteCommand = GaboCommandParse(command, 0);
		}
		break;
	}
	default:
	{
		GaboCommandNotRecognisedMessage();
		break;
	}
	}
}

void GaboCommandNotRecognisedMessage(void)
{
	GaboCommandWriteLog("Command not recognised. Enter H? for help.");
}

void GaboCommandPrintTelemetry(void)
{
	// TODO: here push out all system variables and values.

	char buffer[5]; // TODO: refactor those into single global

	GaboCommandWriteLog("Power");
	GaboCommandWriteLog(IntToString(powerCommandTemp, "%d", buffer, sizeof buffer));

	//memset(&buffer[0], 0, sizeof(buffer));
	//// Now clear data_in, the USART can reuse it now
	memset(buffer, 0, sizeof(buffer));

	GaboCommandWriteLog("Powertrain");
	GaboCommandWriteLog(IntToString(powertrainCommandTemp, "%d", buffer, sizeof buffer));
	
	/*
		memory
		workhours power-train
		workhours power-takeOff
	*/
}

// Displays all available commands.
void GaboCommandHelp(void)
{
	char buffer[8];

	GaboCommandWriteLog("Command(s) write must start with Z=1\n and end with Z=0\n command.");
	GaboCommandWriteLog("Each command must start with A-Z character and end with newline character.");
	GaboCommandWriteLog("Command max size.");
	GaboCommandWriteLog(IntToString(8, "%d", buffer, sizeof(buffer))); // TODO: remove the hard coded value use RX_BUFFER_SIZE instead
	GaboCommandWriteLog("Use =,? signs to write or display value.");
	
	GaboCommandWriteLog("Available commands");

	GaboCommandWriteLog("<H?,h?> for help.");
	GaboCommandWriteLog("<T?,t?> for telemetry.");
		
	GaboCommandWriteLog("A={Power} write value");
	GaboCommandWriteLog("B={Powertrain} write value");
		
	GaboCommandWriteLog("Running time in milliseconds.");
	//GaboCommandWriteLog(IntToString(GaboTimeGetTickCount(), "%d", buffer, sizeof(buffer))); // nresolved external symbol GaboTimeGetTickCount referenced in function GaboCommandHelp
}
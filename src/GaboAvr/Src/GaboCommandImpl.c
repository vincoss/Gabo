/*
 * GaboCommandImpl.c
 *
 * Created: 16/02/2018 6:12:25 PM
 *  Author: Ferdinand Lukasak
 */ 

#include "GaboIo.h"
#include "GaboCommandImpl.h"

void GaboCommandNotRecognisedMessage(void);

 /*
 TODO: refactor this. This method is Gabo specific possible to refactor into own file.
 Possible store commands int temp values and then apply those when command apply is send.

 GaboCommand.h
 GaboCommandImpl.h
 */
void GaboCommandProcess(char * command)
{
	if (strlen(command) <= 1)
	{
		GaboCommandNotRecognisedMessage();
		return;
	}

	if (command[1] != '=' || command[1] != '?')
	{
		GaboCommandWriteLog("Incomplete command, command must follow with '=' or '?' character.");
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
			GaboCommandWriteLog(IntToString(powerCommand, "%d", buffer, sizeof buffer));
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
			char buffer[5];
			GaboCommandWriteLog(IntToString(powertrainCommand, "%d", buffer, sizeof buffer));
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
	case 'H':
	{
		if (command[1] == '?')
		{
			GaboCommandHelp();
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

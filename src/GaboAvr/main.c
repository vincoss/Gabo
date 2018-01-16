#include <avr/io.h>
#include <avr/delay.h>
#include <util\atomic.h>
#include <Usart.h>
#include <GaboIo.h>
#include <GaboCommand.h>
#include <GaboUsart.h>

#ifndef _AVR32
#define _AVR32
#endif

int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();

	char* a = "asd";
	char b[9];

	GaboCommandCopyLocal(a, b);

	uint8_t result = GaboCommandParse("A=255", 0);
	UsartWriteChar(result);

	while (1)
	{
		UsartWriteChar(powerCommand);
		UsartWriteChar(powertrainCommand);

		GaboCommandRead();

		UsartWriteChar(powerCommand);
		UsartWriteChar(commandPowertrain);

		_delay_ms(2000);
	}

	return 0;
}


void GaboCommandCopyLocal(char * srcData, char * destCommand)
{
	if (strlen(srcData) <= 0)
	{
		return;
	}

	// The USART might interrupt this - don't let that happen!
	ATOMIC_BLOCK(ATOMIC_FORCEON) 
	{
		// Copy the contents of data_in into command_in
		memcpy(destCommand, srcData, 8);

		//// Now clear data_in, the USART can reuse it now
		memset(srcData, 0, 8);
	}
}
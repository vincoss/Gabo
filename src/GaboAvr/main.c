#include <avr/io.h>
#include <avr/delay.h>
#include <Usart.h>
#include <GaboIo.h>
#include <GaboCommand.h>
#include <GaboUsart.h>


int main(int argc, char *argv[])
{
	UsartInitialize();
	GaboUsartInterruptInitialize();

	uint8_t result = GaboCommandParse("A=255", 0);
	UsartWriteChar(result);

	while (1)
	{
		UsartWriteChar(powerCommand);
		UsartWriteChar(commandPowertrain);

		GaboCommandRead();

		UsartWriteChar(powerCommand);
		UsartWriteChar(commandPowertrain);

		_delay_ms(2000);
	}

	return 0;
}
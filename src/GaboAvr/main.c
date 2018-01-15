#include <avr/io.h>
#include <avr/delay.h>
#include <Usart.h>
#include <GaboIo.h>
#include <GaboCommand.h>

int main(int argc, char *argv[])
{
	UsartInitialize();

	uint8_t result = GaboCommandParse("A=255", 0);

	while (1)
	{
	
		_delay_ms(100);
	}

	return 0;
}
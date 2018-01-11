#include <avr/io.h>
#include <avr/delay.h>
#include <Usart.h>

int main(int argc, char *argv[])
{
	UsartInitialize();

	_delay_ms(100);

	

	/*
	while (1)
	{
		GaboCommandProcess();
	}*/

	return 0;
}
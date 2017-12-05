#include <avr/io.h>	
#include <avr/interrupt.h>
#include "Usart.h"
#include "GaboUsart.h"
#include "GaboIo.h"


void GaboUsartInitialize(void)
{
	UsartInitialize();

	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Recieve Complete interrupt ( USART_RX )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

ISR(USART_RX_vect)
{
	// Get data from the USART in register
	data_in[data_count] = UDR0;

	// End of line!
	if (data_in[data_count] == '\n') 
	{
		command_ready = TRUE;
		// Reset to 0, ready to go again
		data_count = 0;
	}
	else
	{
		data_count++;
	}
}
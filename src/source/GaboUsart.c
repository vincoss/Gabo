#include <avr/io.h>	
#include <avr/interrupt.h>
#include "Usart.h"
#include "GaboUsart.h"
#include "GaboCommand.h"

// TODO: review these
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

void GaboUsartInterruptInitialize(void)
{
	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Recieve Complete interrupt ( USART_RX )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

ISR(USART_RX_vect)
{
	char status, data;

	///status = UCSRA;
	data = UDR0;

	// TODO:
	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) != 0)
	{
		return;
	};

	GaboCommandReadUsart(data);	
}
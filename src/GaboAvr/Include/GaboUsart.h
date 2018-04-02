/*
 * GaboUsart.h
 *
 * Created: 28/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_USART_H_
#define GABO_USART_H_

#include <avr/io.h>	
#include <avr/interrupt.h>
#include "GaboCommand.h"

void GaboUsartInterruptInitialize(void);

#define FRAMING_ERROR		(1 << FE0)
#define PARITY_ERROR		(1 << UPE0)
#define DATA_OVERRUN		(1 << DOR0)

// TODO: refactor into Usart.c one initialize just Usart no interrupt and second with interrupt
void GaboUsartInterruptInitialize(void)
{
	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Recieve Complete interrupt ( USART_RX )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

// TODO: move int main.c

ISR(USART_RX_vect)
{
	char status, data;

	status = UCSR0A;
	data = UDR0;

	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) != 0)
	{
		return;
	};

	GaboCommandReadUsart(data);
}

#endif
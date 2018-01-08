#include <avr/io.h>	
#include <avr/interrupt.h>
#include "Usart.h"
#include "GaboUsart.h"
#include "GaboCommand.h"


#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

void GaboUsartInitialize(void)
{
	UsartInitialize();

	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0); // Enable the USART Recieve Complete interrupt ( USART_RX )
	sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

ISR(USART_RX_vect)
{
	char status, data;

	status = UCSRA;
	data = UDR0;

	if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) != 0)
	{
		return;
	};

	GaboCommandReadUsart(data);	
}


//
//// USART Receiver interrupt service routine
//interrupt [USART_RXC] void usart_rx_isr(void)
//{
//char status,data;
//status=UCSRA;
//data=UDR;
//if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
//   { 
//   character_received=1;//enables parsing only if something is received
//   rx_buffer[rx_wr_index]=data;
//   if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
//   if (++rx_counter == RX_BUFFER_SIZE)
//      {
//      rx_counter=0;
//      rx_buffer_overflow=1;
//      };
//   };
//}
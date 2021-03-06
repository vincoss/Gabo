
#ifndef USART_H
#define USART_H 1

#include <avr/io.h>		

// NOTE: For more information see specification document. RS-232
 
//#define USART_BAUDRATE 9600   // The baudrate that we want to use
//#define USART_BAUD_PRESCALLER (((( F_CPU / 16UL) + ( USART_BAUDRATE / 2)) / ( USART_BAUDRATE )) - 1)

#define F_CPU 16000000UL // Says to the compiler which is our clock frequency, permits the delay functions to be very accurate
#define USART_BAUDRATE 9600   // The baudrate that we want to use
#define USART_BAUD_PRESCALLER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)    // The formula that does all the required maths

void UsartInitialize(void);

void UsartInitialize(void)
{
	// Load upper 8- bits of the baud rate value into the high byte of the UBRR register
	UBRR0H = (uint8_t)(USART_BAUD_PRESCALLER >> 8);
	// Load lower 8- bits of the baud rate value into the low byte of the UBRR register
	UBRR0L = (uint8_t)(USART_BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
}

void UsartWriteChar(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char UsartReadChar(void)
{
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UsartWriteCharString(unsigned char* stringPtr)
{
	// Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null '\n' char
	while (*stringPtr != 0x00)
	{
		// Using the simple send function we send one char at a time
		UsartWriteChar(*stringPtr);

		// We increment the pointer so we can read the next char
		stringPtr++;
	}
}

#endif
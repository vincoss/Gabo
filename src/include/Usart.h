
#ifndef USART_H
#define USART_H

// NOTE: For more information see specification document. RS-232
 
//#define USART_BAUDRATE 9600   // The baudrate that we want to use
//#define USART_BAUD_PRESCALLER (((( F_CPU / 16UL) + ( USART_BAUDRATE / 2)) / ( USART_BAUDRATE )) - 1)

#define F_CPU 16000000UL // Says to the compiler which is our clock frequency, permits the delay functions to be very accurate
#define USART_BAUDRATE 9600   // The baudrate that we want to use
#define USART_BAUD_PRESCALLER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)    // The formula that does all the required maths

void UsartInitialize(void);
void UsartWriteChar(unsigned char data);
unsigned char UsartReadChar(void);
void UsartWriteCharString(unsigned char* StringPtr);

#endif
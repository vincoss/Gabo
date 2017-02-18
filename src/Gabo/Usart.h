
#ifndef USART_H
#define USART_H

// NOTE: For more information see specification document. RS-232

#define USART_BAUDRATE 9600   // The baudrate that we want to use
#define USART_BAUD_PRESCALLER (((( F_CPU / 16) + ( USART_BAUDRATE / 2)) / ( USART_BAUDRATE )) - 1)

void UsartInitialize(void);
void UsartWriteChar(unsigned char data);
unsigned char UsartReadChar(void);
void UsartWriteCharString(char* StringPtr);

#endif
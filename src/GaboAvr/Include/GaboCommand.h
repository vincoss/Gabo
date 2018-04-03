/*
 * GaboCommand.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_COMMAND_H_
#define GABO_COMMAND_H_

#include <inttypes.h>

// Command variables
#define RX_BUFFER_SIZE 8
volatile unsigned char rx_data_in[RX_BUFFER_SIZE];
volatile unsigned char command_in[RX_BUFFER_SIZE];
volatile uint8_t rx_data_count;
volatile uint8_t command_ready;

// This flag is set on USART Receiver buffer overflow
volatile unsigned char rx_buffer_overflow;

void GaboCommandRead();
uint8_t GaboCommandParse(const char * str, uint8_t defaultValue);
void GaboCommandCopy(char * data, char * command);
void GaboCommandReadUsart(const unsigned char data);
void GaboCommandWriteLog(const char * message);

#endif
#ifndef GaboCommand_H
#define GaboCommand_H

#include <inttypes.h>

volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

void GaboCommandProcess(char * command_in);
uint8_t GaboCommandParse(char * str, uint8_t defaultValue);
void GaboCommandCopy(char * data, char * command);
void GaboCommandPrint(char *id, int *value);

#endif
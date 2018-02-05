/*
 * GaboCommand.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_COMMAND_H_
#define GABO_COMMAND_H_

#include <inttypes.h>

void GaboCommandRead();
void GaboCommandProcess(char * command_in);
uint8_t GaboCommandParse(char * str, uint8_t defaultValue);
void GaboCommandCopy(char * data, char * command);
void GaboCommandPrint(char *id, int *value);
void GaboCommandReadUsart(unsigned char data);
void CopyString(char *source, char *destination);
void GaboCommandWriteLog(char * message);

#endif
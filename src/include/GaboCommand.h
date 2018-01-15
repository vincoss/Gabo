#ifndef GaboCommand_H
#define GaboCommand_H 1

#include <inttypes.h>

void GaboCommandRead();
void GaboCommandProcess(char * command_in);
uint8_t GaboCommandParse(char * str, uint8_t defaultValue);
void GaboCommandCopy(char * data, char * command);
void GaboCommandPrint(char *id, int *value);
void GaboCommandReadUsart(unsigned char data);
void CopyString(char *source, char *destination);

#endif
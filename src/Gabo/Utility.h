
#ifndef UTILITY_H
#define UTILITY_H

#include <avr/io.h>

#define OFF 0
#define ON	1

uint8_t UtilityIsBitSet(uint8_t value, uint8_t bitindex);
void UtilitySetBitAsUsed(uint8_t * value, uint8_t bitIndex);
void UtilitySetBitAsUnUsed(uint8_t * value, uint8_t bitIndex);
void UtilityFlipBit(uint8_t * value, uint8_t bitIndex);

#endif
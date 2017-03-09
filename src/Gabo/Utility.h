
#ifndef UTILITY_H
#define UTILITY_H

#include <avr/io.h>

#define UTILITY_OFF 0
#define UTILITY_ON	1

uint8_t UtilityIsBitSet(uint8_t value, uint8_t bitindex); // TODO: Also by ref maybe
void UtilitySetBitAsUsed(volatile uint8_t * value, uint8_t bitIndex);
void UtilitySetBitAsUnUsed(volatile uint8_t * value, uint8_t bitIndex);
void UtilityFlipBit(volatile uint8_t * value, uint8_t bitIndex);

#endif
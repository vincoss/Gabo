/*
 * Utility.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef UTILITY_H_
#define UTILITY_H_

#define UTILITY_OFF 0
#define UTILITY_ON	1

uint8_t UtilityIsBitSet(uint8_t value, uint8_t bitindex) // TODO: Also by ref 
{
	return ((value & (1 << bitindex)) != 0) ? 1 : 0;
}

void UtilitySetBitAsUsed(volatile uint8_t * value, uint8_t bitIndex)
{
	*value = (*value | 1 << bitIndex);
}

void UtilitySetBitAsUnUsed(volatile uint8_t * value, uint8_t bitIndex)
{
	*value = (*value & ~(1 << bitIndex));
}

void UtilityFlipBit(volatile uint8_t * value, uint8_t bitIndex)
{
	((*value) ^= (1 << (bitIndex)));
}

#endif
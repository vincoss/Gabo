#include "Utility.h"


uint8_t UtilityIsBitSet(uint8_t value, uint8_t bitindex)
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
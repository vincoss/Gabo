/*
 * Utility.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef UTILITY_H_
#define UTILITY_H_

#include <inttypes.h>

uint8_t UtilityIsBitSet(uint8_t address, uint8_t bitindex)
{
	return ((address & (1 << bitindex)) != 0) ? 1 : 0;
}

void UtilitySetBitAsUsed(volatile uint8_t * address, uint8_t bitIndex)
{
	*address = (*address | 1 << bitIndex);
}

void UtilitySetBitAsUnUsed(volatile uint8_t * address, uint8_t bitIndex)
{
	*address = (*address & ~(1 << bitIndex));
}

void UtilityFlipBit(volatile uint8_t * address, uint8_t bitIndex)
{
	((*address) ^= (1 << (bitIndex)));
}

int IsNullOrEmpty(const char * str)
{
	if (str == NULL || !*str || *str == '\0')
	{
		return 1;
	}
	return 0;
}

/*
	NOTE: The snprintf and sscanf require other linker flags. '-Wl,-u,vfscanf -lprintf_flt -lscanf_flt'
*/

/*
	Formats
	short				%hi
	unsigned short		%hu
	signed int			%i or %d
	unsigned int		%u
	signed long			%li
	unsigned long		%lu
	long long			%lli
	unsinged long long	%llu
*/
char * IntToString(int value, const char * format, char * buffer, int length)
{
	if (IsNullOrEmpty(format) == 1)
	{
		return "";
	}
	memset(buffer, 0, length); // Clear
	snprintf(buffer, length, format, value);
	return buffer;
}

char * UnsignedIntToString(unsigned int value, const char * format, char * buffer, int length)
{
	if (IsNullOrEmpty(format) == 1)
	{
		return "";
	}
	memset(buffer, 0, length); // Clear
	snprintf(buffer, length, format, value);
	return buffer;
}

int ConvertToInt32(const char * str)
{
	if (IsNullOrEmpty(str) == 1)
	{
		return 0;
	}

	long int v;
	sscanf(str, "%ld", &v);
	return v;
}

unsigned int ConvertToUnsignedInt32(const char * str)
{
	if (IsNullOrEmpty(str) == 1)
	{
		return 0;
	}

	unsigned long int v;
	sscanf(str, "%lu", &v);
	return v;
}

uint8_t ConvertToUInt8(const char * str)
{
	if (IsNullOrEmpty(str) == 1)
	{
		return 0;
	}

	uint8_t v;
	sscanf(str, "%hhu", &v);
	return v;
}

/*
	TOOD: Not tested
*/

///*
//Formats
//float			%f, %g, %e, %a
//double			%lf, %lg, %le, %la
//long double		%Lf, %Lg, %Le, %La
//*/
//char * FloatToString(long double value, const char * format, char * buffer, int length)
//{
//	if (IsNullOrEmpty(format) == 1)
//	{
//		return "";
//	}
//	memset(buffer, 0, length); // Clear
//	snprintf(buffer, length, format, value);
//	return buffer;
//}
//
//
//float ConvertToFloat(const char * str)
//{
//	if (IsNullOrEmpty(str) == 1)
//	{
//		return 0;
//	}
//
//	//return atof(str);
//	float v;
//	sscanf(str, "%f", &v);
//	return v;
//}
//
//double ConvertToDouble(const char * str)
//{
//	if (IsNullOrEmpty(str) == 1)
//	{
//		return 0;
//	}
//
//	double v;
//	sscanf(str, "%lf", &v);
//	return v;
//}



#endif
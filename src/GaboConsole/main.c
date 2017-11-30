
#include<stdio.h>
#include <inttypes.h>

uint8_t DDRB = 4;
uint8_t PORTB = 2;

#define SET_SS_CS_LOW	(DDRB &= ~(1 << PORTB))  // Activate slave// TODO: port must be configurable
#define SET_SS_CS_HIGH	(DDRB |= (1 << PORTB))	// Deactivate slave // TODO: review wheter correct port is used


#define BitEquals(REG, bit, val)( ( (REG & (1UL << (bit) ) ) == ( (val) << (bit) ) ) )
uint8_t ButtonDebounce(volatile uint8_t * registerAddress, uint8_t pinNo);

int main()
{
	char dataInput[8] = "";

	int r = ParseCommand(dataInput, 0);

	printf("%d", r);

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}

void ToBinarySample()
{
	int a = (1 << 8);

	char binary[16];
	ToBinary(a, binary, sizeof(binary) - 1);
	printf("\n\nBinary a: %s", binary);
}


uint8_t ParseCommand(char * str, uint8_t defaultValue)
{
	if (strlen(str) <= 0)
	{
		return defaultValue;
	}

	char *pch;
	char cmdValue[8];
	// Find the position the equals sign is
	// in the string, keep a pointer to it
	pch = strchr(str, '=');
	// Copy everything after that point into
	// the buffer variable
	strcpy_s(cmdValue, strlen(str), pch + 1);
	// Now turn this value into an integer and
	// return it to the caller.
	return atoi(cmdValue);
}

// USART Receiver buffer
#define RX_BUFFER_SIZE 20
char rx_buffer[RX_BUFFER_SIZE];

#if RX_BUFFER_SIZE<256
unsigned char rx_wr_index, rx_rd_index, rx_counter;
#else
unsigned int rx_wr_index, rx_rd_index, rx_counter;
#endif

void clear_buffer(void)
{
	unsigned char temp;
	for (temp = 0; temp<RX_BUFFER_SIZE; temp++)
		rx_buffer[temp] = 0;           //fils receive buffer at beggining witk x       
	rx_wr_index = 0;   //when we empty buffer we should also reset circular buffer pointers to say it is empty.
	rx_rd_index = 0;
	rx_counter = 0;
}

void ToBinary(int num, char *str, int length)
{
	int i;
	str[length] = '\0';
	for (i = length - 1; i >= 0; --i, num >>= 1)
	{
		str[i] = (num & 1) + '0';
	}
}


uint8_t ButtonDebounce(volatile uint8_t * registerAddress, uint8_t pinNo)
{
	// If the button was pressed delay a bit
	if (BitEquals(*registerAddress, pinNo, 1))
	{
		printf("delay");
	}


	// Debounce the read value
	if (BitEquals(*registerAddress, pinNo, 1))  //Verify that the value is the same that what was read
	{
		return 1;
	}
	// If it is still 0 its because we had a button press
	// If the value is different the press is invalid
	else
	{
		return 0;
	}
}

// TODO: Review
//#define GetBit(p,m) ((p) & (m))
//#define SetBit(p,m) ((p) |= (m))

//#define bit_clear(p,m) ((p) &= ~(m))
//#define bit_flip(p,m) ((p) ^= (m))
//#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
//#define BIT(x)	(0x01 << (x))
//#define LONGBIT(x) ((unsigned long)0x00000001 << (x))
//To set a bit :
//bit_set(foo, 0x01);
//To set bit number 5:
//bit_set(foo, BIT(5));
//To clear bit number 6 with a bit mask :
//bit_clear(foo, 0x40);
//To flip bit number 0:
//bit_flip(foo, BIT(0));
//To check bit number 3:
//if (bit_get(foo, BIT(3)))
//{
//}
//To set or clear a bit based on bit number 4 :
//	if (bit_get(foo, BIT(4)))
//	{
//		bit_set(bar, BIT(0));
//	}
//	else
//	{
//		bit_clear(bar, BIT(0));
//	}
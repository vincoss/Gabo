
#include<stdio.h>
#include<string.h>
#include <inttypes.h>
#include "SampleCommand.h"

uint8_t DDRB = 4;
uint8_t PORTB = 2;

#define SET_SS_CS_LOW	(DDRB &= ~(1 << PORTB))  // Activate slave// TODO: port must be configurable
#define SET_SS_CS_HIGH	(DDRB |= (1 << PORTB))	// Deactivate slave // TODO: review wheter correct port is used


#define BitEquals(REG, bit, val)( ( (REG & (1UL << (bit) ) ) == ( (val) << (bit) ) ) )
uint8_t ButtonDebounce(volatile uint8_t * registerAddress, uint8_t pinNo);
//
//uint8_t ParseCommand(char * str, uint8_t defaultValue);
//void CopyCommand(char * command, char * data);
//void ProcessCommand(char * command_in);
//void print_value(char *id, int *value);
void ToBinary(int num, char *str, int length);
//long sensitivityCommand = 99;

int main()
{
	char dataInput[8] = "A?255";
	char command[8];

	CopyCommand(dataInput, command);
//	int r = ParseCommand(command, 0);
	ProcessCommand(command);

	//printf("%d", r);

	printf("\nDone...");
	getchar();
	getchar();

	return 0;
}


//void CopyCommand(char * data, char * command)
//{
//	if (strlen(data) <= 0)
//	{
//		return;
//	}
//
//	// TODO: lock in here
//
//	// Copy the contents of data_in into command_in
//	memcpy(command, data, 8);
//
//	//// Now clear data_in, the USART can reuse it now
//	memset(data, 0, 8);
//
//	//// The USART might interrupt this - don't let that happen!
//	//ATOMIC_BLOCK(ATOMIC_FORCEON) {
//	//	// Copy the contents of data_in into command_in
//	//	memcpy(command_in, data_in, 8);
//
//	//	// Now clear data_in, the USART can reuse it now
//	//	memset(data_in[0], 0, 8);
//	//}
//}
//
//uint8_t ParseCommand(char * str, uint8_t defaultValue)
//{
//	if (strlen(str) <= 0)
//	{
//		return defaultValue;
//	}
//
//	char *pch;
//	char cmdValue[8];
//	// Find the position the equals sign is
//	// in the string, keep a pointer to it
//	pch = strchr(str, '=');
//	// Copy everything after that point into
//	// the buffer variable
//	strcpy_s(cmdValue, strlen(str), pch + 1);
//	// Now turn this value into an integer and
//	// return it to the caller.
//	return atoi(cmdValue);
//}
//
//long ParseCommandLong(char * str, long defaultValue)
//{
//	return 0;
//}
//
//void ProcessCommand(char * command_in)
//{
//	switch (command_in[0])
//	{
//		case 'A': // Powertrain
//		{
//			if (command_in[1] == '?') // TODO: send response back if '?'
//			{
//				// Do the query action for S
//				print_value('A', sensitivityCommand);
//			}
//			else if (command_in[1] == '=')
//			{
//				sensitivityCommand = ParseCommand(command_in, 0);
//			}
//			break;
//		}
//	case 'B': // Left Powertrain speed
//		if (command_in[1] == '?') {
//			// Do the query action for M
//		}
//		else if (command_in[1] == '=') {
//			// Do the set action for M
//		}
//		break;
//	case 'C': // Right Powertrain speed
//	{
//		if (command_in[1] == '?') {
//			// Do the query action for M
//		}
//		else if (command_in[1] == '=') {
//			// Do the set action for M
//		}
//		break;
//	}
//	default:
//		//usart_puts("NOT RECOGNISED\r\n");
//		break;
//	}
//}
//
//void print_value(char *id, int *value)
//{
//	printf("%c %d", id, value);
//	//char buffer[8];
//	//itoa(value, buffer, 10);
//	//usart_putc(id);
//	//usart_putc(':');
//	//usart_puts(buffer);
//	//usart_puts(RETURN_NEWLINE);
//}

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


void ToBinarySample()
{
	int a = (1 << 8);

	char binary[16];
	ToBinary(a, binary, sizeof(binary) - 1);
	printf("\n\nBinary a: %s", binary);
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
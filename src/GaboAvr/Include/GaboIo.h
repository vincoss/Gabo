/*
 * GaboIo.h
 *
 * Created: 29/01/2018 10:09:16 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABO_IO_H_
#define GABO_IO_H_ 1

#include <inttypes.h>

//#define TRUE	1 // TODO: remove is not used
//#define FALSE	0

/*
	SPI
*/
#define GABOIO_SPI_REGISTER	DDRB
#define GABOIO_SPI_PORT		PORTB

#define GABOIO_SPI_DATA			(1<<PB3)	// MOSI (SI)
#define GABOIO_SPI_CLOCK		(1<<PB5)	//SCK  (SCK)
#define GABOIO_SPI_OUTPUT_LATCH	PB2	// Output
#define GABOIO_SPI_INPUT_LATCH	PB4	// Input
#define GABOIO_SPI_SET_OUTPUT_LATCH_LOW		(PORTB &= ~(1 << GABOIO_SPI_OUTPUT_LATCH))	// Activate slave
#define GABOIO_SPI_SET_OUTPUT_LATCH_HIGH	(PORTB |= (1 << GABOIO_SPI_OUTPUT_LATCH))	// Deactivate slave
#define GABOIO_SPI_SET_INPUT_LATCH_LOW		(PORTB &= ~(1 << GABOIO_SPI_INPUT_LATCH))	// Activate slave
#define GABOIO_SPI_SET_INPUT_LATCH_HIGH		(PORTB |= (1 << GABOIO_SPI_INPUT_LATCH))	// Deactivate slave

/*
*/
volatile uint8_t powerCommandTemp;		// 00000111, controller, powertrain, pto
volatile uint8_t powertrainCommandTemp;

volatile uint8_t PowerCommand;			// Store power on/off value
volatile uint8_t PowertrainCommand;		// Store powertrain on/off values left and right
volatile uint8_t PowerTakeOffCommand;	// Store Power takeOff values

volatile int powertrainWorkHours;	// TODO: these should be persited every hour write increment log
volatile int powertakeoffWorkHours; // TODO: these should be persited every hour write increment log

volatile uint8_t startWriteCommand; // z=1,z=0
volatile uint8_t IsOutputInitialized;	// Indicates that output was already set at least one time.


/*
	TODO: add commands flags, startWriteCommand, endWriteCommand
	Those flags shall be used when commands are written, it might take few interactions(CPU cycles) 
	until all commands are written when command write is complete set end writeCommand to true.
	On this stage commands must be pushed from temp variables to program variables.
	
	# Shaft read sensor (Hall sensor), current max rpm is 200 then encoder has 50 teeth, the SPI read rate should be high enough to read incoming
	shaft changes = 200*50 = 10,000 per minute
	main loop read SPI bus should around 200 per second
	on/off signals
	
*/

#endif

/*
	TODO: See this regitster definition as a example. io43u32x.h

	I/O Registers
	
	A	Power
	B	Powertrain
	C	PowerTakeOff
	D	
*/

// A=Power	(output)
#define PINA0	0	// controller
#define PINA1	1	// powertrain
#define PINA3	2	// powerTakeOff (PTO)
#define PINA3	3

// B=Powertrain	(output)
#define PINB0	0	// left		start/stop
#define PINB1	1	// right	start/stop
#define PINB2	2	// left		run/brake
#define PINB3	3	// right	run/brake
#define PINB4	4	// left		cw/ccw
#define PINB5	5	// right	cw/ccw
#define PINB6	6	// left&right	int.vr/ext (set POT Internal)
#define PINB7	7	// left&right	alarm-reset

// C=PowerTakeOff (output)

// D=Hall sensor (input)
#define PIND0	0	// left
#define PIND1	1	// right

/*
	# Powertrain Right and Left, input and output signals. JST 12 pin connector.
	
	Oriental Motor
	BLHD30K DC24V
	BLH230
	
	1	Alarm (output)	Brown
	2	Speed (output)	Red
	3	GND				Orange
	4	VRH POT			Yellow
	5	VRH POT			Green
	6	VRH POT			Blue
	7	Alarm-Reset (input)	Purple
	8	INT.VR/EXT	POT internal or external	Brown
	9	CW/CCW		(input)	Gray
	10	Run/Brake	(input)	White
	11	Start/Stop	(input)	Black
	
*/

/*
	# Example input command
	A=3	On power controller and powertrain
	B=159	start,run,cw,pot internal,alarm off
*/
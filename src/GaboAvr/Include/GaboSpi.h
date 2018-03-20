/*
 * GaboSpi.h
 *
 * Created: 13/03/2018 5:23:36 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOSPI_H_
#define GABOSPI_H_

void GaboSpiInitialize(void);
uint8_t GaboSpiSend(uint8_t data);

void GaboSpiInitialize(void)
{
	//// IO init
	//GABOIO_SPI_REGISTER_DDRB |= (GABOIO_SPI_DATA | GABOIO_SPI_OUTPUT_LATCH_PINB2 | GABOIO_SPI_CLOCK);	//Set control pins as outputs
	//GABOIO_SPI_PORT_PORTB &= ~(GABOIO_SPI_DATA | GABOIO_SPI_OUTPUT_LATCH_PINB2 | GABOIO_SPI_CLOCK);		//Set control pins low
	//
	//
	//// Enable SPI, Set Master, clock F_CPU/16
	//SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);	// Start SPI as Master
}

uint8_t GaboSpiSend(uint8_t data)
{
	return 0;
}

#endif /* GABOSPI_H_ */
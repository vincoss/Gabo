/*
 * GaboSpi.h
 *
 * Created: 13/03/2018 5:23:36 PM
 *  Author: Ferdinand Lukasak
 */ 


#ifndef GABOSPI_H_
#define GABOSPI_H_

void GaboSpiInitialize(void);
void GaboSpiIoInitialize(void);
uint8_t GaboSpiSend(uint8_t data);

void GaboSpiInitialize(void)
{
	SPCR = ((1 << SPE) |	// SPI Enable
			(1 << MSTR) |   // Master/Slave select
			(1 << SPR0));	// Clock F_CPU/16
}

void GaboSpiIoInitialize()
{
	// Set control pins as outputs
	GABOIO_SPI_REGISTER |= (GABOIO_SPI_DATA | GABOIO_SPI_OUTPUT_LATCH | GABOIO_SPI_CLOCK);	
	
	// Set control pins low
	GABOIO_SPI_PORT &= ~(GABOIO_SPI_DATA | GABOIO_SPI_OUTPUT_LATCH | GABOIO_SPI_CLOCK);
	
	// Set to high to not transmit
	GABOIO_SPI_SET_OUTPUT_LATCH_HIGH;
	GABOIO_SPI_SET_INPUT_LATCH_HIGH;
}

uint8_t GaboSpiSend(uint8_t dataOut)
{
	uint8_t dataIn;
	SPDR = dataOut; // Shift in some data
	while (!(SPSR & (1 << SPIF)));	//Wait for SPI process to finish
	dataIn = SPDR; // Clear SPIF flag,
	return dataIn;
}

#endif /* GABOSPI_H_ */

#ifndef MCP4XXX_H
#define MCP4XXX_H

#include <stdlib.h> 
#include <avr/io.h>	

/*

Microchip Pins 4251/103E/P

CS		VDD
SCK		SDO
SDI		SHDN
VSS		NC
P1B		P0B
P1W		P0W
P1A		P0A

*/

void Mcp4xxxInitialize(uint8_t * ssRegister, uint8_t  ssPort);

uint8_t Mcp4xxxSetBothWiper(uint16_t value);
uint8_t Mcp4xxxSetBothWiperByPercent(uint8_t percent);
uint8_t Mcp4xxxSetStep(uint8_t wiper, uint16_t value);

uint8_t Mcp4xxxSetMaxStepWiper0();
uint8_t Mcp4xxxSetMinStepWiper0();
uint8_t Mcp4xxxSetMaxStepWiper1();
uint8_t Mcp4xxxSetMinStepWiper1();

uint8_t Mcp4xxxIncrementStep(uint8_t wiper);
uint8_t Mcp4xxxDecrementStep(uint8_t wiper);

uint8_t Mcp4xxxRead(uint16_t *wiper0, uint16_t *wiper1);

// TODO: complete
uint8_t Mcp4xxxWriteTcon(uint8_t value);
uint8_t Mcp4xxxReadTcon(void);

#endif

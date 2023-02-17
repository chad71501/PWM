#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef SPI_SET
#define SPI_SET


#define PIN_SS   PD5
#define PIN_SCK  PB1
#define PIN_MOSI PB2
#define PIN_MISO PB3
#define SS_LOW   PORTD &= ~(1 << PIN_SS)
#define SS_HIGH  PORTD |= (1 << PIN_SS)


void SPI_MasterInit(void) ;
void SPI_SlaveInit(void);
uint8_t SPI_transmit_byte(uint8_t);
void SPIDecoder(uint8_t);

#endif 

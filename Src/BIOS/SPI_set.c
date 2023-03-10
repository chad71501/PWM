#include "SPI_set.h"

#include <stdio.h>
#define TEST printf("123\n");


#define A PF0
#define B PF1
#define C PF2
#define HI  1 // HI
#define LOW  0 // LOW

// SPISASBUS select
void SPIDecoder(uint8_t selectnum){
    DDRF |= 0x07;
    PORTF |= selectnum & 0x07;
}


void SPI_MasterInit(void) {
    DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << PB0);    // set pin SCK, MOSI, SS as output
    DDRB &= ~(1 << PIN_MISO);    // set pin MISO as input
    SS_Set;      // SS as output
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) |
           (1 << CPHA);    // notice M&S's CPOL and CPHA  need to equal
    SS_HIGH;
}

void SPI_SlaveInit(void) {
    DDRB &=
        ~((1 << PIN_SCK) | (1 << PIN_MISO) | (1 << PIN_SS));    // set pin SCK, MOSI, SS as input
    DDRB |= (1 << PIN_MISO);                                    // set pin MISO as output
    SPCR = (1 << SPIE) | (1 << SPE) | (1 << SPR1) |
           (1 << SPR0);    // notice M&S's CPOL and CPHA  need to equal
    sei();
}

uint8_t SPI_transmit_byte(uint8_t data) {
    // printf("data %x \n", data);
    SPDR = data;    // start transmission
    while (!(SPSR & (1 << SPIF)))
        ;    // wait for transmission complet
    return SPDR;    // return data from Slave/Receiver
}

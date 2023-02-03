/**
 * @file Encoder.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <avr/io.h>
#include "Src/SPI/SPI_set.h"
#include "Src/Uart/uartdevice.h"
#include <util/delay.h>

uint16_t Command = 0x7FFF;
uint16_t Data = 0;
uint8_t readData = 0;
int main()
{
    C4M_STDIO_init();
    SPI_MasterInit();
    /*check footpin state*/
    // printf("DDRB %x\n", DDRB);
    // printf("PortB %x\n", PORTB);
    // printf("DDRD %x\n",DDRD);
    // printf("PortD %x\n", PORTD);

    while (1)
    {

        //printf("123\n");
        SS_LOW; // SPI_set.h define
        //printf("123\n");
        Data = SPI_transmit_byte((Command >> 8) & 0x7F); // send Command  MSB 8bit
        readData = SPI_transmit_byte((Command & 0xFF)); // send Command LSB 8bit
        Data = (Data<<8)|readData ;
        printf("Data %x\n",Data);
        SS_HIGH;
        _delay_us(100000);
        // scanf("%hhd", &a);
    }
    return 0;
}
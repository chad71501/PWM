#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Src/SPI/SPI_set.h"
#include "Src/Uart/uartdevice.h"

int main()
{
  uint8_t mydata[5] = {0x55, 0x44, 0x33, 0x22, 0x11}; // test data
  uint8_t received_data[5];                           // store data from Slave/receiver
  // uint8_t a = 0;
  C4M_STDIO_init();
  SPI_MasterInit();

  printf("DDRB %x\n", DDRB);
  printf("DDRD %x\n", DDRD);
  printf("PortD %x\n", PORTD);
  printf("SPCR %x\n",SPCR);
  //sei();
  while (1)
  {
    _delay_ms(500);
    SS_LOW;
    _delay_ms(500);
    for (unsigned int i = 0; i < 5; i++)
    {
      received_data[i] = SPI_transmit_byte(mydata[i]); // send data and receive data
      printf("received_data[%d] = %x\n ", i, received_data[i]);
      _delay_ms(500);
    }
    SS_HIGH;
    _delay_ms(500);
    //scanf("%hhd", &a);
  }
  return 0;
}

/*
ISR(SPI_STC_vect){
  printf("successful \n");
}
*/
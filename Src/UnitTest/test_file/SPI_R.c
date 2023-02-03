#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "SPI/SPI_set.h"
#include "Uart/uartdevice.h"

uint8_t mydata[5] = {0x90, 0x80, 0x70, 0x60, 0x50};    // test data
uint16_t index1 = 0;                                   // index for test data array
uint8_t received_data[5];                              // store data from Slave/receiver
uint8_t flag = 0;

int main() {
    C4M_STDIO_init();
    SPI_SlaveInit();

    while (1) {
        while (flag == 1) {
            flag = 0;
            printf("received_data[%d] = %x\n", index1, received_data[index1]);
            if (!flag) break;
        }
    }

    return 0;
}

ISR(SPI_STC_vect) {
    SPDR = SPI_transmit_byte(mydata[index1]);
    received_data[index1] = SPDR;
    printf("received_data[%d] = %x\n", index1, received_data[index1]);
    index1++;
    flag = 1;
    if (index1 == 4) {
        index1 = 0;
    }

}
/**
 * @file SPI.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief
 * @version 0.1
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "SPI_set.h"
#include "uartdevice.h"
#include "AS5X47Spi.h"

uint8_t redata;
int main() {
    uart_init();
    SPI_MasterInit();
    while (1)
    {
        /* code */
        readData(0x3FFF, 0);

    }
    
    printf("Hellow\n");
}
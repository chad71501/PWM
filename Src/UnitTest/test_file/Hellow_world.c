/**
 * @file Hellow_world.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <avr/io.h>
#include <stdio.h>
#include "SPI_set.h"
#include "uartdevice.h"
int main(){

    uart_init();
    printf("123\n");
}
/**
 * @file stdio.c
 * @author LiYu87
 * @brief C4M_STDIO_init的實現。
 * @date 2019.10.13
 */

#include "uartdevice.h"
#include <avr/io.h>

#ifndef DEFAULTUARTBAUD
#define DEFAULTUARTBAUD 38400
#endif

/**
 * @brief ASA M128 標準IO 之 putchar 實現。
 *
 * @param c
 * @param stream
 * @return int
 */
static int stdio_putchar(char c, FILE *stream);

/**
 * @brief ASA M128 標準IO 之 getchar 實現。
 *
 * @param stream
 * @return int
 */
static int stdio_getchar(FILE *stream);

/**
 * @brief 標準IO 管理用的結構。
 *
 * 結構中包含輸出入單位元組該呼叫何種函式及其他資訊。
 * 會被 avrlibc 中的標準IO函式(getc、putc、printf、scanf等)所使用。
 */
static FILE STDIO_BUFFER =
    FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar, _FDEV_SETUP_RW);

static int stdio_putchar(char c, FILE *stream) {
    if (c == '\n') stdio_putchar('\r', stream);
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;

    return 0;
}

int stdio_getchar(FILE *stream) {
    int UDR_Buff;
    while (!(UCSR0A & (1 << RXC0)))
        ;
    UDR_Buff = UDR0;

    return UDR_Buff;
}

void uart_init(void) {
    unsigned int baud;

    baud = F_CPU / 16 / DEFAULTUARTBAUD - 1;
    UBRR0H = (unsigned char)(baud >> 8);
    UBRR0L = (unsigned char)baud;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (3 << UCSZ00);

    stdout = &STDIO_BUFFER;
    stdin = &STDIO_BUFFER;
}

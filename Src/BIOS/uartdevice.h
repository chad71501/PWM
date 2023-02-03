/**
 * @file stdio.h
 * @author LiYu87
 * @brief 宣告初始化 stdio 相關函式原型。
 * @date 2019.4.6
 */

#ifndef C4MLIB_STDIO_STDIO_H
#define C4MLIB_STDIO_STDIO_H

#include <stdio.h>
/**
 * @defgroup stdio_func stdio functions
 */

/* Public Section Start */
/**
 * @brief 進行標準IO進行初始化的動作。
 * @ingroup stdio_func
 *
 * 依據各個硬體平台去連結不同的通訊方式到 standard IO 中，
 * 便有printf、scanf等的標準IO操作函式可以使用。
 */
void uart_init(void);
/* Public Section End */


#endif  // C4MLIB_STDIO_STDIO_H

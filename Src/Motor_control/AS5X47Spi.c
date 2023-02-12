/** @file AS5X47Spi.cpp
 *
 * @brief A library for Arduino boards that reads angles from AS5047 and AS5147 sensors.
 * 		  Also support configuration of the sensor parameters.
 *
 * @par
 * COPYRIGHT NOTICE: MIT License
 *
 * 	Copyright (c) 2020 Adrien Legrand <contact@adrien-legrand.com>
 *
 * 	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 * 	in the Software without restriction, including without limitation the rights
 * 	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * 	copies of the Software, and to permit persons to whom the Software is
 * 	furnished to do so, subject to the following conditions:
 *
 * 	The above copyright notice and this permission notice shall be included in all
 * 	copies or substantial portions of the Software.
 *
 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * 	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 	SOFTWARE.
 *
*/

#include "AS5X47Spi.h"

// uint8_t Command[2] = {0xFF, 0x3F};    // encoder reg mode

void  writeData(uint16_t command, uint16_t value) {
	// @todo Expose the SPI Maximum Frequency in library interface.
	Command _command;
	Encoder _encoder;
	_command.reg = command;
	_encoder.data = value;
	// Send command
	SS_LOW;
    SPI_transmit_byte(_command.regarray[0]);    // send Command LSB 8bit
    SPI_transmit_byte(_command.regarray[1]);    // send Command  MSB 8bit
	SS_HIGH;
	_delay_ms(1);
	
	// Read data
	SS_LOW;
	SPI_transmit_byte(_encoder.readarray[0]);    // send Command LSB 8bit
    SPI_transmit_byte(_encoder.readarray[1]);    // send Command  MSB 8bit	SS_HIGH;
	_delay_ms(1);

}

uint16_t readData(uint16_t command, uint16_t nopCommand) {

	Command _command;
	Encoder _encoder;
	_command.reg = command;
	// Send Read Command
	SS_LOW;
    SPI_transmit_byte(_command.regarray[0]);    // send Command MSB 8bit
    SPI_transmit_byte(_command.regarray[1]);    // send Command LSB 8bit
	SS_HIGH;
	_delay_ms(1);
	
	// Send Nop Command while receiving data
	SS_LOW;
   	_encoder.readarray[1] = SPI_transmit_byte(nopCommand);    // send Command LSB 8bit
    _encoder.readarray[0] = SPI_transmit_byte(nopCommand);    // send Command  MSB 8bit	SS_HIGH;
	_delay_ms(1);
	SS_HIGH;
	return _encoder.data;
}

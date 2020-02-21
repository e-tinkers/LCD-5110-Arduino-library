# LCD5110 Arduino library
This is a simple and easy-to-use Arduino library for LCD 5110 (a.k.a. Nokia 5110 or PCD8544) display module. Unlike other libraries that try to be swiss-knift for all LCD modules, this library targeting only LCD5110 with compact code and reliable SPI interface.

There is also a python library that shares the same APIs for Raspberry Pi [available](https://github.com/e-tinkers/LCD-5110-Raspberry-Library).

## Installation

Download the repository and move it into your Sketchbook/Libraries directory. For **Linux** machine, the directory is home/username/Sketchbook/Libraries/. For **Windows** or **Macintosh** machines, it is Documents/Arduino/Libraries/.

## Hardware interface

By default, the library assumed that the LCD module is connected with Arduino I/O pins as follow:

|**LCD Pin** |**Arduino I/O Pin** |**Functionality**|
|:----------:|:------------------:|:---------------:|
|CLK|D13 (SCLK)|Serial clock|
|DN|D11 (MOSI)|Master output, Slave input|
|DC|D10|0: Command mode, 1: Data mode|
|RST|D9|Reset the chip when RST=0|
|SCE|D8|System Chip Enable when SCE=0|
|LED|D7|Backlight LED,ON = HIGH, OFF=LOW|
|GND|GND|System ground|
|VCC|3v3|Power Supply from 2.7 - 5v|

* LED = Backlight. Connects D7 to the backlight pin via a 220-ohm resistor to restrict the current flow through the GPIO D7.

## API for LCD5110 library

**`LCD5110 lcd`**
- Create an instance called lcd of class LCD5110. The class construct will:

    1. initialise GPIO and SPI ports;
    2. clear the screen and internal display memory
    3. set cursor to row 1, col 1
    4. set LCD display mode = Normal


**`void LCD5110.clear(void)`**
- Clear LCD screen and internal DDRAM, it is also set cursor to row 1, col 1


**`void LCD5110.cursor(uint8_t row, uint8_t col)`**
- Set LCD cursor to row (from 1 to 6), col (from 1 to 14)


**`void LCD5110.backlight(const uint8_t ON|OFF)`**
- set ON or OFF of LCD backlight


**`void LCD5110.inverse(const uint8_t ON|OFF)`**
- Set display mode to Inverse with ON or Normal with OFF


**`void LCD5110.printStr(const char *str)`**
- Print str[] array on screen


**`void LCD5110.printImage(const char *image)`**
- Print image[], image is an array[504] of pixels data

## Wiring between LCD5110 and Arduino
[![wiring diagram between LCD5110 and Arduino](https://github.com/e-tinkers/LCD-5110-Arduino-library/blob/master/LCD5110_wiring_with_arduino.png)](https://github.com/e-tinkers/LCD-5110-Arduino-library/blob/master/LCD5110_wiring_with_arduino.png)
## Extra
[Nokia5110 LCD Image Creator](https://www.e-tinkers.com/nokia5110-lcd-image-creator/) is a web application that providea pixel canvas for creating logo image to be used by LCD5110. The app will generate a logo array that you can copy and paste into your sketch.

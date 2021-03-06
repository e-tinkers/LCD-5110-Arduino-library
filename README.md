# Simple LCD5110/PCD8544 library
This is a simple and SRAM-efficient Arduino library for LCD 5110 (a.k.a. Nokia 5110 or PCD8544) display module. Unlike other libraries that try to be swiss-knift for all LCD modules, this library targeting only on LCD5110 with compact code and reliable SPI interface. It has extremely low usage of only 23 bytes SRAM (depends on MCU used).

## Installation

Download the repository and move it into your Sketchbook/Libraries directory. Or intall using `git clone https://github.com/e-tinkers/LCD-5110-Arduino-library`.

## Hardware interface

By default, the library assumed that the LCD module is connected with SPI pins based on whatever the Arduino board you are using. The only extra pins that you will need to defined when creating an instance of LCD class are pins to be used for DC and LED pins, you can use any Digital I/O pins, here is an example when connecting to an Arduino Nano where pin 8 is used as DC, and pin 7 is used as LED control:

|**LCD Pin** |**Arduino I/O Pin** |**Functionality**|
|:----------:|:------------------:|:---------------:|
|CLK|SCK|Serial clock|
|DN|MOSI|Master output, Slave input|
|DC|D8|0: Command mode, 1: Data mode|
|RST|RST|Reset the chip when RST=0|
|SCE|SS|System Chip Enable when SCE=0|
|LED|D7*|Turn ON/OFF Backlight LED|
|GND|GND|System ground|
|VCC|3v3|Power Supply from 2.7 - 5v|

* Connects D7 to the backlight pin via a 330-ohm (or 220-ohm for 3.3v supply) resistor to restrict the current flow through the GPIO D7.

## API for LCD5110 library

**`LCD5110 lcd`**
- Create an instance of LCD5110 class.


**`void LCD5110.begin(uint8_t dc, uint8_t led)`**
- Setup and initialized LCD:

    1. initialise GPIO and SPI ports together with the pins passed in for using as DC and LED backlight;
    2. clear the screen and internal display memory
    3. set cursor to row 1, col 1
    4. set LCD display mode = Normal (i.e. non-inverse)


**`void LCD5110.clear(void)`**
- Clear LCD screen and internal DDRAM, it is also set cursor to row 1, col 1


**`void LCD5110.cursor(uint8_t row, uint8_t col)`**
- Set LCD cursor to row (from 1 to 6), col (from 1 to 14)


**`void LCD5110.backlight(const uint8_t ON|OFF)`**
- set ON or OFF of LCD backlight


**`void LCD5110.inverse(const uint8_t ON|OFF)`**
- Set display mode to Inverse with ON or Normal with OFF


**`void LCD5110.printStr(const char *str)`**

**`void LCD5110.printStr((__FlashStringHelper *) *str)`**
- Print string on the LCD screen. The string can be either a c string array or string literal. Noted that both c string array and string literal will be loaded into SRAM during execution. To save memory usage, it is recommended to use F() macro or [PROGMEM](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/) variable when calling `LCD5110.printStr()`. See example for the usage.

**`void LCD5110.printImage(const char *image)`**
- Print image, image is an array[504] of pixels data. The method is expecting the image to be declared with PROGMEM modifier (that is, it get read from the program memory). See example for the usage.

## Extra
[Nokia5110 LCD Image Creator](https://www.e-tinkers.com/nokia5110-lcd-image-creator/) is a web application that provides a pixel canvas for creating logo image to be used by LCD5110. The app will generate a logo array that you can be used as an image in the sketch.

PCD8544 Controller Datasheet: https://www.e-tinkers.com/wp-content/uploads/2017/11/PCD8544_Controller_Datasheet.pdf

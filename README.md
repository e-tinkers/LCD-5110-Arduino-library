# LCD5110 Arduino library
This is a simple and easy-to-use Arduino library for LCD 5110 (a.k.a. Nokia 5110 or PCD8544) display module. Unlike other libraries that try to be swiss-knift for all LCD modules, this library targeting only LCD5110 with compact code and reliable SPI interface.

There is also a python library that shares the same APIs for Raspberry Pi [available](https://github.com/e-tinkers/LCD-5110-Raspberry-Library).

## Installation

Download the repository and move it into your Sketchbook/Libraries directory. For **Linux** machine, the directory is home/username/Sketchbook/Libraries/. For **Windows** or **Macintosh** machines, it is Documents/Arduino/Libraries/.

## Hardware interface

By default, the library assumed that the LCD module is connected with Arduino I/O pins as follow:

|**LCD Pin** |**Arduino I/O Pin** |
|:----------:|:------------------:|
|CLK|D13 (SCLK)|
|DN|D11 (MOSI)|
|DC|D10|
|RST|D9|
|SCE|D8|
|LED|D7|
|GND|GND|
|VCC|3v3|

* D7 connects to LED pin via a 220-ohm resistor to restrict the LED current.

In case you need to use alternative pins for connecting to the LCD module, you culd re-define the pin assignment using `#define` directive at the beginning of your Arduino sketch. See this example:

```
#define LED D5  // use D5 instead of default D7 for LED backlight
```

## API for LCD5110 library


**`LCD5110 lcd`**
- Create an instance called lcd of class LCD5110\. The class construct will:

    1. initialise GPIO and SPI ports;
    2. clear the screen and internal display memory
    3. set cursor to row 1, col 1
    4. set LCD display mode = Normal


**`void LCD5110.clear(void)`**
- Clear LCD screen and internal DDRAM, it is also set cursor to row 1, col 1


**`void LCD5110.cursor(uint8_t row, uint8_t col)`**
- Set LCD cursor to row (from 1 to 6), col (from 1 to 14)


**`void LCD5110.backlight(const uint8_t ON|OFF)`**
- set LCD backlight to ON or OFF


**`void LCD5110.inverse(const uint8_t ON|OFF)`**
- Set display mode to Inverse with ON or Normal with OFF


**`void LCD5110.printStr(const char *str)`**
- Print str[] array on screen


**`void LCD5110.printImage(const char *image)`**
- Print image[], image is an array[504] of pixels data

## Extra
[Nokia5110 LCD Image Creator](https://www.e-tinkers.com/nokia5110-lcd-image-creator/) is a web application that providea pixel canvas for creating logo image to be used by LCD5110. The app will generate a logo array that you can copy and paste into your sketch.

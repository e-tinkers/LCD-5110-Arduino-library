# LCD5110 Arduino library
This repository is an Arduino library for LCD 5110 (a.k.a. Nokia 5110 or PCD8544) display module. There is also a python library that shares the same APIs for Raspberry Pi [available](https://github.com/e-tinkers/LCD-5110-Raspberry-Library).

## Installation

Download the repository and move it into your Sketchbook/Libraries directory. For **Linux** machine, the directory is home/username/Sketchbook/Libraries/. For **Windows** or **Macintosh** machines, it is Documents/Arduino/Libraries/.

## Hardware interface

The LCD module is connected with Arduino I/O pins as follow:

LCD --- Arduino I/O pin  
CLK --- D13 (SCLK)  
DN --- D11 (MOSI)  
DC --- D10  
RST --- D9  
SCE --- D8  
LED --- D7  
GND --- GND  
VCC --- 3v3

* D7 connects to LED pin via a 220-ohm resistor to restrict the LED current.

## API for LCD5110 library


**LCD5110 lcd**
- Create an instance called lcd of class LCD5110\. The class construct will:

    1. initialise GPIO and SPI ports;
    2. clear the screen and internal display memory
    3. set cursor to row 1, col 1
    4. set LCD backlight = Off
    5. set LCD display mode = Normal


**void LCD5110.clear(void)**
- Clear LCD screen and internal DDRAM, it is also set cursor to row 1, col 1


**void LCD5110.cursor(unsigned char row, unsigned char col)**
- Set LCD cursor to row (from 1 to 6), col (from 1 to 14)


**void LCD5110.backlight(boolean true|false)**
- Set LCD backlight on (true) or off (false)


**void LCD5110.inverse(boolean true/false)**
- Set display mode to Inverse (true) or Normal (false)


**void LCD5110.printStr(unsigned char str[])**
- Print str[] array on screen


**void LCD5110.printImage(unsigned char image[])**
- Print image[], image is an array[504] of pixels data

## More information

For more information, please refer to my blog posts:
- [How to use LCD 5110 (PCD 8544) with Arduino](https://www.e-tinkers.com/2017/11/how-to-use-lcd-5110-pcd-8544-with-arduino/)
- [How to create Arduino Library from Arduino sketch](https://www.e-tinkers.com/2017/12/how-to-create-arduino-library-from-arduino-sketch/)
- [How to use LCD 5110 (PCD 8544) with Raspberry Pi](https://www.e-tinkers.com/2017/11/how-to-use-lcd-5110-pcd-8544-with-raspberry-pi/)

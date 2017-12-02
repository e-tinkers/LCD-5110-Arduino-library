/*
  LCD5110.h - A LCD5110 (PCD8544) display library
  Created by Henry Cheung, December 1, 2017.
  License: MIT
*/
#ifndef LCD5110_h
#define LCD5110_h

#include "Arduino.h"

class LCD5110
{
  public:
    LCD5110(void);
    void clear(void);
    void cursor(unsigned char row, unsigned char col);
    void backlight(boolean state);
    void inverse(boolean inv);
    void printStr(unsigned char str[]);
    void printImage(unsigned char image[]);
  private:
    void write(unsigned int mode, unsigned char data);
    boolean _inverse;

    const int CLK = 13; // Must connect to Arduino D13 (SPI SCLK) when using SPI library
    const int DN = 11;  // Must connect to Arduino D11 (SPI MOSI) when using SPI library
    const int DC = 10;
    const int RST = 9;
    const int SCE = 8;
    const int LED = 7;

    const int LCD_WIDTH = 84;
    const int LCD_HEIGHT = 48;
    const int CMD = LOW;
    const int DATA = HIGH;
    const int ON = HIGH;
    const int OFF = LOW;
};

#endif

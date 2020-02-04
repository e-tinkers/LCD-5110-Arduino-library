/*
  LCD5110.h - A LCD5110 (PCD8544) display library
  Created by Henry Cheung, December 1, 2017.
  License: MIT
*/
#ifndef LCD5110_h
#define LCD5110_h

#include "Arduino.h"

//spi pin assignment
#define CLK 13 // Must connect to Arduino D13 (SPI SCLK) when using SPI library
#define DN 11  // Must connect to Arduino D11 (SPI MOSI) when using SPI library
#define DC 10
#define RST 9
#define SCE 8
#define LED 7

#define ON HIGH
#define OFF LOW

class LCD5110
{
  public:
    LCD5110(void);
    void clear(void);
    void cursor(uint8_t row, uint8_t col);
    void backlight(const uint8_t state);
    void inverse(const uint8_t inv);
    void printStr(const char *str);
    void printImage(const char *image);
  private:
    void _write(const uint8_t mode, char data);
    uint8_t _inverse;
    const uint8_t LCD_WIDTH = 84;
    const uint8_t LCD_HEIGHT = 48;
    const uint8_t CMD = LOW;
    const uint8_t DATA = HIGH;
};

#endif

/*
  LCD5110.h - A LCD5110 (PCD8544) display library
  Created by Henry Cheung, December 1, 2017.
  License: MIT
*/
#ifndef LCD5110_h
#define LCD5110_h

#include "Arduino.h"
#include "SPI.h"

#define ON HIGH
#define OFF LOW
#define CMD LOW
#define DATA HIGH
#define LCD_WIDTH 84
#define LCD_HEIGHT 48

class LCD5110
{
  public:
    LCD5110(const uint8_t dc, const uint8_t led);
    void clear(void);
    void cursor(uint8_t row, uint8_t col);
    void backlight(const uint8_t state);
    void inverse(const uint8_t inv);
    void printStr(const char *str);
    void printImage(const char *image);
  private:
    void _write(const uint8_t mode, char data);
    uint8_t _inverse = OFF;
    uint8_t _DC;
    uint8_t _BACKLIGHT;
};

#endif

#include "LCD5110.h"

LCD5110::LCD5110(const uint8_t dc, const uint8_t led)
{
  _DC = dc;
  _BACKLIGHT = led;

  pinMode(_DC, OUTPUT);
  pinMode(_BACKLIGHT, OUTPUT);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);

  SPI.begin();    //set SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high.
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  _write(CMD, 0x21);  // Set Extended Command set
  _write(CMD, 0xb2);  // Set Vlcd to 6v (LCD Contrast)
  _write(CMD, 0x13);  // Set voltage bias system 1:48 (Viewing Angle)
  _write(CMD, 0x20);  // Set Normal Command set
  clear(); // Clear all display memory and set cursor to 1,1
  _write(CMD, 0x09);  // Set all pixels ON
  _write(CMD, 0x0c);  // Set display mode to Normal

}

void LCD5110::clear(void) {
  cursor(0,0);
  for (int pixel=(LCD_WIDTH * LCD_HEIGHT / 8); pixel > 0; pixel--) {
    _write(DATA, 0x00);
  }
}

void LCD5110::cursor(uint8_t row, uint8_t col) {
  if ( (row < 1 | row > LCD_HEIGHT / 8) | (col < 1 | col > LCD_WIDTH / 6)) {
    return;
  }
  _write(CMD, 0x40 | ( row - 1) );
  _write(CMD, 0x80 | ( col - 1) * 6 );
}

void LCD5110::_write(const uint8_t mode, char data) {
  digitalWrite(_SCE, LOW);
  digitalWrite(_DC, mode);  //HIGH = Data mode, LOW = Command mode
  if (mode == DATA & _inverse == ON) {
      data = ~ data;
  }
  SPI.transfer(data);
  digitalWrite(_SCE, HIGH);
}

void LCD5110::backlight(const uint8_t state) {
  digitalWrite(_BACKLIGHT, state);
}

void LCD5110::inverse(const uint8_t inv) {
  _inverse = inv;
}

void LCD5110::printImage(const char *image) {
  cursor(1,1);
  for (int i = 0; i < (LCD_WIDTH * LCD_HEIGHT / 8); i++) {
    _write(DATA, pgm_read_byte_near(image + i));
  }
}

void LCD5110::printStr(const char *str) {
  static const char FONT_TABLE [][5] PROGMEM = {
    { 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0x20, space
    { 0x00, 0x00, 0x5f, 0x00, 0x00 }, // 0x21, !
    { 0x00, 0x07, 0x00, 0x07, 0x00 }, // 0x22, "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // 0x23, #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // 0x24, $
    { 0x23, 0x12, 0x08, 0x64, 0x62 }, // 0x25, %
    { 0x36, 0x49, 0x55, 0x22, 0x50 }, // 0x26, &
    { 0x00, 0x05, 0x03, 0x00, 0x00 }, // 0x27, '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 }, // 0x28, (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 }, // 0x29, )
    { 0x14, 0x08, 0x3E, 0x08, 0x14 }, // 0x2a, *
    { 0x08, 0x08, 0x3E, 0x08, 0x08 }, // 0x2b, +
    { 0x00, 0x50, 0x30, 0x00, 0x00 }, // 0x2c, ,
    { 0x08, 0x08, 0x08, 0x08, 0x08 }, // 0x2d, -
    { 0x00, 0x60, 0x60, 0x00, 0x00 }, // 0x2e, .
    { 0x20, 0x10, 0x08, 0x04, 0x02 }, // 0x2f, /
    { 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0x30, 0
    { 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 0x31, 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 }, // 0x32, 2
    { 0x21, 0x41, 0x45, 0x4B, 0x31 }, // 0x33, 3
    { 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 0x34, 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 }, // 0x35, 5
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 }, // 0x36, 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 }, // 0x37, 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 }, // 0x38, 8
    { 0x06, 0x49, 0x49, 0x29, 0x1E }, // 0x39, 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 }, // 0x3a, :
    { 0x00, 0x56, 0x36, 0x00, 0x00 }, // 0x3b, ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 }, // 0x3c, <
    { 0x14, 0x14, 0x14, 0x14, 0x14 }, // 0x3d, =
    { 0x00, 0x41, 0x22, 0x14, 0x08 }, // 0x3e, >
    { 0x02, 0x01, 0x51, 0x09, 0x06 }, // 0x3f, ?
    { 0x32, 0x49, 0x59, 0x51, 0x3E }, // 0x40, @
    { 0x7E, 0x11, 0x11, 0x11, 0x7E }, // 0x41, A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // 0x42, B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // 0x43, C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C }, // 0x44, D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // 0x45, E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 }, // 0x46, F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A }, // 0x47, G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // 0x48, H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // 0x49, I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 }, // 0x4a, J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // 0x4b, K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 }, // 0x4c, L
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F }, // 0x4d, M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F }, // 0x4e, N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // 0x4f, O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 }, // 0x50, P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E }, // 0x51, Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 }, // 0x52, R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // 0x53, S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 }, // 0x54, T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F }, // 0x55, U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F }, // 0x56, V
    { 0x3F, 0x40, 0x38, 0x40, 0x3F }, // 0x57, W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // 0x58, X
    { 0x07, 0x08, 0x70, 0x08, 0x07 }, // 0x59, Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // 0x5a, Z
    { 0x00, 0x7F, 0x41, 0x41, 0x00 }, // 0x5b, [
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 }, // 0x5c, back slash
    { 0x00, 0x41, 0x41, 0x7F, 0x00 }, // 0x5d, ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 }, // 0x5e, ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 }, // 0x5f, _
    { 0x00, 0x01, 0x02, 0x04, 0x00 }, // 0x60, `
    { 0x20, 0x54, 0x54, 0x54, 0x78 }, // 0x61, a
    { 0x7F, 0x48, 0x44, 0x44, 0x38 }, // 0x62, b
    { 0x38, 0x44, 0x44, 0x44, 0x20 }, // 0x63, c
    { 0x38, 0x44, 0x44, 0x48, 0x7F }, // 0x64, d
    { 0x38, 0x54, 0x54, 0x54, 0x18 }, // 0x65, e
    { 0x08, 0x7E, 0x09, 0x01, 0x02 }, // 0x66, f
    { 0x0C, 0x52, 0x52, 0x52, 0x3E }, // 0x67, g
    { 0x7F, 0x08, 0x04, 0x04, 0x78 }, // 0x68, h
    { 0x00, 0x44, 0x7D, 0x40, 0x00 }, // 0x69, i
    { 0x20, 0x40, 0x44, 0x3D, 0x00 }, // 0x6a, j
    { 0x7F, 0x10, 0x28, 0x44, 0x00 }, // 0x6b, k
    { 0x00, 0x41, 0x7F, 0x40, 0x00 }, // 0x6c, l
    { 0x7C, 0x04, 0x18, 0x04, 0x78 }, // 0x6d, m
    { 0x7C, 0x08, 0x04, 0x04, 0x78 }, // 0x6e, n
    { 0x38, 0x44, 0x44, 0x44, 0x38 }, // 0x6f, o
    { 0x7C, 0x14, 0x14, 0x14, 0x08 }, // 0x70, p
    { 0x08, 0x14, 0x14, 0x18, 0x7C }, // 0x71, q
    { 0x7C, 0x08, 0x04, 0x04, 0x08 }, // 0x72, r
    { 0x48, 0x54, 0x54, 0x54, 0x20 }, // 0x73, s
    { 0x04, 0x3F, 0x44, 0x40, 0x20 }, // 0x74, t
    { 0x3C, 0x40, 0x40, 0x20, 0x7C }, // 0x75, u
    { 0x1C, 0x20, 0x40, 0x20, 0x1C }, // 0x76, v
    { 0x3C, 0x40, 0x30, 0x40, 0x3C }, // 0x77, w
    { 0x44, 0x28, 0x10, 0x28, 0x44 }, // 0x78, x
    { 0x0C, 0x50, 0x50, 0x50, 0x3C }, // 0x79, y
    { 0x44, 0x64, 0x54, 0x4C, 0x44 }, // 0x7a, z
    { 0x00, 0x08, 0x36, 0x41, 0x00 }, // 0x7b, {
    { 0x00, 0x00, 0x7f, 0x00, 0x00 }, // 0x7c, |
    { 0x00, 0x41, 0x36, 0x08, 0x00 }, // 0x7d, }
    { 0x10, 0x08, 0x08, 0x10, 0x08 }, // 0x7e, ~
    { 0x78, 0x46, 0x41, 0x46, 0x78 }  // 0x7f, DEL
  };
  int p = 0;
  while (str[p]!='\0') {
    if ( (str[p] >= 0x20) & (str[p] <= 0x7f) ) {
      for (int i = 0; i < 5; i++) {
        _write(DATA, pgm_read_byte_near(FONT_TABLE[str[p] - 32] + i));
      }
      _write(DATA, 0x00);
    }
    p++;
  }
}

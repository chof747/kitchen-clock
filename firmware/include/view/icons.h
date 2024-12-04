#ifndef ICONS_H
#define ICONS_H

#include <Arduino.h>

static const uint8_t iconTimer40x40[] PROGMEM = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 
  0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 
  0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x7E, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xE1, 0x80, 
  0x00, 0x0F, 0xFF, 0xF3, 0xC0, 0x00, 0x3F, 0xFF, 
  0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xC0, 0x00, 
  0xFF, 0x00, 0xFF, 0x80, 0x01, 0xFC, 0x00, 0x3F, 
  0x80, 0x01, 0xF8, 0x3C, 0x1F, 0x80, 0x03, 0xF0, 
  0x3C, 0x0F, 0xC0, 0x03, 0xE0, 0x3C, 0x07, 0xC0, 
  0x07, 0xC0, 0x3C, 0x03, 0xE0, 0x07, 0xC0, 0x3C, 
  0x03, 0xE0, 0x07, 0x80, 0x3C, 0x01, 0xE0, 0x07, 
  0x80, 0x3C, 0x01, 0xE0, 0x07, 0x80, 0x3C, 0x01, 
  0xE0, 0x07, 0x80, 0x3C, 0x01, 0xE0, 0x07, 0x80, 
  0x3C, 0x01, 0xE0, 0x07, 0x80, 0x3C, 0x01, 0xE0, 
  0x07, 0x80, 0x00, 0x01, 0xE0, 0x07, 0xC0, 0x00, 
  0x03, 0xE0, 0x07, 0xC0, 0x00, 0x03, 0xE0, 0x03, 
  0xE0, 0x00, 0x07, 0xC0, 0x03, 0xE0, 0x00, 0x07, 
  0xC0, 0x03, 0xF0, 0x00, 0x0F, 0xC0, 0x01, 0xF8, 
  0x00, 0x1F, 0x80, 0x00, 0xFE, 0x00, 0x7F, 0x00, 
  0x00, 0x7F, 0xC3, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 
  0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 
  0x07, 0xFF, 0xE0, 0x00, 0x00, 0x01, 0xFF, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t iconThermometer40x40[] PROGMEM = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 
  0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 
  0xFF, 0x80, 0x00, 0x00, 0x01, 0xE7, 0x80, 0x00, 
  0x00, 0x01, 0xE7, 0x80, 0x00, 0x00, 0x01, 0xE7, 
  0x80, 0x00, 0x00, 0x01, 0xE7, 0x80, 0x00, 0x00, 
  0x01, 0xE7, 0x80, 0x00, 0x00, 0x01, 0xE7, 0x80, 
  0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 
  0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 
  0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 
  0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 
  0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 
  0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x07, 
  0xFF, 0xE0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 
  0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 
  0xF0, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 
  0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 
  0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 
  0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 
  0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 
  0xE0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00, 
  0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0xFF, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
  
static const uint8_t iconHomeAutomation40x40[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 
  0x7E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 
  0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 
  0xE0, 0x00, 0x00, 0x0F, 0xC3, 0xF0, 0x00, 0x00, 
  0x3F, 0x81, 0xFC, 0x00, 0x00, 0x7F, 0x00, 0xFE, 
  0x00, 0x00, 0xFE, 0xFF, 0x3F, 0x00, 0x03, 0xF9, 
  0xFF, 0x9F, 0xC0, 0x07, 0xF3, 0xFF, 0xCF, 0xE0, 
  0x0F, 0xE3, 0xC3, 0xC7, 0xF0, 0x3F, 0xC7, 0x81, 
  0xE3, 0xF8, 0x3F, 0xC7, 0x81, 0xE3, 0xFC, 0x3F, 
  0xC7, 0x81, 0xE3, 0xFC, 0x3B, 0xC7, 0x81, 0xE3, 
  0xDC, 0x03, 0xC3, 0xC3, 0xC3, 0xC0, 0x03, 0xC3, 
  0xE7, 0xC3, 0xC0, 0x03, 0xC1, 0xE7, 0x83, 0xC0, 
  0x03, 0xC0, 0xFF, 0x03, 0xC0, 0x03, 0xC0, 0xFF, 
  0x03, 0xC0, 0x03, 0xC0, 0xFF, 0x03, 0xC0, 0x03, 
  0xC0, 0x3E, 0x03, 0xC0, 0x03, 0xC0, 0x7E, 0x03, 
  0xC0, 0x03, 0xC0, 0x7E, 0x03, 0xC0, 0x03, 0xC0, 
  0x7E, 0x03, 0xC0, 0x03, 0xC0, 0x00, 0x03, 0xC0, 
  0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0xFF, 0xFF, 
  0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 
  0x7F, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t iconSettings40x40[] PROGMEM = 
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 
  0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 
  0xFF, 0x80, 0x00, 0x00, 0x01, 0xE7, 0x80, 0x00, 
  0x01, 0xC3, 0xE7, 0xC3, 0x80, 0x03, 0xFF, 0xE7, 
  0xFF, 0xC0, 0x03, 0xFF, 0xE7, 0xFF, 0xC0, 0x07, 
  0xFF, 0xE7, 0xFF, 0xE0, 0x0F, 0xFF, 0x00, 0xFF, 
  0xF0, 0x0F, 0xBC, 0x7E, 0x7D, 0xF0, 0x1F, 0x81, 
  0xFF, 0x81, 0xF8, 0x1F, 0xC3, 0xFF, 0xC3, 0xF8, 
  0x0F, 0xF3, 0xFF, 0xCF, 0xF0, 0x07, 0xF7, 0xE7, 
  0xEF, 0xE0, 0x01, 0xF7, 0xC3, 0xEF, 0x80, 0x01, 
  0xE7, 0x81, 0xE7, 0x80, 0x01, 0xE7, 0x81, 0xE7, 
  0x80, 0x01, 0xF7, 0xC3, 0xEF, 0x80, 0x07, 0xF7, 
  0xE7, 0xEF, 0xE0, 0x0F, 0xF3, 0xFF, 0xCF, 0xF0, 
  0x1F, 0xC3, 0xFF, 0xC3, 0xF8, 0x1F, 0x81, 0xFF, 
  0x81, 0xF8, 0x0F, 0xBE, 0x7E, 0x7D, 0xF0, 0x0F, 
  0xFF, 0x00, 0xFF, 0xF0, 0x07, 0xFF, 0xE7, 0xFF, 
  0xE0, 0x03, 0xFF, 0xE7, 0xFF, 0xC0, 0x03, 0xFF, 
  0xE7, 0xFF, 0xC0, 0x01, 0xC3, 0xE7, 0xC3, 0x80, 
  0x00, 0x01, 0xE7, 0x80, 0x00, 0x00, 0x01, 0xFF, 
  0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 
  0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#endif // ICONS_H
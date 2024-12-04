#ifndef SETUP_DISPLAY_VIEWS_H
#define SETUP_DISPLAY_VIEWS_H

#include "config.h"

#include "tftdisplay.h"
#include "view/memory_icon.h"

#include "view/icons.h"

ModFirmWare::TFTDisplay display(DISPLAY_CS, DISPLAY_RS, DISPLAY_RST, DISPLAY_BKLT, INITR_BLACKTAB);

ModFirmWare::MemoryIcon iconTimer(40, 40, iconTimer40x40);
ModFirmWare::MemoryIcon iconThermometer(40, 40, iconThermometer40x40);
ModFirmWare::MemoryIcon iconHomeAutomation(40, 40, iconHomeAutomation40x40);
ModFirmWare::MemoryIcon iconSettings(40,40, iconSettings40x40);

#endif //SETUP_DISPLAY_VIEWS_H
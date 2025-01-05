#ifndef SETUP_MENUS_H
#define SETUP_MENUS_H

#include "view/icons.h"
#include "model/iconmenu_item.h"
#include "view/memory_icon.h"
#include "iconmenu_controller.h"

ModFirmWare::MemoryIcon iconTimer(40, 40, iconTimer40x40);
ModFirmWare::MemoryIcon iconThermometer(40, 40, iconThermometer40x40);
ModFirmWare::MemoryIcon iconHomeAutomation(40, 40, iconHomeAutomation40x40);
ModFirmWare::MemoryIcon iconSettings(40, 40, iconSettings40x40);

ModFirmWare::IconMenuItem mniTimer(&iconTimer, "Timer", nullptr);
ModFirmWare::IconMenuItem mniThermometer(&iconThermometer, "Temp.", nullptr);
ModFirmWare::IconMenuItem mniHomeAutomation(&iconHomeAutomation, "Home", nullptr);
ModFirmWare::IconMenuItem mniSettings(&iconSettings, "Setup", nullptr);

namespace KitchenClock
{

  void compileMenu(ModFirmWare::IconMenuController *menu,
                   ModFirmWare::Controller *timerCtrl,
                   ModFirmWare::Controller *thermoCtrl,
                   ModFirmWare::Controller *homeAutoCtrl,
                   ModFirmWare::Controller *settingsCtrl)
  //****************************************************************************
  {
      menu->addMenuItem(&mniTimer, timerCtrl);
      menu->addMenuItem(&mniThermometer, thermoCtrl);
      menu->addMenuItem(&mniHomeAutomation, homeAutoCtrl);
      menu->addMenuItem(&mniSettings, settingsCtrl);
  }

};

#endif // SETUP_MENUS_H
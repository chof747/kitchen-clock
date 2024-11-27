#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "buttons.h"

namespace ModFirmWare
{
  class RotaryEncoder;
  class GPIOButton;
  class TFTDisplay;
};

namespace KitchenClock
{

  class ControlUnit
  {
  public:
    ControlUnit(ModFirmWare::RotaryEncoder *rotaryEncoder,
                ModFirmWare::GPIOButton *rotaryButton,
                ModFirmWare::GPIOButton *modeButton,
                ModFirmWare::TFTDisplay *display);

  protected:
    virtual void onRotaryCw(long counter) = 0;
    virtual void onRotaryCCw(long counter) = 0;
    virtual void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type) = 0;
    virtual void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type) = 0;

    virtual void onAnyEvent() { }

    ModFirmWare::RotaryEncoder *rotaryEncoder;
    ModFirmWare::GPIOButton *rotaryButton;
    ModFirmWare::GPIOButton *modeButton;
    ModFirmWare::TFTDisplay *display;

    void takeOverControls();
  };
};

#endif // MAINCONTROLLER_H
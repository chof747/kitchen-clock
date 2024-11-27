#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "idleablecontroller.h"
#include "buttons.h"
#include "controlunit.h"

namespace KitchenClock
{

  class MainController : public ModFirmWare::IdleableController, protected ControlUnit
  {
  public:
    MainController(ModFirmWare::Controller *idleController,
                   ModFirmWare::RotaryEncoder *rotaryEncoder,
                   ModFirmWare::GPIOButton *rotaryButton,
                   ModFirmWare::GPIOButton *modeButton,
                   ModFirmWare::TFTDisplay *display);

    void activate() override;
    void loop() override;
    void deactivate() override;

  protected:
    void onRotaryCw(long counter);
    void onRotaryCCw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onAnyEvent();
  };
};

#endif // MAINCONTROLLER_H
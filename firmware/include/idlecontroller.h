#ifndef IDLECONTROLLER_H
#define IDLECONTROLLER_H

#include <controller.h>
#include "controlunit.h"

namespace ModFirmWare
{
  class WLan;
  class TFTDisplay;
  class Servo;
};

namespace KitchenClock
{
  using namespace ModFirmWare;

  class IdleController : public ModFirmWare::Controller, ControlUnit
  {
  public:
    IdleController(WLan *wifi, TFTDisplay *display, Servo *clockServo, time_t deepSleepTime,
                   RotaryEncoder *rotaryEncoder, GPIOButton *rotaryButton, GPIOButton *modeButton);

    void activate() override;
    void loop() override;
    void deactivate() override;
  
  protected:
    void onRotaryCw(long counter);
    void onRotaryCCw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);

  private:
    WLan *wifi;
    Servo *clockServo;
    time_t timeToDeepSleep;
    time_t idlingStartTime;

    void startDeepSleep();
    void startIdling();
    void endIdling();
  };

};

#endif // IDLECONTROLLER_H
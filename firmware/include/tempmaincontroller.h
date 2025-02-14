#ifndef TEMPONTROLLER_H
#define TEMPCONTROLLER_H

#include "idleablecontroller.h"
#include "controlunit.h"
#include "regions/tempmainregion.h"

namespace ModFirmWare
{
  class Mqtt;
};

namespace KitchenClock
{
  class TempProbe;
  class TempMonitorController;
  class TempMainController : public ModFirmWare::IdleableController, protected ControlUnit
  {
  public:
    TempMainController(ModFirmWare::Controller *idleController,
                   ModFirmWare::RotaryEncoder *rotaryEncoder,
                   ModFirmWare::GPIOButton *rotaryButton,
                   ModFirmWare::GPIOButton *modeButton,
                   TempProbe* ntc1,
                   TempProbe* ntc2,
                   ModFirmWare::Mqtt* mqtt,
                   ModFirmWare::TFTDisplay *display,
                   ModFirmWare::DisplayRegion::window_t window);

    void activate() override;
    void loop() override;
    void deactivate() override;

    void setMonitorController(TempMonitorController* monitor);

  protected:
    void onRotaryCw(long counter);
    void onRotaryCCw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onTempUpdate();
    void onAnyEvent();

  private:
    TempMainRegion region;
    ModFirmWare::Mqtt* mqtt;
    bool calibration;

    TempProbe* ntcProbe1;
    TempProbe* ntcProbe2;
    TempMonitorController* monitor;

    void sendResistanceTemperature(uint8_t ix, float t, float r);

  };
};

#endif // TEMPCONTROLLER_H
#ifndef KITCHENCLOCK_TEMPMONITORCONTROLLER_H
#define KITCHENCLOCK_TEMPMONITORCONTROLLER_H

#include "idleablecontroller.h"
#include "controlunit.h"
#include "regions/tempmonitorregion.h"

namespace ModFirmWare
{
  class Mqtt;
  class Servo;
};

namespace KitchenClock
{
  class TempProbe;

  class TempMonitorController : public ModFirmWare::IdleableController, protected ControlUnit
  {
  public:
    TempMonitorController(ModFirmWare::Controller *idleController,
                       ModFirmWare::RotaryEncoder *rotaryEncoder,
                       ModFirmWare::GPIOButton *rotaryButton,
                       ModFirmWare::GPIOButton *modeButton,
                       ModFirmWare::Mqtt *mqtt,
                       ModFirmWare::TFTDisplay *display,
                       ModFirmWare::Servo *servo,
                       ModFirmWare::DisplayRegion::window_t window);

    void activate() override;
    void setTempProbe(TempProbe* probe);
    void loop() override;
    void deactivate() override;

  protected:
    void onRotaryCw(long counter);
    void onRotaryCCw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onTempUpdate(float temperature);
    void onAnyEvent();

  private:
    bool settingMode;
    float oldTarget;

    TempProbe* ntcProbe;
    TempMonitorRegion region;
    ModFirmWare::Servo* servo;
    ModFirmWare::Mqtt* mqttClient;

    void updateTarget();
    void updateServo();
    void updateRange();

    void activateSettingsMode();
    void deactivateSettingsMode(bool cancel = false);
    void deactivateTemperatureTarget();
    void adjustServoRange(float target);
  };
};

#endif // KITCHENCLOCK_TEMPMONITORCONTROLLER_H
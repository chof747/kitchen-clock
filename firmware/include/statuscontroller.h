#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include <controller.h>
#include "regions/statusregion.h"

namespace ModFirmWare
{
  class PowerManagement;
  class WLan;
  class SensorComponent;
  class Mqtt;
  class TFTDisplay;
};

namespace KitchenClock
{
  class StatusController : ModFirmWare::Controller
  {
  public:
    StatusController(ModFirmWare::PowerManagement *pwrMgmt, 
    ModFirmWare::WLan *wlan, ModFirmWare::Mqtt* mqtt, 
    ModFirmWare::TFTDisplay* display, ModFirmWare::DisplayRegion::window_t window)
        : pwrMgmt(pwrMgmt), wlan(wlan), mqtt(mqtt), display(display), region(window, display) {}

    void activate() override;
    void loop() override;
    void deactivate() override;

  protected:

    void getPowerManagementUpdate(ModFirmWare::SensorComponent* s);

  private:

    int getBatteryPercentage(long v);

    StatusRegion region;
    ModFirmWare::PowerManagement *pwrMgmt;
    ModFirmWare::WLan *wlan;
    ModFirmWare::Mqtt* mqtt;
    ModFirmWare::TFTDisplay* display;
  };
};

#endif // STATUSCONTROLLER_H
#ifndef STATUSREGION_H
#define STATUSREGION_H

#include <Arduino.h>
#include "display_region.h"

namespace ModFirmWare
{
  class LogEngine;
}

namespace KitchenClock
{

  class StatusRegion : public ModFirmWare::DisplayRegion
  {
  public:
    StatusRegion(ModFirmWare::DisplayRegion::window_t window, ModFirmWare::TFTDisplay* display)
        : ModFirmWare::DisplayRegion(window, display), anythingNew(false), 
        powered(false), connected(false), batteryPercent(250) {}

    void update(bool blink) override;
    void setBatteryPercent(const uint8_t batteryPercent);
    void setPowered(const bool powered);
    void setCharging(const bool charging);
    void setWLanConnectivity(const bool connected);

  protected:
    bool isUpdated() const override;

  private:

    int getBatteryIndicator();

    void drawBatteryIndicator(int startx);
    void drawPoweredIndicator(int startx);
    void doBlinking(bool blinkstate);
    void doBlinkBatteryIndicator(bool blinkstate);

    uint8_t batteryPercent;
    bool connected;
    bool powered;
    bool charging;
    bool anythingNew;

    ModFirmWare::LogEngine* logger;
  };
};

#endif // STATUSREGION_H

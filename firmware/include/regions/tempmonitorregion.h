#ifndef KITCHENCLOCK_TEMPMONITORREGION_H
#define KITCHENCLOCK_TEMPMONITORREGION_H

#include "display_region.h"
#include "config.h"

namespace ModFirmWare
{
  class LogEngine;
}

namespace KitchenClock
{
  class TempProbe;

  class TempMonitorRegion : public ModFirmWare::DisplayRegion
  {
  public:

    enum range_t
    {
      OK = 0,
      NEAR = 1,
      OFF = 2
    };

    TempMonitorRegion(ModFirmWare::TFTDisplay *display,  ModFirmWare::DisplayRegion::window_t window);

    void updateCanvas() override;

    void setProbe(TempProbe* probe);
    void setRange(range_t range);
    void triggerUpdate() { newvalues = true; }

    void enableSettingsMode(const bool setting); 

  protected:
    bool isUpdated() const;

  private:
    TempProbe* probe;
    bool newvalues;
    bool settingsMode;
    range_t range;

  };
}

#endif // KITCHENCLOCK_TEMPMONITORREGION_H
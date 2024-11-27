#ifndef STARTREGION_H
#define STARTREGION_H

#include "display_region.h"

namespace ModFirmWare
{
  class LogEngine;
}

namespace KitchenClock
{

  class StartRegion : public ModFirmWare::DisplayRegion
  {
  public:
    StartRegion(ModFirmWare::TFTDisplay *display, const char *startImageFileName);

    void update(bool blink) override;

  protected:
    bool isUpdated() const { return done; }

  private:
    bool done;

    ModFirmWare::imgbuffer_t buffer;
    ModFirmWare::DisplayRegion::window_t imgSize;

    ModFirmWare::LogEngine* logger;

  };
}

#endif // STARTREGION_H
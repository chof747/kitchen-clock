#include "regions/tempmonitorregion.h"
#include "regions/regionshelper.h"
#include "tempprobe.h"

using namespace KitchenClock;
using namespace ModFirmWare;

TempMonitorRegion::TempMonitorRegion(ModFirmWare::TFTDisplay *display,
                                     ModFirmWare::DisplayRegion::window_t window)
    : DisplayRegion(window, display),
      settingsMode(false),
      newvalues(false),
      probe(nullptr),
      range(range_t::OFF)
//******************************************************************************
{
}

void KitchenClock::TempMonitorRegion::updateCanvas()
//******************************************************************************
{
  if (newvalues)
  {
    auto *gfx = display();
    gfx->fillScreen(0); // Clear screen

    if (settingsMode)
    {

    }
    else
    {
      char buffer[50];
      bool withdegrees = false;
      if (probe->isReadingValid())
      {
        float t = probe->getTemperatureC();
        sprintf(buffer, "%.1f",t);
        withdegrees = true;
      }
      else
      {
        sprintf(buffer, "no value");
      }

      printBlock(this, buffer, 2, 0, 30, withdegrees, true);
    }
  }

  newvalues = false;
}

void TempMonitorRegion::setProbe(TempProbe *probe)
//******************************************************************************
{
  this->probe = probe;
}

void TempMonitorRegion::setRange(range_t range)
//******************************************************************************
{
  this->range = range;
}

void TempMonitorRegion::enableSettingsMode(const bool setting)
//******************************************************************************
{
  settingsMode = setting;
}

bool TempMonitorRegion::isUpdated() const
//******************************************************************************
{
  return newvalues;
}

#include "regions/tempmainregion.h"
#include "tftdisplay.h"
#include "logengine.h"
#include <Arduino.h>
#include "tempprobe.h"
#include "regions/regionshelper.h"

// #include <Fonts/FreeSans9pt7b.h>  // Include 10px font
// #include "fonts/FreeSans7pt7b.h" // Include 20px font


using namespace KitchenClock;
#define LOGTAG "TempMainRegion"

#define ACCURACY 1e-4

TempMainRegion::TempMainRegion(ModFirmWare::TFTDisplay *display, ModFirmWare::DisplayRegion::window_t window)
    : DisplayRegion(window, display, "TempMainRegion"), newvalues(false), calibration(false), selectedProbeIx(-1)
//****************************************************************************************
{
  for (int i = 0; i < NUM_PROBES; ++i)
  {
    probes[i] = nullptr;
  }
}

void KitchenClock::TempMainRegion::updateCanvas()
//****************************************************************************************
{
  if (newvalues)
  {
    auto *gfx = display();
    gfx->fillScreen(0); // Clear screen

    int y = 2;

    for (int i = 0; i < NUM_PROBES; ++i)
    {
      if (probes[i]->isReadingValid())
      {
        if (!calibration)
        {
          printTempBlock(i);
        }
        else
        {
          printCalibrationBlock(i);
        }
      }
    }

    newvalues = false;
  }
}

void TempMainRegion::setProbe(uint ix, TempProbe *probe)
//****************************************************************************************
{
  if (ix < NUM_PROBES)
  {
    probes[ix] = probe;
  }
}

void TempMainRegion::enableCalibrationMode(const bool calibration)
//****************************************************************************************
{
  if (calibration != this->calibration)
  {
    this->calibration = calibration;
    newvalues = true;
  }
}

int TempMainRegion::selectNextProbe()
//****************************************************************************************
{
  int pix;
  if ((NUM_PROBES - 1) > selectedProbeIx)
  {
    pix = selectedProbeIx + 1;
  }
  else
  {
    pix = 0;
  }

  return checkIfProbeCanBeSelected(pix);
}

int TempMainRegion::selectPrevProbe()
//****************************************************************************************
{
  int pix;

  if (0 < selectedProbeIx)
  {
    pix = selectedProbeIx - 1;
  }
  else
  {
    pix = NUM_PROBES - 1;
  }

  return checkIfProbeCanBeSelected(pix);
}

void TempMainRegion::unselectProbes()
//****************************************************************************************
{
  selectedProbeIx=-1;
  newvalues=true;  
}

bool TempMainRegion::isUpdated() const
//****************************************************************************************
{
  return newvalues;
}

void TempMainRegion::printCalibrationBlock(uint ix)
//****************************************************************************************
{
  char buffer[255];

  int y = (ix == 0) ? 2 : height() / 2 + 2;

  float r = probes[ix]->getResistance();
  float t = probes[ix]->getTemperatureC();

  sprintf(buffer, "R%d= %.3fk", ix + 1, r / 1000);
  y = printBlock(this, buffer, 1, 2, y, false);
  sprintf(buffer, "T%d = %.1f", ix, t);
  y = printBlock(this, buffer, 0, 10, y + 3, true);
}

const int TempMainRegion::checkIfProbeCanBeSelected(const int pix)
//****************************************************************************************
{
  if (probes[pix]->isReadingValid())
  {
    newvalues=true;
    return (selectedProbeIx=pix);
  }
  else
  {
    return selectedProbeIx;
  }
}
void TempMainRegion::printTempBlock(uint ix)
//****************************************************************************************
{
  auto *gfx = display();
  int y = (ix == 0) ? 2 : height() / 2 + 2;

  if (ix == selectedProbeIx)
  {
    gfx->fillRect(0,y, width(), height() / 2 - 4, ST7735_WHITE);
    gfx->setTextColor(ST7735_BLACK);
  }
  else
  {
    gfx->setTextColor(ST7735_WHITE);    
  }

  char buffer[255];

  float r = probes[ix]->getResistance();
  float t = probes[ix]->getTemperatureC();

  sprintf(buffer, "T%d = %.1f", ix + 1, t);
  y = printBlock(this, buffer, 1, 10, y, true);
  sprintf(buffer, "R%d = %.1f Ohm", ix, r);
  y = printBlock(this, buffer, 0, 15, y + 3, false);
}
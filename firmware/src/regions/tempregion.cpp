#include "regions/tempregion.h"
#include "tftdisplay.h"
#include "logengine.h"
#include <Arduino.h>
#include "regions/tempregion.h"

// #include <Fonts/FreeSans9pt7b.h>  // Include 10px font
// #include "fonts/FreeSans7pt7b.h" // Include 20px font
#include "fonts/tahoma12pt.h"
#include "fonts/tahoma7pt.h"
#include "regions/tempregion.h"

using namespace KitchenClock;
#define LOGTAG "tempregion"

#define ACCURACY 1e-4

TempRegion::TempRegion(ModFirmWare::TFTDisplay *display, ModFirmWare::DisplayRegion::window_t window)
    : DisplayRegion(window, display, "tempregion"),
      temp1(MAXFLOAT), temp2(MAXFLOAT), r1(MAXFLOAT), r2(MAXFLOAT), newvalues(false),
      calibration(false)
//****************************************************************************************
{
}
void KitchenClock::TempRegion::updateCanvas()
//****************************************************************************************
{
  if (newvalues)
  {
    auto *gfx = display();
    gfx->fillScreen(0); // Clear screen

    int y = 2;

    logger->debug(LOGTAG, "Temp1 : %.2f (R= %0.2f)", temp1, r1);
    if (abs(MAXFLOAT - r1) > ACCURACY)
    {
      if (!calibration)
      {
        printTempBlock(temp1, r1, 1);
      }
      else
      {
        printCalibrationBlock(temp1, r1, 1);
      }
    }

    logger->debug(LOGTAG, "Temp2 : %.2f (R= %0.2f)", temp2, r2);
    if (abs(MAXFLOAT - r2) > ACCURACY)
    {
      if (!calibration)
      {
        printTempBlock(temp2, r2, 2);
      }
      else
      {
        printCalibrationBlock(temp2, r2, 2);
      }
    }

    newvalues = false;
  }
}

void TempRegion::setTemperature1(const float temp)
//****************************************************************************************
{
  temp1 = setValueIfNew(temp1, temp);
}

void TempRegion::setTemperature2(const float temp)
//****************************************************************************************
{
  temp2 = setValueIfNew(temp2, temp);
}

void TempRegion::setResistance1(const float r)
//****************************************************************************************
{
  r1 = setValueIfNew(r1, r);
}

void TempRegion::setResistance2(const float r)
//****************************************************************************************
{
  r2 = setValueIfNew(r2, r);
}

void TempRegion::enableCalibrationMode(const bool calibration)
//****************************************************************************************
{
  if (calibration != this->calibration)
  {
    this->calibration = calibration;
    newvalues = true;
  }
}

bool TempRegion::isUpdated() const
//****************************************************************************************
{
  return newvalues;
}

float TempRegion::setValueIfNew(const float oldvalue, const float newvalue)
//****************************************************************************************
{
  float value = oldvalue;
  if (abs(oldvalue - newvalue) > ACCURACY)
  {
    value = newvalue;
    this->newvalues = true;
    // logger->debug(LOGTAG, "Reset value. Values are %s", newvalues ? "NEW" : "OLD");
  }

  return value;
}

void TempRegion::printCalibrationBlock(float t, float r, int ix)
//****************************************************************************************
{
  char buffer[255];

  int y = (ix == 1) ? 2 : height() / 2 + 2;

  sprintf(buffer, "R%d= %.3fk", ix, r / 1000);
  y = printBlock(buffer, true, 2, y, false);
  sprintf(buffer, "T%d = %.1f", ix, t);
  y = printBlock(buffer, false, 10, y + 3, true);  

}

void TempRegion::printTempBlock(float t, float r, int ix)
//****************************************************************************************
{
  char buffer[255];
  int y = (ix == 1) ? 2 : height() / 2 + 2;

  sprintf(buffer, "T%d = %.1f", ix, t);
  y = printBlock(buffer, true, 10, y, true);

  sprintf(buffer, "R%d = %.1f Ohm", ix, r);
  y = printBlock(buffer, false, 15, y + 3, false);
}

int TempRegion::printBlock(const char *buffer, bool large, int x, int y, bool withDegree, const char *unit)
//****************************************************************************************
{
  auto *gfx = display();
  gfx->setFont((large) ? &tahoma12pt8b : &tahoma7pt8b);
  int fh = getTextHeight(buffer);
  gfx->setCursor(x, y + fh);
  // logger->debug(LOGTAG, "y1 = %d", gfx->getCursorY());
  gfx->print(buffer);
  if (withDegree)
  {
    gfx->write(176);
    gfx->print(unit);
  }
  return y + fh;
}

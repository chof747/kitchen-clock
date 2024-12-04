#include "regions/statusregion.h"
#include "tftdisplay.h"
#include "logengine.h"

#define BATTERY_IND_HEIGHT 8
#define BATTERY_IND_WIDTH 17
#define POWERED_IND_HEIGHT 8
#define POWERED_IND_WIDTH 8
#define BATTERY_IND_COLOR ST7735_BLACK
#define BACKGROUND_COLOR ST7735_YELLOW
#define COLOR_GREY 0x7BEF

#define BATTERY_POS_FROM_RIGHT 19

#define LOGTAG "statusr"

using namespace KitchenClock;

bool StatusRegion::isUpdated() const
//****************************************************************************************
{
  return anythingNew;
}

void StatusRegion::updateCanvas()
//****************************************************************************************
{
  Adafruit_GFX *tft = display();

  tft->fillRect(0, 0, width(), height(), BACKGROUND_COLOR);
  drawBatteryIndicator(width() - BATTERY_POS_FROM_RIGHT);
  if (powered)
  {
    drawPoweredIndicator(width() - (BATTERY_POS_FROM_RIGHT + POWERED_IND_WIDTH + 1));
  }

  anythingNew = false;
}

void StatusRegion::setBatteryPercent(const uint8_t batteryPercent)
//****************************************************************************************
{
  if (batteryPercent != this->batteryPercent)
  {
    this->batteryPercent = batteryPercent;
    anythingNew = true;
  }
}

void StatusRegion::setCharging(const bool charging)
//****************************************************************************************
{
  if (charging != this->charging)
  {
    this->charging = charging;
    blinking = this->charging;
  }
}

void StatusRegion::setPowered(const bool powered)
//****************************************************************************************
{
  if (powered != this->powered)
  {
    this->powered = powered;
    anythingNew = true;
  }
}

void StatusRegion::setWLanConnectivity(const bool connected)
//****************************************************************************************
{
  if (connected != this->connected)
  {
    this->connected = connected;
    anythingNew = true;
  }
}

int StatusRegion::getBatteryIndicator()
//****************************************************************************************
{
  return (batteryPercent > 75) ? 4 : (batteryPercent > 50) ? 3
                                 : (batteryPercent > 25)   ? 2
                                 : (batteryPercent > 5)    ? 1
                                                           : 0;
}

void StatusRegion::drawBatteryIndicator(int startx)
//****************************************************************************************
/*
   Schematic image:

   ###############
   #             #
   # ## ## ## ## ###
   # ## ## ## ## ###
   # ## ## ## ## ###
   # ## ## ## ## ###
   #             #
   ###############

*/
{
  int starty = (height() - BATTERY_IND_HEIGHT) / 2;

  if (0 > starty)
  {
    return;
  }

  // draw the big rect for battery body
  display()->drawRect(startx, starty, 15, 8, BATTERY_IND_COLOR);
  // draw the small rect for battery pole
  display()->drawRect(startx + 15, starty + 2, 2, 4, BATTERY_IND_COLOR);

  int indicator = getBatteryIndicator();

  for (int i = 0; i < indicator; ++i)
  {
    display()->drawRect(startx + 2 + i * 3, starty + 2, 2, 4, BATTERY_IND_COLOR);
  }
}

void KitchenClock::StatusRegion::drawPoweredIndicator(int startx)
//****************************************************************************************
/*
    schematic image:
      ###
     #######
    #####***
    #####
    #####
    ########
     ####***
      ###
*/
{
  int starty = (height() - POWERED_IND_HEIGHT) / 2;
  if (0 > starty)
  {
    return;
  }

  display()->fillRect(startx + 2, starty, 3, 8, BATTERY_IND_COLOR);
  display()->drawLine(startx + 1, starty + 1, startx + 1, starty + 6, BATTERY_IND_COLOR);
  display()->drawLine(startx, starty + 2, startx, starty + 5, BATTERY_IND_COLOR);

  display()->drawLine(startx + 5, starty + 1, startx + 7, starty + 1, BATTERY_IND_COLOR);
  display()->drawLine(startx + 5, starty + 2, startx + 7, starty + 2, COLOR_GREY);

  display()->drawLine(startx + 5, starty + 5, startx + 7, starty + 5, BATTERY_IND_COLOR);
  display()->drawLine(startx + 5, starty + 6, startx + 7, starty + 6, COLOR_GREY);
}

void StatusRegion::doBlinking(bool blinkstate)
//****************************************************************************************
{
  doBlinkBatteryIndicator(blinkstate);
}

void StatusRegion::doBlinkBatteryIndicator(bool blinkstate)
//****************************************************************************************
{
  int starty = (height() - BATTERY_IND_HEIGHT) / 2;

  if (0 > starty)
  {
    return;
  }

  int indicatormax = getBatteryIndicator() - 1;
  int startx = width() - BATTERY_POS_FROM_RIGHT;

  if (0 <= indicatormax)
  {
    display()->drawRect(startx + 2 + indicatormax * 3, starty + 2, 2, 4,
                        (blinkstate) ? BACKGROUND_COLOR : BATTERY_IND_COLOR);
  }
}
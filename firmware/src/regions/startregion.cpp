#include "regions/startregion.h"
#include "tftdisplay.h"
#include "display_helper.h"
#include "logengine.h"
#include "Fonts/FreeSansBold9pt7b.h"

using namespace KitchenClock;
#define LOGTAG "startregion"

StartRegion::StartRegion(ModFirmWare::TFTDisplay *display, const char *startImageFileName)
    : DisplayRegion(ModFirmWare::DisplayRegion::window_t({
                      x : 0,
                      y : 0,
                      width : display->width(),
                      height : display->height()
                    }),
                    display),
      done(false), buffer(nullptr), imgSize()
//****************************************************************************************
{
  logger = ModFirmWare::LogEngine::getInstance();

  if (nullptr != display)
  {
    setWindow(display->getWindow());

    imgSize = getPictureDimensions(startImageFileName);

    if (0 != imgSize.width && 0 != imgSize.height)
    {
      buffer = display->loadImageFromSPIFFS(
          startImageFileName, imgSize.width, imgSize.height);

      logger->debug(LOGTAG, "Read image with dimension (w: %d, h:%d)", imgSize.width, imgSize.height);

      if (nullptr != buffer)
      {
        done = false;
        return;
      }
      else
      {
        logger->error(LOGTAG, "Could not read file %s", startImageFileName);
      }
    }
    else
    {
      logger->error(LOGTAG, "Could not parse %s filename", startImageFileName);
    }
  }

  done = true;
}
void KitchenClock::StartRegion::updateCanvas()
//****************************************************************************************
{
  if (!done)
  {
    int16_t x,y;
    uint16_t w,h;

    logger->info(LOGTAG, "Showing image");
    display()->setFont(&FreeSansBold9pt7b);
    display()->getTextBounds("Kitchen",0,0,&x,&y,&w,&h);

    display()->drawRGBBitmap(0,0,buffer.get(), imgSize.width, imgSize.height);

    display()->setTextSize(0);
    display()->setCursor(imgSize.width, 16);
    display()->print("Kitchen");
    display()->setCursor(imgSize.width, 20 + h + 2);
    display()->print("Clock");
    display()->setFont();
    display()->setCursor(imgSize.width+10, 20 + h*2+6);
    display()->print(VERSION);
    display()->setCursor(imgSize.width+10, 20 + h*2+6 + 10);
    display()->print("by chof");

    done = true;
    buffer.release();
  }
}
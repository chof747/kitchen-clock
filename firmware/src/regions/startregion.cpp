#include "regions/startregion.h"
#include "tftdisplay.h"
#include "display_helper.h"
#include "logengine.h"

using namespace KitchenClock;
#define LOGTAG "startregion"

StartRegion::StartRegion(ModFirmWare::TFTDisplay *display, const char *startImageFileName)
    : DisplayRegion(ModFirmWare::DisplayRegion::window_t(), display),
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
void KitchenClock::StartRegion::update(bool blink)
//****************************************************************************************
{
  if (!done)
  {
    //drawImage(buffer, imgSize.width, imgSize.height);
    display()->drawRGBBitmap(0,0,buffer.get(), imgSize.width, imgSize.height);
    done = true;
    buffer.release();
  }
}
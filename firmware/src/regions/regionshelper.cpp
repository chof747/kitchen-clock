#include "regions/regionshelper.h"
#include "fonts/tahoma12pt.h"
#include "fonts/tahoma18pt.h"
#include "fonts/tahoma7pt.h"
#include "logengine.h"

const GFXfont* fonts[] = { &tahoma7pt8b, &tahoma12pt8b, &tahoma18pt8b };

int printBlock(ModFirmWare::DisplayRegion* region, const char *buffer, int size, int x, int y, bool withDegree, bool centered, const char *unit)
//****************************************************************************************
{
  ModFirmWare::LogEngine* logger = ModFirmWare::LogEngine::getInstance();

  auto* gfx = region->display();
  gfx->setFont(fonts[size]);
  char unittext[3] = "";
  if (0 != strcmp("", unit))
  {
    unittext[0] = 176;
    unittext[1] = unit[0];
    unittext[2] = 0;
  }
  int fh = region->getTextHeight(buffer);
  if (centered)
  {
    x = (gfx->width() - region->getTextWidth(buffer) - region->getTextWidth(unittext)) / 2;
    logger->debug("HLPER", "text : %d, unit: %d", region->getTextWidth(buffer), region->getTextWidth(unittext));
    logger->debug("HLPER", "x = %d", x);
  }
  gfx->setCursor(x, y + fh);
  // logger->debug(LOGTAG, "y1 = %d", gfx->getCursorY());
  gfx->print(buffer);
  if (withDegree)
  {
    gfx->write(176);
    gfx->print(unit);
  }
  else
  {
    gfx->print(unit);
  }
  return y + fh;
}

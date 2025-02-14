#ifndef REGIONSHELPER_H
#define REGIONSHELPER_H

#include "display_region.h"

int printBlock(ModFirmWare::DisplayRegion* region, const char *buffer, int size, int x, int y, bool withDegree, bool centered = false, const char *unit = "C");

#endif

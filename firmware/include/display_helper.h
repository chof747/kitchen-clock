#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

#include "display_region.h"
#include <string>
#include <stdexcept>

namespace KitchenClock
{
  const ModFirmWare::DisplayRegion::window_t getPictureDimensions(const char *filename)
  {

      ModFirmWare::DisplayRegion::window_t window({
        x : 0,
        y : 0,
        width : 0,
        height : 0
      });

    std::string fname(filename);
    size_t underscore_pos = fname.rfind('_');
    size_t x_pos = fname.rfind('x');
    size_t dot_pos = fname.rfind('.');

    if (underscore_pos == std::string::npos ||
        x_pos == std::string::npos ||
        dot_pos == std::string::npos ||
        underscore_pos >= x_pos ||
        x_pos >= dot_pos)
    {
      //in case of error return an empty window
      return window;
    }

    try
    {
      int w = std::stoi(fname.substr(underscore_pos + 1, x_pos - underscore_pos - 1));
      int h = std::stoi(fname.substr(x_pos + 1, dot_pos - x_pos - 1));

      window.width = w;
      window.height = h;
    }
    catch (const std::exception &)
    {
     //in case of wrongly formatted number, return an empty window
     return window;
    }

    return window;
  }

};

#endif // DISPLAY_HELPER_H

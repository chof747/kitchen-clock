#ifndef TEMPREGION_H
#define TEMPREGION_H

#include "display_region.h"

namespace ModFirmWare
{
  class LogEngine;
}

namespace KitchenClock
{

  class TempRegion : public ModFirmWare::DisplayRegion
  {
  public:
    TempRegion(ModFirmWare::TFTDisplay *display,  ModFirmWare::DisplayRegion::window_t window);

    void updateCanvas() override;

    void setTemperature1(const float temp);
    void setTemperature2(const float temp);
    void setResistance1(const float r);
    void setResistance2(const float r);
    void forceupdate() { newvalues = true; }

    void enableCalibrationMode(const bool calibration); 

  protected:
    bool isUpdated() const;

  private:
    float temp1, temp2, r1, r2;
    bool newvalues;
    bool calibration;

    float setValueIfNew(const float oldvalue, const float newvalue);


    void printTempBlock(float t, float r, int ix);
    void printCalibrationBlock(float t, float r, int ix);

    int printBlock(const char* buffer, bool large, int x, int y, bool withDegree, const char* unit = "C");
  };
}

#endif // TEMPREGION_H
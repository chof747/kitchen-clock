#ifndef TEMP_PROBE_H
#define TEMP_PROBE_H

#include "ntcsensor.h"
#include <limits>

#define NAN_FLOAT std::numeric_limits<float>::quiet_NaN()

namespace ModFirmWare
{
  class Ads1115Sensor;
};

namespace KitchenClock
{
  class TempProbe: public ModFirmWare::NTCSensor
  {
  public:
    TempProbe(ModFirmWare::Ads1115Sensor* ads, uint8_t channel, double alpha, double beta, double gamma);

    void setTarget(float targetTemperature);
    void changeTargetBy(float increment);
    inline const uint getIndex() const { return index; }
    inline const float getTarget() const { return (targetEnabled) ? target : NAN_FLOAT; };
    void enableTarget(bool enable);
    inline const bool isTargetEnabled() const { return targetEnabled; }

  private:
    float target;
    bool targetEnabled;
    uint index;


  };
};

#endif //TEMP_PROBE_H
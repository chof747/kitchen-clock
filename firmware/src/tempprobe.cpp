#include "tempprobe.h"
#include "config.h"

using namespace KitchenClock;

TempProbe::TempProbe(ModFirmWare::Ads1115Sensor *ads,
                     uint8_t channel,
                     double alpha,
                     double beta,
                     double gamma)
    : NTCSensor(ads, channel, alpha, beta, gamma),
      target(NAN_FLOAT), targetEnabled(false)
//******************************************************************************
{
  //hard coded here for the sake of simplicity
  if (PRB_00_CHL == channel)
  {
    index = 1;
  }
#ifdef PRB_01_CHL
  else if (PRB_01_CHL == channel)
  {
    index = 2;
  }
#endif
#ifdef PRB_02_CHL
  else if (PRB_02_CHL == channel)
  {
    index = 3;
  }
#endif
#ifdef PRB_03_CHL
  else if (PRB_03_CHL == channel)
  {
    index = 4;
  }
#endif
  else 
  {
    index = 0;
  }
}

void TempProbe::setTarget(float targetTemperature)
//******************************************************************************
{
  target = targetTemperature;
}

void TempProbe::changeTargetBy(float increment)
//******************************************************************************
{
  target += increment;
}

void TempProbe::enableTarget(bool enable)
//******************************************************************************
{
  targetEnabled = enable;
}

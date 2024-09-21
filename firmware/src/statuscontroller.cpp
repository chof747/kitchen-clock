#include "statuscontroller.h"
#include "powermanagement.h"
#include "logengine.h"
#include "mqtt.h"
#include <functional>
#include "tftdisplay.h"

#include "config.h"

using namespace KitchenClock;

#define LOGTAG "status"

void StatusController::activate()
//*****************************************************************************
{
  display->registerRegion(&region);
  pwrMgmt->setUpdateCallback([this](ModFirmWare::SensorComponent *s)
                             { this->getPowerManagementUpdate(s); });
  pwrMgmt->measureNow();
}

void StatusController::deactivate()
//*****************************************************************************
{
  display->unregisterRegion(&region);
}


void StatusController::loop()
//*****************************************************************************
{
}

int StatusController::getBatteryPercentage(long v)
//*****************************************************************************
{
  // Check the voltage and interpolate between the defined ranges

  ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();

  logger->debug(LOGTAG, "V = %d", v);

  if (v >= FULLY_CHARGED_VOLTAGE)
  {
    return PERCENT_FULL; // 100% or above
  }
  else if (v >= ALMOST_FULL_VOLTAGE)
  {
    return PERCENT_ALMOST_FULL +
           (v - ALMOST_FULL_VOLTAGE) * (PERCENT_FULL - PERCENT_ALMOST_FULL) /
               (FULLY_CHARGED_VOLTAGE - ALMOST_FULL_VOLTAGE);
  }
  else if (v >= HIGH_VOLTAGE)
  {
    return PERCENT_HIGH +
           (v - HIGH_VOLTAGE) * (PERCENT_ALMOST_FULL - PERCENT_HIGH) /
               (ALMOST_FULL_VOLTAGE - HIGH_VOLTAGE);
  }
  else if (v >= MEDIUM_VOLTAGE)
  {
    return PERCENT_MEDIUM +
           (v - MEDIUM_VOLTAGE) * (PERCENT_HIGH - PERCENT_MEDIUM) /
               (HIGH_VOLTAGE - MEDIUM_VOLTAGE);
  }
  else if (v >= LOW_VOLTAGE)
  {
    return PERCENT_LOW +
           (v - LOW_VOLTAGE) * (PERCENT_MEDIUM - PERCENT_LOW) /
               (MEDIUM_VOLTAGE - LOW_VOLTAGE);
  }
  else if (v >= VERY_LOW_VOLTAGE)
  {
    return PERCENT_VERY_LOW +
           (v - VERY_LOW_VOLTAGE) * (PERCENT_LOW - PERCENT_VERY_LOW) /
               (LOW_VOLTAGE - VERY_LOW_VOLTAGE);
  }
  else if (v >= MINIMUM_VOLTAGE)
  {
    return PERCENT_MINIMUM +
           (v - MINIMUM_VOLTAGE) * (PERCENT_VERY_LOW - PERCENT_MINIMUM) /
               (VERY_LOW_VOLTAGE - MINIMUM_VOLTAGE);
  }
  else
  {
    return PERCENT_MINIMUM;
  }
}

void StatusController::getPowerManagementUpdate(ModFirmWare::SensorComponent *s)
//*****************************************************************************
{
  int bp = getBatteryPercentage((long) (pwrMgmt->getBusVoltage() * 1000));
  region.setBatteryPercent(bp);
  region.setCharging(pwrMgmt->isCharging());
  region.setPowered(pwrMgmt->isCharging() || pwrMgmt->isReady());

  char msg[120];

  ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();

  sprintf(msg, "{ \"busV\" : %.2f, \"current_mA\" : %.2f, \"consumption\" : %.2f \"charge status\" : %s}",
          pwrMgmt->getBusVoltage(), pwrMgmt->getCurrentmA(), pwrMgmt->getConsumptionmAh(), (pwrMgmt->isCharging()) ? "charging" : ((pwrMgmt->isReady()) ? "ready" : "battery"));
  logger->info(LOGTAG, msg);
  logger->info(LOGTAG, "charge: %d, ready: %d, battery = %d %", pwrMgmt->isCharging(), pwrMgmt->isReady(), bp);
  mqtt->sendMessage("tele", "battery", msg);
}

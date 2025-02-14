#include "tempmonitorcontroller.h"
#include "tftdisplay.h"
#include "tempprobe.h"
#include "servo.h"
#include "config.h"

using namespace KitchenClock;
using namespace ModFirmWare;

#define TEMP_INCREMENT 1.0f
#define TEMP_SERVO_TICK 1.0f
#define TEMP_OK_RANGE 2 * TEMP_SERVO_TICK
#define TEMP_NEAR_RANGE 10 * TEMP_SERVO_TICK
#define TEMP_SERVO_RANGE 15 * TEMP_SERVO_TICK

TempMonitorController::TempMonitorController(ModFirmWare::Controller *idleController,
                                             ModFirmWare::RotaryEncoder *rotaryEncoder,
                                             ModFirmWare::GPIOButton *rotaryButton,
                                             ModFirmWare::GPIOButton *modeButton,
                                             ModFirmWare::Mqtt *mqtt,
                                             ModFirmWare::TFTDisplay *display,
                                             ModFirmWare::Servo *servo,
                                             ModFirmWare::DisplayRegion::window_t window)
    : IdleableController(idleController),
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display),
      ntcProbe(nullptr),
      mqttClient(mqtt),
      servo(servo),
      region(display, window),
      settingMode(false),
      oldTarget(NAN_FLOAT)
//******************************************************************************
{
  setIdlePeriod(DISPLAY_IDLE_TURN_OFF_TIME);
}

void TempMonitorController::activate()
//******************************************************************************
{
  setTempProbe(ntcProbe);
  IdleableController::activate();
  region.triggerUpdate();
  display->registerRegion(&region, true);
  takeOverControls();

  ntcProbe->setUpdateCallback([this](SensorComponent *n)
                              { this->onTempUpdate(((TempProbe *)n)->getTemperatureC()); });
}

void TempMonitorController::setTempProbe(TempProbe *probe)
//******************************************************************************
{
  if (isActive()) return;

  ntcProbe = probe;
  region.setProbe(probe);
}

void TempMonitorController::loop()
//****************************************************************************************
{
  IdleableController::loop();

  if (ntcProbe->isTargetEnabled())
  {
    watchdog();
  }
}

void TempMonitorController::deactivate()
//****************************************************************************************
{
  display->unregisterRegion(&region);
  region.setProbe(nullptr);
  IdleableController::deactivate();
}

void KitchenClock::TempMonitorController::onRotaryCCw(long counter)
//****************************************************************************************
{
  if ((nullptr != ntcProbe) && (settingMode))
  {
    ntcProbe->changeTargetBy(-1 * TEMP_INCREMENT);
    region.triggerUpdate();
  }
}

void KitchenClock::TempMonitorController::onRotaryCw(long counter)
//****************************************************************************************
{
  if ((nullptr != ntcProbe) && (settingMode))
  {
    ntcProbe->changeTargetBy(TEMP_INCREMENT);
    region.triggerUpdate();
  }
}

void TempMonitorController::onRotaryClick(const uint16_t state,
                                          Buttons::click_t type)
//****************************************************************************************
{
  if (Buttons::click_t::SINGLE == type)
  {
    if (settingMode)
    {
      deactivateSettingsMode();
    }
    else
    {
      activateSettingsMode();
    }
  }
  else if (Buttons::click_t::LONG == type)
  {
    deactivateTemperatureTarget();
  }
}

void TempMonitorController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  if (settingMode)
  {
    deactivateSettingsMode(true);
  }
  else
  {
    gotoPrev();
  }
}

void TempMonitorController::onTempUpdate(float temperature)
//****************************************************************************************
{
  region.triggerUpdate();
  updateServo();
}

void TempMonitorController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

void TempMonitorController::updateTarget()
//****************************************************************************************
{
  if (nullptr != ntcProbe)
  {
    adjustServoRange(ntcProbe->getTarget());
    region.triggerUpdate();
  }
}

void TempMonitorController::updateServo()
//****************************************************************************************
{
  if ((nullptr != ntcProbe) && ntcProbe->isTargetEnabled() && ntcProbe->isReadingValid())
  {
    servo->moveToPosition(ntcProbe->getTemperatureC());
  }
}
void TempMonitorController::updateRange()
//****************************************************************************************
{
  if ((nullptr != ntcProbe) && ntcProbe->isTargetEnabled() && ntcProbe->isReadingValid())
  {
    TempMonitorRegion::range_t range;
    const float t = ntcProbe->getTemperatureC();
    const float tTarget = ntcProbe->getTarget();

    if ((t < (tTarget + TEMP_OK_RANGE)) && (t > (tTarget - TEMP_OK_RANGE)))
    {
      range = TempMonitorRegion::range_t::OK;
    }
    else if ((t < (tTarget + TEMP_NEAR_RANGE)) && (t > (tTarget - TEMP_NEAR_RANGE)))
    {
      range = TempMonitorRegion::range_t::NEAR;
    }
    else
    {
      range = TempMonitorRegion::range_t::OFF;
    }
  }
}

void TempMonitorController::activateSettingsMode()
//****************************************r************************************************
{
  if (nullptr == ntcProbe) return;

  oldTarget = ntcProbe->getTarget();
  if (isnanf(ntcProbe->getTarget()))
  {
    ntcProbe->setTarget(ntcProbe->getTemperatureC());
  }

  settingMode = true;
  region.enableSettingsMode(true);
  updateTarget();
}

void TempMonitorController::deactivateSettingsMode(bool cancel)
//****************************************************************************************
{
  if (nullptr == ntcProbe) return;

  if (cancel)
  {
    ntcProbe->setTarget(oldTarget);
  }
  else
  {
    ntcProbe->enableTarget(true);
  }

  settingMode = false;
  region.enableSettingsMode(false);
  updateTarget();
}

void TempMonitorController::deactivateTemperatureTarget()
//****************************************************************************************
{
  if (nullptr == ntcProbe) return;

  settingMode = false;
  ntcProbe->enableTarget(false);
  updateTarget();
}

void KitchenClock::TempMonitorController::adjustServoRange(float target)
//****************************************************************************************
{
  if ((nullptr != ntcProbe) && ntcProbe->isTargetEnabled())
  {
    servo->setMinPosition(target - TEMP_SERVO_RANGE);
    servo->setMaxPosition(target + TEMP_SERVO_RANGE);
    updateServo();
  }
}

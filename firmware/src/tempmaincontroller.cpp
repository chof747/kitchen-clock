#include "tempmaincontroller.h"
#include "tempmonitorcontroller.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"
#include "tempprobe.h"
#include "mqtt.h"
#include "config.h"

using namespace ModFirmWare;
using namespace KitchenClock;

#define LOGTAG "tempctrl"

TempMainController::TempMainController(Controller *idleController,
                               RotaryEncoder *rotaryEncoder,
                               GPIOButton *rotaryButton,
                               GPIOButton *modeButton,
                               TempProbe *ntc1,
                               TempProbe *ntc2,
                               ModFirmWare::Mqtt *mqtt,
                               TFTDisplay *display,
                               DisplayRegion::window_t window)
    //****************************************************************************************
    : IdleableController(idleController),
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display), region(display, window), 
      calibration(false), mqtt(mqtt), ntcProbe1(ntc1), ntcProbe2(ntc2)
{
  region.setProbe(0, ntc1);
  region.setProbe(1, ntc2);
  setIdlePeriod(DISPLAY_IDLE_TURN_OFF_TIME);
}

void TempMainController::activate()
//****************************************************************************************
{
  IdleableController::activate();

  onTempUpdate();
  region.triggerUpdate();
  display->registerRegion(&region, true);

  takeOverControls();
  ntcProbe1->setUpdateCallback([this](SensorComponent *n)
                         { this->onTempUpdate(); });
  ntcProbe2->setUpdateCallback([this](SensorComponent *n)
                         { this->onTempUpdate(); });
}

void TempMainController::loop()
//****************************************************************************************
{
  IdleableController::loop();
}

void TempMainController::deactivate()
//****************************************************************************************
{
  display->unregisterRegion(&region);
  region.unselectProbes();
  IdleableController::deactivate();
}

void TempMainController::onRotaryCw(long counter)
//****************************************************************************************
{
  region.selectNextProbe();
}

void TempMainController::onRotaryCCw(long counter)
//****************************************************************************************
{
  region.selectPrevProbe();
}

void TempMainController::onRotaryClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  if ((Buttons::click_t::SINGLE == type) && (-1 < region.getSelectedProbeIx()))
  {
    monitor->setTempProbe( (0 == region.getSelectedProbeIx()) ? ntcProbe1 : ntcProbe2);
    monitor->activate();
  }
  else if (Buttons::click_t::LONG == type)
  {
    calibration = !calibration;
    region.enableCalibrationMode(calibration);
  }
}

void TempMainController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  gotoPrev();
}

void TempMainController::onTempUpdate()
//****************************************************************************************
{
  region.triggerUpdate();

  if (calibration)
  {
    watchdog();
  }
}

void TempMainController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

void TempMainController::setMonitorController(TempMonitorController *monitor)
//****************************************************************************************
{
  this->monitor = monitor;
}

void TempMainController::sendResistanceTemperature(uint8_t ix, float t, float r)
//****************************************************************************************
{
  char msg[120];

  sprintf(msg, "{\n  \"temperature\" : %.2f,\n  \"resistance\" : %.2f,\n  \"index\" : %d\n }", 
    t, r, ix); 

  mqtt->sendMessage("tele", "tempsensor", msg);
}

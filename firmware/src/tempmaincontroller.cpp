#include "tempmaincontroller.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"
#include "ntcsensor.h"
#include "mqtt.h"

using namespace ModFirmWare;
using namespace KitchenClock;

#define LOGTAG "tempctrl"

TempMainController::TempMainController(Controller *idleController,
                               RotaryEncoder *rotaryEncoder,
                               GPIOButton *rotaryButton,
                               GPIOButton *modeButton,
                               NTCSensor *ntc1,
                               NTCSensor *ntc2,
                               ModFirmWare::Mqtt *mqtt,
                               TFTDisplay *display,
                               DisplayRegion::window_t window)
    //****************************************************************************************
    : IdleableController(idleController),
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display), region(display, window), 
      calibration(false), mqtt(mqtt), ntcProbe1(ntc1), ntcProbe2(ntc2)
{
}

void TempMainController::activate()
//****************************************************************************************
{
  IdleableController::activate();
  logger->debug(LOGTAG, "TempMainController activated");

  onTempUpdate();
  region.forceupdate();
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
  logger->debug(LOGTAG, "TempMainController deactivated");
  display->unregisterRegion(&region);
  IdleableController::deactivate();
}

void TempMainController::onRotaryCw(long counter)
//****************************************************************************************
{
}

void TempMainController::onRotaryCCw(long counter)
//****************************************************************************************
{
}

void TempMainController::onRotaryClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  logger->debug(LOGTAG, "Button press: %d - %s", state, (Buttons::click_t::LONG == type) ? "long" : "normal");
  if (Buttons::click_t::LONG == type)
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
  float r1 = ntcProbe1->getResistance();
  float r2 = ntcProbe2->getResistance();

  float t1 = ntcProbe1->getTemperatureC();
  float t2 = ntcProbe2->getTemperatureC();

  region.setResistance1(r1);
  region.setResistance2(r2);

  region.setTemperature1(t1);
  region.setTemperature2(t2);

  if (MAXFLOAT > r1)
  {
    sendResistanceTemperature(1, t1, r1);
  }

  if (MAXFLOAT > r2)
  {
    sendResistanceTemperature(2, t2, r2);
  }

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

void TempMainController::sendResistanceTemperature(uint8_t ix, float t, float r)
//****************************************************************************************
{
  char msg[120];

  sprintf(msg, "{\n  \"temperature\" : %.2f,\n  \"resistance\" : %.2f,\n  \"index\" : %d\n }", 
    t, r, ix); 

  mqtt->sendMessage("tele", "tempsensor", msg);
}

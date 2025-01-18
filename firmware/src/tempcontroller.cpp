#include "tempcontroller.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"
#include "ntcsensor.h"
#include "mqtt.h"

using namespace ModFirmWare;
using namespace KitchenClock;

#define LOGTAG "tempctrl"

TempController::TempController(Controller *idleController,
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

void TempController::activate()
//****************************************************************************************
{
  IdleableController::activate();
  logger->debug(LOGTAG, "TempController activated");

  onTempUpdate();
  region.forceupdate();
  display->registerRegion(&region, true);

  takeOverControls();
  ntcProbe1->setUpdateCallback([this](SensorComponent *n)
                         { this->onTempUpdate(); });
  ntcProbe2->setUpdateCallback([this](SensorComponent *n)
                         { this->onTempUpdate(); });
}

void TempController::loop()
//****************************************************************************************
{
  IdleableController::loop();
}

void TempController::deactivate()
//****************************************************************************************
{
  logger->debug(LOGTAG, "TempController deactivated");
  display->unregisterRegion(&region);
  IdleableController::deactivate();
}

void TempController::onRotaryCw(long counter)
//****************************************************************************************
{
}

void TempController::onRotaryCCw(long counter)
//****************************************************************************************
{
}

void TempController::onRotaryClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  logger->debug(LOGTAG, "Button press: %d - %s", state, (Buttons::click_t::LONG == type) ? "long" : "normal");
  if (Buttons::click_t::LONG == type)
  {
    calibration = !calibration;
    region.enableCalibrationMode(calibration);
  }
}

void TempController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  gotoPrev();
}

void TempController::onTempUpdate()
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

void TempController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

void TempController::sendResistanceTemperature(uint8_t ix, float t, float r)
//****************************************************************************************
{
  char msg[120];

  sprintf(msg, "{\n  \"temperature\" : %.2f,\n  \"resistance\" : %.2f,\n  \"index\" : %d\n }", 
    t, r, ix); 

  mqtt->sendMessage("tele", "tempsensor", msg);
}

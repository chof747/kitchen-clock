#include "tempcontroller.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"

using namespace ModFirmWare;
using namespace KitchenClock;

#define LOGTAG "tempctrl"

TempController::TempController(Controller *idleController,
                               RotaryEncoder *rotaryEncoder,
                               GPIOButton *rotaryButton,
                               GPIOButton *modeButton,
                               TFTDisplay *display)
    //****************************************************************************************
    : IdleableController(idleController), 
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display)
{
}

void TempController::activate()
//****************************************************************************************
{ 
  IdleableController::activate();
  takeOverControls();
  logger->debug(LOGTAG, "TempController took over!");
}

void TempController::loop()
//****************************************************************************************
{
  IdleableController::loop();
}

void TempController::deactivate()
//****************************************************************************************
{
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
}

void TempController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  gotoPrev();
}

void TempController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

#include "maincontroller.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"

using namespace ModFirmWare;
using namespace KitchenClock;

#define LOGTAG "mainctrl"

MainController::MainController(Controller *idleController,
                               RotaryEncoder *rotaryEncoder,
                               GPIOButton *rotaryButton,
                               GPIOButton *modeButton,
                               TFTDisplay *display)
    //****************************************************************************************
    : IdleableController(idleController), 
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display)
{
}

void MainController::activate()
//****************************************************************************************
{ 
  IdleableController::activate();
  takeOverControls();
  logger->debug(LOGTAG, "MainController took over!");
}

void MainController::loop()
//****************************************************************************************
{
  IdleableController::loop();
}

void MainController::deactivate()
//****************************************************************************************
{
  IdleableController::deactivate();
}

void MainController::onRotaryCw(long counter)
//****************************************************************************************
{
}

void MainController::onRotaryCCw(long counter)
//****************************************************************************************
{
}

void MainController::onRotaryClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
}

void MainController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
}

void MainController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

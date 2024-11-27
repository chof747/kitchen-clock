#include "idlecontroller.h"
#include "tftdisplay.h"
#include "wlan.h"
#include "servo.h"

#include "esp_sleep.h"
#include "config.h"
#include "driver/rtc_io.h"


using namespace KitchenClock;
using namespace ModFirmWare;

#define LOGTAG "idle"

IdleController::IdleController(WLan *wifi, TFTDisplay *display, Servo *clockServo, time_t deepSleepTime,
                               RotaryEncoder *rotaryEncoder, GPIOButton *rotaryButton, GPIOButton *modeButton)
    : wifi(wifi), clockServo(clockServo), timeToDeepSleep(deepSleepTime), idlingStartTime(0),
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display)
//****************************************************************************************
{
}

void IdleController::activate()
//****************************************************************************************
{
  Controller::activate();
  takeOverControls();
  startIdling();
}

void IdleController::loop()
//****************************************************************************************
{
  if (timeToDeepSleep < (millis() - idlingStartTime))
  {
    startDeepSleep();
  }
}

void IdleController::deactivate()
//****************************************************************************************
{
}

void IdleController::onRotaryCw(long counter)
//****************************************************************************************
{
  endIdling();
}

void IdleController::onRotaryCCw(long counter)
//****************************************************************************************
{
  endIdling();
}

void IdleController::onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type)
//****************************************************************************************
{
  endIdling();
}

void IdleController::onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type)
//****************************************************************************************
{
  endIdling();
}

void IdleController::startDeepSleep()
//****************************************************************************************
{
  gpio_num_t wakeup = static_cast<gpio_num_t>(REN_DAT);
  esp_sleep_enable_ext0_wakeup(wakeup, 0);

  // Go to deep sleep
  logger->info(LOGTAG, "Going into deep sleep - wakeup via mode button");
  rtc_gpio_pullup_en(wakeup);
  esp_deep_sleep_start();
}

void IdleController::startIdling()
//****************************************************************************************
{
  display->enableSleep(true);
  clockServo->disable();
  idlingStartTime = millis();
}

void KitchenClock::IdleController::endIdling()
//****************************************************************************************
{
  display->enableSleep(false);
  gotoNext();
}

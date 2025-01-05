#include "timercontroller.h"
#include "tftdisplay.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "servo.h"

using namespace KitchenClock;
using namespace ModFirmWare;

TimerController::TimerController(Controller *idleController,
                                 RotaryEncoder *rotenc,
                                 GPIOButton *rotencBtn,
                                 GPIOButton *modeBtn,
                                 TFTDisplay *display,
                                 MultiTimer *timer,
                                 Servo *servo)
    //****************************************************************************************
    : IdleableController(idleController),
      ControlUnit(rotaryEncoder, rotaryButton, modeButton, display),
      timer(timer), servo(servo)
{
}

void TimerController::loop()
//****************************************************************************************
{
}

void TimerController::activate()
//****************************************************************************************
{
}

void TimerController::deactivate()
//****************************************************************************************
{
  IdleableController::deactivate();
}

bool TimerController::onTimerMileStone(const char *caption, time_t atTime)
//****************************************************************************************
{
  return true;
}

bool TimerController::onTimerPeriod(const ModFirmWare::MultiTimer::periodtype_t periodType,
                                    time_t atTime, time_t elapsed, time_t remaining,
                                    time_t toNextMilestone)
//****************************************************************************************
{
  return true;
}

void TimerController::onTimerFinished(time_t atTime)
//****************************************************************************************
{
}

void TimerController::onTimerPause(time_t atTime)
//****************************************************************************************
{
}

void TimerController::onTimerResume(time_t atTime)
//****************************************************************************************
{
}

void TimerController::onTimerStart(time_t atTime)
//****************************************************************************************
{
}

void TimerController::onTimerReset(time_t atTime)
//****************************************************************************************
{
}

void TimerController::onRotaryCw(long counter)
//****************************************************************************************
{
}

void TimerController::onRotaryCCw(long counter)
//****************************************************************************************
{
}

void TimerController::onRotaryClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
}

void TimerController::onModeClick(const uint16_t state, Buttons::click_t type)
//****************************************************************************************
{
  gotoPrev();
}

void TimerController::onAnyEvent()
//****************************************************************************************
{
  watchdog();
}

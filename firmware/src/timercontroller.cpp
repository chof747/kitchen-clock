#include "timercontroller.h"
#include "tftdisplay.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "servo.h"

using namespace KitchenClock;

TimerController::TimerController(ModFirmWare::TFTDisplay *display,
                                 ModFirmWare::RotaryEncoder *rotenc,
                                 ModFirmWare::GPIOButton rotencBtn,
                                 ModFirmWare::GPIOButton modeBtn,
                                 ModFirmWare::MultiTimer timer,
                                 ModFirmWare::Servo servo)
//****************************************************************************************
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

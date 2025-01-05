#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include "idleablecontroller.h"
#include "controlunit.h"
#include "multitimer.h"

namespace ModFirmWare
{
  class Servo;
}

namespace KitchenClock
{

  class TimerController : public ModFirmWare::IdleableController, protected ControlUnit
  {
  public:
    TimerController(ModFirmWare::Controller *idleController,
                    ModFirmWare::RotaryEncoder *rotenc,
                    ModFirmWare::GPIOButton *rotencBtn,
                    ModFirmWare::GPIOButton *modeBtn,
                    ModFirmWare::TFTDisplay *display,
                    ModFirmWare::MultiTimer *timer,
                    ModFirmWare::Servo *servo);

    void activate();
    void loop();
    void deactivate();

    // timing events
    bool onTimerMileStone(const char *caption, time_t atTime);
    bool onTimerPeriod(const ModFirmWare::MultiTimer::periodtype_t periodType, time_t atTime,
                       time_t elapsed, time_t remaining, time_t toNextMilestone);
    void onTimerFinished(time_t atTime);
    void onTimerPause(time_t atTime);
    void onTimerResume(time_t atTime);
    void onTimerStart(time_t atTime);
    void onTimerReset(time_t atTime);

  protected:
    void onRotaryCw(long counter);
    void onRotaryCCw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onAnyEvent();

  private:
    ModFirmWare::MultiTimer* timer;
    ModFirmWare::Servo* servo;
  };
};

#endif // TIMERCONTROLLER_H

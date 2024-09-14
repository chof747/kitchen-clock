#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <controller.h>
#include <multitimer.h>
#include <buttons.h>

namespace ModFirmWare
{
  class RotaryEncoder;
  class TFTDisplay;
  class GPIOButton;
  class Servo;
}

namespace KitchenClock
{

  class TimerController : public ModFirmWare::Controller
  {
  public:
    TimerController(ModFirmWare::TFTDisplay* display, 
                    ModFirmWare::RotaryEncoder* rotenc,
                    ModFirmWare::GPIOButton rotencBtn,
                    ModFirmWare::GPIOButton modeBtn,
                    ModFirmWare::MultiTimer timer,
                    ModFirmWare::Servo servo);

    void activate();
    void loop();

    //timing events
    bool onTimerMileStone(const char *caption, time_t atTime);
    bool onTimerPeriod(const ModFirmWare::MultiTimer::periodtype_t periodType, time_t atTime, 
                       time_t elapsed, time_t remaining, time_t toNextMilestone);
    void onTimerFinished(time_t atTime);
    void onTimerPause(time_t atTime);
    void onTimerResume(time_t atTime);
    void onTimerStart(time_t atTime);
    void onTimerReset(time_t atTime);

    //input controls
    void onRotaryCw(long counter);
    void onRotaryCcw(long counter);
    void onRotaryClick(const uint16_t state, ModFirmWare::Buttons::click_t type);
    void onModeClick(const uint16_t state, ModFirmWare::Buttons::click_t type);

  private:


  };
};

#endif // TIMERCONTROLLER_H

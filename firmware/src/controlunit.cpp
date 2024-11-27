#include "controlunit.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"

using namespace KitchenClock;
using namespace ModFirmWare;

ControlUnit::ControlUnit(ModFirmWare::RotaryEncoder *rotaryEncoder,
                         ModFirmWare::GPIOButton *rotaryButton,
                         ModFirmWare::GPIOButton *modeButton,
                         ModFirmWare::TFTDisplay *display)
  :rotaryEncoder(rotaryEncoder), rotaryButton(rotaryButton), modeButton(modeButton), display(display)
{
}

void ControlUnit::takeOverControls()
{
  rotaryEncoder->setOnClockwise([this](int param)
                                { this->onAnyEvent();
                                  this->onRotaryCw(param); });

  rotaryEncoder->setOnCounterClockwise([this](int param)
                                       { this->onAnyEvent();
                                         this->onRotaryCCw(param); });

  rotaryButton->setButtonPressedCallBack([this](int button, Buttons::click_t state)
                                         { this->onAnyEvent();
                                           this->onRotaryClick(button, state); });

  modeButton->setButtonPressedCallBack([this](int button, Buttons::click_t state)
                                       { this->onAnyEvent();
                                         this->onModeClick(button, state); });
}
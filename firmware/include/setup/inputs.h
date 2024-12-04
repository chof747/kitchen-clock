#ifndef SETUP_INPUTS_H
#define SETUP_INPUTS_H

#include "config.h"

#include "gpiobutton.h"
#include "roteryencoder.h"
#include "powermanagement.h"
#include "ads1115.h"



/*******************************************************************************
 * 
 * INPUTS:
 * 
 * - mode button
 * - rotary encoder (rotary button  and encoder)
 * - power management (charging status and power consumption)
 * - ADC channels 
 */

ModFirmWare::GPIOButton modeButton(MODE_BTN, INPUT_PULLUP, true);
ModFirmWare::GPIOButton rotaryButton(REN_BTN, INPUT_PULLUP, true);
ModFirmWare::PowerManagement powerMgmt(CHG_IND, RDY_IND);
ModFirmWare::RotaryEncoder encoder(REN_CLK, REN_DAT, 0, 100);

ModFirmWare::Ads1115Sensor::channels_t adcChannels = {
  ADC_00_DRV, 
  ModFirmWare::Ads1115Sensor::CHANNEL_NOT_USED,
  ModFirmWare::Ads1115Sensor::CHANNEL_NOT_USED,
  ADC_01_DRV
};
ModFirmWare::Ads1115Sensor adsSensor(adcChannels);

#endif //SETUP_INPUTS_H
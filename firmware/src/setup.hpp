#ifndef SETUP_H
#define SETUP_H

#include "config.h"

#include <Wire.h>
#include <SPI.h>

#include "logengine.h"
#include "logengine/serial.h"
#include "modfirmware.h"
#include "multitimer.h"
#include "gpiobutton.h"
#include "roteryencoder.h"
#include "powermanagement.h"
#include "ads1115.h"
#include "servo.h"
#include "wlan.h"
#include "mqtt.h"
#include "tftdisplay.h"

#include "regions/startregion.h"
#include "idlecontroller.h"

ModFirmWare::LogEngineSerial logger_serial(MODFIRMWARE_LOG_LEVEL, LOGSPEED);
ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();

/*******************************************************************************
 * 
 * COMMUNICATION:
 * 
 * - WiFi
 * - MQTT
 */

ModFirmWare::WLan wifi("kitchen-clock", "KitchenClock");
ModFirmWare::Mqtt mqttClient;

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
    ADC_01_DRV};
ModFirmWare::Ads1115Sensor adsSensor(adcChannels);

/*******************************************************************************
 * 
 * OUTPUTS:
 * 
 * - clock servo
 * - piezzo buzzer (TODO: add)
 */

ModFirmWare::Servo clock_servo(SERVO_PWM, SERVO_DRV, 
                               SERVO_PWM_CHANNEL, SERVO_PWM_RESOLUTION, SERVO_FREQ,
                               SERVO_MIN_PULSE, SERVO_MAX_PULSE);

/*******************************************************************************
 * 
 * DISPLAY COMPONENTS:
 * 
 * - TFT Display
 * - Icons
 */

ModFirmWare::TFTDisplay display(DISPLAY_CS, DISPLAY_RS, DISPLAY_RST, DISPLAY_BKLT, INITR_BLACKTAB);

ModFirmWare::MultiTimer mtimer(5 IN_SECONDS);

KitchenClock::IdleController idleController(&wifi,&display,&clock_servo, ESP_IDLE_DEEP_SLEEP_TIME, &encoder, &rotaryButton, &modeButton);

ModFirmWare::Application app("KitchenClock");

namespace KitchenClock
{
  void setupInputs()
  //***************************************************************************
  {
    app.addComponent(&powerMgmt);
    
    app.addComponent(&modeButton);
    app.addComponent(&encoder);
    app.addComponent(&rotaryButton);

    app.addComponent(&adsSensor);
  }

  KitchenClock::StartRegion* setupDisplay()
  //***************************************************************************
  {
    app.addComponent(&display);
    KitchenClock::StartRegion* startRegion = new KitchenClock::StartRegion(&display,"/pics/logo_61x128.rgb");
    display.setShowAtStartup(startRegion);
    return startRegion;
  }

  void resetWifiSettings(const char *topic, const char *payload)
  //****************************************************************************
  {
    if (0 == strcmp("reset", payload))
    {
      wifi.resetWifiSettings();
    }
  }

  void setupPeripherals()
  //***************************************************************************
  {
    Wire.begin(I2C_SDA, I2C_SCL);
    SPI.begin(DISPLAY_SCK, -1, DISPLAY_SDA);
  }

  void setupCommunication()
  //***************************************************************************
  {
    app.addComponent(&wifi);
    app.addComponent(&mqttClient);
    mqttClient.setClient(wifi.getClient());
    wifi.addConfigurator(&mqttClient);

    mqttClient.registerCommand("resetwifi", resetWifiSettings);
  }

}

#endif //SETUP_H
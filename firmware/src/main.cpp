#include "config.h"

#include <Arduino.h>
#include "logengine.h"
#include "logengine/serial.h"
#include "modfirmware.h"
#include "wlan.h"
#include "mqtt.h"
#include "gpiobutton.h"
#include "roteryencoder.h"
#include "servo.h"
#include "multitimer.h"
#include "tftdisplay.h"
#include "ads1115.h"
#include "powermanagement.h"
#include "statuscontroller.h"
#include "idlecontroller.h"
#include "maincontroller.h"
#include "regions/statusregion.h"
#include "regions/startregion.h"
#include <Wire.h>
#include <SPI.h>

#define RDY_IND 6
#define CHG_IND 7


#define LOGTAG "main"
#define LOGSPEED 115200

ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();
ModFirmWare::LogEngineSerial logger_serial(MODFIRMWARE_LOG_LEVEL, LOGSPEED);
ModFirmWare::WLan wifi("kitchen-clock", "KitchenClock");
ModFirmWare::Mqtt mqttClient;

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

ModFirmWare::Servo clock_servo(SERVO_PWM, SERVO_DRV, 
                               SERVO_PWM_CHANNEL, SERVO_PWM_RESOLUTION, SERVO_FREQ,
                               SERVO_MIN_PULSE, SERVO_MAX_PULSE);
ModFirmWare::TFTDisplay display(DISPLAY_CS, DISPLAY_RS, DISPLAY_RST, DISPLAY_BKLT, INITR_BLACKTAB);

ModFirmWare::MultiTimer mtimer(5 IN_SECONDS);

ModFirmWare::Application app("KitchenClock");

KitchenClock::IdleController idleController(&wifi,&display,&clock_servo, ESP_IDLE_DEEP_SLEEP_TIME, &encoder, &rotaryButton, &modeButton);
KitchenClock::StatusController statusController(&powerMgmt, &wifi, &mqttClient, &display, {0, 0, 160, 16});
KitchenClock::MainController mainController(&idleController, &encoder, &rotaryButton, &modeButton, &display);

time_t lastAction = 0;
time_t reactivaTimerAt = 0;
long servoPosition = 0;
bool enableSleep = false;

void resetWifiSettings(const char *topic, const char *payload)
//******************************************************************************
{
  if (0 == strcmp("reset", payload))
  {
    wifi.resetWifiSettings();
  }
}

void setup()
{
  delay(2000);
  //setup peripheral interfaces;
  Wire.begin(I2C_SDA, I2C_SCL);
  SPI.begin(DISPLAY_SCK, -1, DISPLAY_SDA);

  // put your setup code here, to run once:
  logger->addStrategy(&logger_serial);  

  app.addComponent(&display);

  app.setDeviceName("test_esp32");
  app.addComponent(&wifi);

  app.addComponent(&mqttClient);
  mqttClient.setClient(wifi.getClient());
  wifi.addConfigurator(&mqttClient);

  app.addComponent(&powerMgmt);

  app.addComponent(&modeButton);
  app.addComponent(&encoder);
  app.addComponent(&rotaryButton);

  app.addComponent(&adsSensor);

/*
  app.addComponent(&clock_servo);
  app.addComponent(&mtimer);
*/

  //setup startup screen
  KitchenClock::StartRegion startRegion(&display,"/pics/logo_61x128.rgb");
  display.setShowAtStartup(&startRegion);

  logger->debug(LOGTAG, "Starting setup");
  app.setup();

  display.fillRect(0,0,display.width(), display.height(), ST77XX_BLACK);
  
  mqttClient.registerCommand("resetwifi", resetWifiSettings);

  app.registerController(&mainController);
  app.registerController(&idleController);

  statusController.activate();
  mainController.activate();
  

  logger->info(LOGTAG, "Setup Done!");
  
  mtimer.start();
}

void loop()
{
  statusController.loop();
  app.loop();
  // logger->info(LOGTAG,"Hello World!");
}

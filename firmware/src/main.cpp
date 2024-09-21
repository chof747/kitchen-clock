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
#include "powermanagement.h"
#include "statuscontroller.h"
#include "regions/statusregion.h"
#include <Wire.h>
#include <SPI.h>

#define RDY_IND 6
#define CHG_IND 7


#define LOGTAG "main"

ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();
ModFirmWare::LogEngineSerial logger_serial(MODFIRMWARE_LOG_LEVEL, ModFirmWare::usbCDCHelper(9600));
ModFirmWare::WLan wifi("kitchen-clock", "KitchenClock");
ModFirmWare::Mqtt mqttClient;

ModFirmWare::GPIOButton modeButton(MODE_BTN, INPUT_PULLUP, true);
ModFirmWare::GPIOButton rotaryButton(REN_BTN, INPUT_PULLUP, true);
ModFirmWare::PowerManagement powerMgmt(CHG_IND, RDY_IND);
ModFirmWare::RotaryEncoder encoder(REN_CLK, REN_DAT, 0, 100);
ModFirmWare::Servo clock_servo(SERVO_PWM, SERVO_DRV, 
                               SERVO_PWM_CHANNEL, SERVO_PWM_RESOLUTION, SERVO_FREQ,
                               SERVO_MIN_PULSE, SERVO_MAX_PULSE);
ModFirmWare::TFTDisplay display(DISPLAY_CS,DISPLAY_RS,DISPLAY_RST);

ModFirmWare::MultiTimer mtimer(5 IN_SECONDS);

ModFirmWare::Application app("KitchenClock");

KitchenClock::StatusController statuscontroller(&powerMgmt, &wifi, &mqttClient, &display, {0, 0, 160, 16});

time_t lastAction = 0;
time_t reactivaTimerAt = 0;
long servoPosition = 0;

void resetWifiSettings(const char *topic, const char *payload)
//******************************************************************************
{
  if (0 == strcmp("reset", payload))
  {
    wifi.resetWifiSettings();
  }
}

void modeButtonPress(uint16_t state, ModFirmWare::Buttons::click_t clicktype)
{
  int d = digitalRead(DISPLAY_BKLT);
  d = (LOW == d) ? HIGH : LOW;
  digitalWrite(DISPLAY_BKLT, d);
}

void setup()
{
  //setup peripheral interfaces;
  Wire.begin(I2C_SDA, I2C_SCL);
  SPI.begin(DISPLAY_SCK, -1, DISPLAY_SDA);

  // put your setup code here, to run once:
  logger->addStrategy(&logger_serial);  

  app.setDeviceName("test_esp32");
  app.addComponent(&wifi);


  app.addComponent(&mqttClient);
  mqttClient.setClient(wifi.getClient());
  wifi.addConfigurator(&mqttClient);

  app.addComponent(&powerMgmt);

  app.addComponent(&modeButton);
  modeButton.setButtonPressedCallBack(modeButtonPress);

  app.addComponent(&encoder);

/*
  app.addComponent(&clock_servo);
  app.addComponent(&mtimer);
*/
  delay(2000);

  pinMode(DISPLAY_BKLT, OUTPUT);
  digitalWrite(DISPLAY_BKLT, LOW);

  logger->debug(LOGTAG, "Starting setup");
  app.setup();

  display.fillRect(0,0,display.width(), display.height(), ST77XX_BLACK);
  statuscontroller.activate();
  
  mqttClient.registerCommand("resetwifi", resetWifiSettings);

  logger->info(LOGTAG, "Setup Done!");
  
  mtimer.start();
}

void loop()
{
  statuscontroller.loop();
  app.loop();
  // logger->info(LOGTAG,"Hello World!");
}

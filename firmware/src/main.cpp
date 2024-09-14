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
ModFirmWare::RotaryEncoder encoder(REN_CLK, REN_DAT);
ModFirmWare::Servo clock_servo(SERVO_PWM, SERVO_DRV, 
                               SERVO_PWM_CHANNEL, SERVO_PWM_RESOLUTION, SERVO_FREQ,
                               SERVO_MIN_PULSE, SERVO_MAX_PULSE);
ModFirmWare::TFTDisplay display(DISPLAY_CS,DISPLAY_RS,DISPLAY_RST);

ModFirmWare::MultiTimer mtimer(5 IN_SECONDS);

ModFirmWare::Application app("KitchenClock");

time_t lastAction = 0;
time_t reactivaTimerAt = 0;
long servoPosition = 0;
bool flip = true;

void resetWifiSettings(const char *topic, const char *payload)
//******************************************************************************
{
  if (0 == strcmp("reset", payload))
  {
    wifi.resetWifiSettings();
  }
}

void moveServoTo(const char *topic, const char *payload)
//******************************************************************************
{
  long pos = strtol(payload, NULL, 10);
  pos = (pos < 0) ? 0 : (pos > 90) ? 90
                                   : pos;
  clock_servo.moveToPosition(pos);
}



void rotaryEncPressed(uint16_t state, ModFirmWare::Buttons::click_t clicktype)
//******************************************************************************
{
  logger->info(LOGTAG, "Encoder pressed with %s", (0 == clicktype) ? "Single-clicked" : (1 == clicktype) ? "Double-clicked"
                                                                                                         : "Long-pressed");
  if (ModFirmWare::Buttons::click_t::SINGLE == clicktype)
  {
    mtimer.pause();
  }
  else if (ModFirmWare::Buttons::click_t::DOUBLE == clicktype)
  {
    mtimer.resume();
  }
  else
  {
    // do nothing
  }
}

void encoderCw(long counter)
//******************************************************************************
{
  logger->info(LOGTAG, "Encoder clockwise (%d)", counter);
  clock_servo.moveToPosition(counter);
  lastAction = millis();
}

void encoderCCw(long counter)
//******************************************************************************
{
  logger->info(LOGTAG, "Encoder counter-clockwise");
  clock_servo.moveToPosition(counter);
  lastAction = millis();
}

bool timerDone(time_t at)
//******************************************************************************
{
  logger->info(LOGTAG, "Timer is finished at %d", at);
  return true;
}

bool timerMilestone(const char* caption, time_t at)
//******************************************************************************
{
  logger->info(LOGTAG, "Milstone: %s at %d", caption, at);
  return true;
}

bool periodPast(const ModFirmWare::MultiTimer::periodtype_t periodType, time_t atMillis, time_t elapsed, time_t remaining, time_t toNextMilestone)
//******************************************************************************
{
  if (ModFirmWare::MultiTimer::periodtype_t::SHORT == periodType)
  {
    // clock_servo.moveToPosition(servoPosition++);
    logger->info(LOGTAG, "Short Period at = %06d", atMillis);
  }
  else if (ModFirmWare::MultiTimer::periodtype_t::LONG == periodType)
  {
    logger->info(LOGTAG, "Long Period at = %06d", atMillis);
  }
  return true;
}

void pwrDataUpdate(ModFirmWare::SensorComponent* sensor)
{
  char msg[120];


  sprintf(msg, "{ \"busV\" : %.2f, \"current_mA\" : %.2f, \"consumption\" : %.2f \"charge status\" : %s}",
   powerMgmt.getBusVoltage(), powerMgmt.getCurrentmA(), powerMgmt.getConsumptionmAh(), (powerMgmt.isCharging()) ? "charging" : ((powerMgmt.isReady()) ? "ready" : "undefined"));
  logger->info(LOGTAG, msg);
  logger->info(LOGTAG, "charge: %d, ready: %d", powerMgmt.isCharging(), powerMgmt.isReady());
  mqttClient.sendMessage("tele", "battery", msg);
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
  powerMgmt.setUpdateCallback(pwrDataUpdate);
/*
  app.addComponent(&modeButton);
  
  app.addComponent(&encoder);
  encoder.setOnClockwise(encoderCw);
  encoder.setOnCounterClockwise(encoderCCw);

  app.addComponent(&rotaryButton);
  rotaryButton.setButtonPressedCallBack(rotaryEncPressed);

  app.addComponent(&clock_servo);
  clock_servo.setMinPosition(0);
  clock_servo.setMaxPosition(90);

  app.addComponent(&display);

  app.addComponent(&mtimer);
  //mtimer.setDuration(1000);
  // mtimer.setFinishedCallback(timerDone);
  // mtimer.setPeriodCallback(periodPast);
  // mtimer.setMileStoneCallback(timerMilestone);
*/
  delay(2000);

  logger->debug(LOGTAG, "Starting setup");
  app.setup();

  mqttClient.registerCommand("resetwifi", resetWifiSettings);
  mqttClient.registerCommand("moveto", moveServoTo);

  logger->info(LOGTAG, "Setup Done!");

  mtimer.start();
}

void loop()
{
  app.loop();

  if (5000 < (millis() - lastAction))
  {
    lastAction = millis();
    //logger->debug(LOGTAG, "heartbeat");
  }

  // logger->info(LOGTAG,"Hello World!");
}

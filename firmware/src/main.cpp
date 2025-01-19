#include "config.h"


#include <Arduino.h>

#include "iconmenu_controller.h"

#include "setup.hpp"
#include "menus.hpp"

#include "statuscontroller.h"
#include "timercontroller.h"
#include "tempmaincontroller.h"
#include "regions/statusregion.h"

#define LOGTAG "main"

KitchenClock::StatusController statusController(&powerMgmt, &wifi, &mqttClient, &display, {0, 0, 160, 16});
KitchenClock::TimerController timerController(&idleController, &encoder, &rotaryButton, &modeButton, &display, &mtimer, &clock_servo); 
KitchenClock::TempMainController tempMainController(&idleController, &encoder, &rotaryButton, &modeButton, &ntcProbe1, &ntcProbe2, &mqttClient, &display, {0, 16, 160, 112});
ModFirmWare::IconMenuController mainMenu(&encoder, &rotaryButton, &modeButton, &display, {0, 16, 160, 112}, &idleController);


void setup()
//******************************************************************************
{
  delay(1000);

  KitchenClock::setupPeripherals();
  app.setDeviceName("test_esp32");
  logger->addStrategy(&logger_serial);  

  KitchenClock::StartRegion* sr = KitchenClock::setupDisplay();
  KitchenClock::setupCommunication();

  KitchenClock::setupInputs();
  adsSensor.setUpdateInterval(5 IN_SECONDS);
/*
  app.addComponent(&clock_servo);
  app.addComponent(&mtimer);
*/

  //setup startup screen

  logger->debug(LOGTAG, "Starting setup");
  app.setup();

  KitchenClock::compileMenu(&mainMenu, 
    nullptr /* timerController */,
    &tempMainController,
    nullptr /* home automation controller */,
    nullptr /* settings controller*/);

  mainMenu.setDimensions(40, 40, 25, 2, 10);

  app.registerController(&tempMainController, &mainMenu);
  app.registerController(&timerController, &mainMenu);
  app.registerController(&idleController);
  app.registerController(&mainMenu);

  statusController.activate();
  logger->info(LOGTAG, "Setup Done!");
  mainMenu.activate();

  display.unregisterRegion(sr);
  delete sr;

  mtimer.start();
}

void loop()
{
  statusController.loop();
  app.loop();
  // logger->info(LOGTAG,"Hello World!");
}

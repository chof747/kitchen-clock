#include <Arduino.h>
#include "logengine.h"
#include "logengine/serial.h"
#include "modfirmware.h"
#include "wlan.h"
#include "mqtt.h"
#include "gpiobutton.h"
#include "roteryencoder.h"

#define LED_PIN 48
#define NUM_LEDS 1

// Create an instance of the Adafruit_NeoPixel class
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


// put function declarations here:
int myFunction(int, int);

ModFirmWare::LogEngine *logger = ModFirmWare::LogEngine::getInstance();
ModFirmWare::LogEngineSerial logger_serial(MODFIRMWARE_LOG_LEVEL, 11520);
ModFirmWare::WLan wifi("kitchen-clock", "KitchenClock");
ModFirmWare::Mqtt mqttClient;

ModFirmWare::GPIOButton button0(0, INPUT_PULLUP, true);
ModFirmWare::RotaryEncoder encoder(17,7, -10, 10, true);

ModFirmWare::Application app("KitchenClock");

void resetWifiSettings(const char* topic, const char* payload)
//******************************************************************************
{
  if (0 == strcmp("reset", payload))
  {
    wifi.resetWifiSettings();
  }
}

void sayHello(const char* topic, const char* payload)
//******************************************************************************
{
  logger->info("MAIN", "Hello %s", payload);
}

void button0Pressed(uint16_t state, ModFirmWare::Buttons::click_t clicktype)
{
  logger->info("MAIN", "%s button0!", (0 == clicktype) ? "Single-clicked" : (1 == clicktype) ? "Double-clicked" : "Long-pressed");
}

void encoderCw(long counter)
//******************************************************************************
{
  logger->info("MAIN", "Encoder clockwise (%d)", counter);
}

void encoderCCw(long counter)
//******************************************************************************
{
  logger->info("MAIN", "Encoder counter-clockwise");
}

void setup()
{
  // put your setup code here, to run once:
  logger->addStrategy(&logger_serial);

  app.setDeviceName("test_esp32");
  app.addComponent(&wifi);

  app.addComponent(&mqttClient);
  mqttClient.setClient(wifi.getClient());
  wifi.addConfigurator(&mqttClient);

  app.addComponent(&button0);
  button0.setButtonPressedCallBack(button0Pressed);

  app.addComponent(&encoder);
  encoder.setOnClockwise(encoderCw);
  encoder.setOnCounterClockwise(encoderCCw);

  app.setup();

  mqttClient.registerCommand("resetwifi", resetWifiSettings);
  mqttClient.registerCommand("hello", sayHello);

  logger->info("MAIN", "Setup Done!");
}

void loop()
{ 
  app.loop();
  // logger->info("MAIN","Hello World!");
}
  
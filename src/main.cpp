#include <Arduino.h>
#include <net/WiFiConfig.h>
#include <sensors/SoilMoistureSensor.h>
#include <sensors/DHTSensor.h>

//To implement
#include <actuators/LCDDisplay.h>
#include <net/CloudDatabase.h>
#include <actuators/WaterPump.h>
//To implement

AsyncWebServer server(80);

const uint8_t soil_moisture_pin = 32;
const uint8_t dht_pin = 33;

void setup() {

  setCpuFrequencyMhz(80);

  wifi::init("rudnik1", "netikazuvam");

  sms::init(&server, soil_moisture_pin);
  dht::init(&server, dht_pin);

  server.begin();
}

void loop() {}
/**
 * DO NOT MODIFY THIS FILE
*/
#ifndef DEVICE_H_
#define DEVICE_H_

#include <helpers.h>
#include <ArduinoJson.h>
#include <configuration.h>
#include <lm35.h>
#include <extern.h>
#include <wifi.h>
#include <timer.h>

class DEVICE
{
public:
  void setup();
  void run();

private:
  WIFI wifi;
  TIMER tmr;
  LM35 lm35;
  void mqttCallback(char *topic, byte *payload, unsigned int length);
  void sendData();
};
#endif

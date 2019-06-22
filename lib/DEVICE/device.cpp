/**
 * DO NOT MODIFY THIS FILE
*/
#include "device.h"

void DEVICE::setup()
{
#ifdef DEBUG_ENABLED
    Serial.begin(SERIAL_BAUD);
    Serial.println(); // Inserts a new line for a clearner terminal
    delay(5000);      // Timeout to give the serial monitor time to connect
#endif

    // Setup Components
    wifi.setup();
    mqtt->setup();
    lm35.setup();
    // Setup MQTT Callback Function (Don't touch)
    mqtt->client.setCallback([this](char *_topic, byte *_payload, unsigned int _length) {
        mqttCallback(_topic, _payload, _length);
    });
    tmr.setInterval(60 * 1000, [this]() { // Every 1 minute
        sendData();
    });
}
void DEVICE::mqttCallback(char *_topic, byte *_payload, unsigned int _length)
{
    // Convert payload to a string
    String callback = payload2string(_payload, _length);
}
void DEVICE::sendData()
{
    String payload = String(lm35.getTemp());
    mqtt->client.publish(MQTT_STATE_TOPIC.c_str(), payload.c_str());
}
void DEVICE::run()
{
    if (wifi.run())
    {
        if (mqtt->run())
        {
            lm35.run();
        }
    }
}

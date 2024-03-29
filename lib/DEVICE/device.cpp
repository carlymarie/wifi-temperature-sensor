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

    tmr.setInterval(100, [this]() { // Every 1 minute
        temps += lm35.getTemp();
        ticks++;
    });
    tmr1.setInterval(10000, [this]() { // Every 1 minute
        sendData();
    });
}
void DEVICE::sendData()
{
    String payload = String(temps / ticks);
    DEBUG_PRINT("Temperature: " + payload, true);
    mqtt->client.publish(MQTT_STATE_TOPIC.c_str(), payload.c_str());
    temps = 0;
    ticks = 0;
}
void DEVICE::run()
{
    if (wifi.run())
    {
        if (mqtt->run())
        {
            //lm35.run();
            tmr.run();
            tmr1.run();
        }
    }
}

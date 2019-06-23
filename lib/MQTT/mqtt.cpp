/**
 * DO NOT MODIFY THIS FILE
*/
#include <mqtt.h>
MQTT::MQTT() : client(espClient)
{
}
void MQTT::setup()
{
    client.setServer(MQTT_HOST, MQTT_PORT);
}
void MQTT::setupSensor()
{

    DynamicJsonDocument buffer(1024);
    JsonObject data = buffer.createNestedObject();
    // HEATING
    data["name"] = MQTT_DEVICE_NAME;
    data["state_topic"] = MQTT_STATE_TOPIC;
    data["unit_of_measurement"] = "°F";
    data["availability_topic"] = MQTT_AVAILABILITY_TOPIC;
    data["payload_available"] = MQTT_WILL_ONLINE;
    data["payload_not_available"] = MQTT_WILL_OFFLINE;
    data["retain"] = MQTT_RETAIN;
    data["qos"] = MQTT_QOS;

    String config;
    serializeJson(data, config);
    if (client.publish(MQTT_CONFIG_TOPIC.c_str(), config.c_str(), MQTT_RETAIN)) // Publish Discoery Configuration
    {
        DEBUG_PRINT(MQTT_DEVICE_NAME, false);
        DEBUG_PRINT(F(" has been setup"), true);
        DEBUG_PRINT(F("[OK] Published to: "), false);
    }
    else
    {
        DEBUG_PRINT(F("[ERROR] Unable to publish to: "), false);
    }
    DEBUG_PRINT(MQTT_CONFIG_TOPIC, true);
}
bool MQTT::run()
{
    bool connected = client.connected();
    if (!connected)
    {
        if (client.connect(MQTT_DEVICE_NAME.c_str(), MQTT_USER, MQTT_PASS, MQTT_AVAILABILITY_TOPIC.c_str(), MQTT_QOS, MQTT_RETAIN, MQTT_WILL_OFFLINE, MQTT_CLEAN_SESSION))
        {
            DEBUG_PRINT(F("[OK] Connected to MQTT Server"), true);
            if (!client.publish(MQTT_AVAILABILITY_TOPIC.c_str(), MQTT_WILL_ONLINE, MQTT_RETAIN))
            {
                DEBUG_PRINT(F("[ERROR] Unable to publish to: "), false);
                DEBUG_PRINT(MQTT_AVAILABILITY_TOPIC, true);
            }
            // Setup MQTT Discovery Configurations
            setupSensor();
        }
        else
        {
            DEBUG_PRINT(F("[ERROR] Unable to connect to MQTT Server"), true);
        }
    }
    client.loop();
    return connected;
}
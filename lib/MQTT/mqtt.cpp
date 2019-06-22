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
    data["command_topic"] = MQTT_COMMAND_TOPIC;
    data["state_topic"] = MQTT_STATE_TOPIC;
    data["availability_topic"] = MQTT_AVAILABILITY_TOPIC;
    data["retain"] = MQTT_RETAIN;
    data["qos"] = MQTT_QOS;

    String config;
    serializeJson(data, Serial);
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

    if (client.subscribe(MQTT_COMMAND_TOPIC.c_str(), MQTT_QOS)) // Subscribe to Command Topic
    {
        DEBUG_PRINT(F("[OK] Subscribed to: "), false);
    }
    else
    {
        DEBUG_PRINT(F("[ERROR] Unable to subscribe to: "), false);
    }
    DEBUG_PRINT(MQTT_COMMAND_TOPIC, true);
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
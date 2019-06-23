/**
 * DO NOT MODIFY THIS FILE
*/
#include <lm35.h>
LM35::LM35()
{
}
void LM35::setup()
{
    pinMode(PIN_LM35, INPUT);
}
float LM35::getTemp()
{
    int analogValue = analogRead(PIN_LM35);
    float millivolts = (analogValue / 1024.0) * 5000;
    float c = millivolts / 10;
    return (c * 1.8) + 32;
}
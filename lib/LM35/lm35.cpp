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
    float t = temp / ticks;
    ticks = 0;
    temp = 0;
    return t;
}
void LM35::run()
{
    int analogValue = analogRead(PIN_LM35);
    float millivolts = (analogValue / 1024.0) * 3300;
    float c = millivolts / 10;
    temp += (c * 1.8) + 32;
    ticks++;
}
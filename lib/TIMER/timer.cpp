#include "timer.h"

void TIMER::setInterval(unsigned long _interval, CALLBACK f)
{
    interval = _interval;
    callback = f;
}

void TIMER::run()
{
    unsigned long ms = millis();
    if (ms - last_ms > interval)
    {
        callback();
        last_ms = ms;
    }
}

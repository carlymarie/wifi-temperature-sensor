/**
 * DO NOT MODIFY THIS FILE
*/
#ifndef LM35_H_
#define LM35_H_

#include <pin_mapping.h>
class LM35
{
public:
    LM35();
    void setup();
    void run();
    float getTemp();

private:
    float temp;
    long ticks;
};
#endif // LM35_H_
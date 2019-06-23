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
    float getTemp();
};
#endif // LM35_H_
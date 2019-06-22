#ifndef TIMER_H_
#define TIMER_H_
#include <Arduino.h>
typedef std::function<void(void)> CALLBACK;
class TIMER
{
public:
  void run();
  void setInterval(unsigned long _interval, CALLBACK f);

private:
  CALLBACK callback;
  unsigned long interval;
  unsigned long last_ms;
};
#endif // TIMER_H_

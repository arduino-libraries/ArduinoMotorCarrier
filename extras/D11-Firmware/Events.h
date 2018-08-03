#include "Arduino.h"

class TimedEvent {
  public:
    TimedEvent(void(*cb)(void* args), void* _args, int _howOften) {
      callback = cb;
      args = _args;
      howOften = _howOften;
    }
    void tryExec() {
      if (millis() < nextExecution && (nextExecution != 0)) {
        return;
      }
      callback(args);
      reschedule();
    }
  private:
    void(*callback)(void* args) = NULL;
    void* args;
    long howOften;
    unsigned long nextExecution = 0;
    void reschedule() {
      nextExecution = millis() + howOften;
    };
};

void executeTimedEvents();
void registerTimedEvent(void(*callback)(void* args), void* arg, int howOften);

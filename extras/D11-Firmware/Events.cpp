//#include "LinkedList.h"
#include "Events.h"

static uint8_t counter = 0;

TimedEvent* events[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void executeTimedEvents() {
  for (int i = 0; events[i] != NULL; i++) {
    events[i]->tryExec();
  }
}

void registerTimedEvent(void(*callback)(void* args), void* args, int howOften) {
  TimedEvent* evt = new TimedEvent(callback, args, howOften);
  events[counter++] = evt;
}

#ifndef _AANIMALS_INTERRUPTIONS
#define _AANIMALS_INTERRUPTIONS

#include <avr/interrupt.h>

class Interruptions {

 public:
  Interruptions(); // Constructor

  // These exist only with Adafruit_GFX (no subclass overrides)
  void
    no(),
    yes();
};

#endif // _AANIMALS_INTERRUPTIONS
// Author: Rogerio Lucas <rlucas@rlrobotics.ind.br>
// Date: 20/09/2011
//
#include "utils.h"

// nonblock delay
void nb_delay(unsigned long ms) {
  int i, c, r, b_ret=0;
  #define DELAY_STEP 5

  if (ms >= DELAY_STEP) { 
    c = ms/DELAY_STEP;
    r = ms % DELAY_STEP;
  }
  else {
    delay(ms);
    return;
  }

  for(i=0; i<c; i++)
  {
    while(Serial.available() > 0)
    {
      Serial.read();
      b_ret = 1;
    }
    if(b_ret)
      return;

    delay(DELAY_STEP);
  }

  if(r)
    delay(r);
}

// return true after time defined in t have elapsed
boolean after(unsigned long value, unsigned long *t) {
  unsigned long ms;

  ms = (unsigned long)millis();

  if(ms > (*t+value)) {
    *t = (unsigned long)ms;
    return true;
  }

  return false;
}

// nonblock read serial
byte serial_read(void)
{
  byte key;

  if (Serial.available() > 0) {
    key = Serial.read();

    return key;
  }

  return 0;
}




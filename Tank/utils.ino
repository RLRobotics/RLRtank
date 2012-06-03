// Author: Roger <rlucas@rlrobotics.ind.br>
// Site: www.rlrobotics.ind.br
// Date: 20/05/2012
//
#include "utils.h"

boolean __g_bHeaderOK = false;
int __g_header_cnt = 0;
int __g_buf_count=0;

// non block delay
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
  else
    delayMicroseconds(10);

  return false;
}

// read nunchuck data joystick and accelerometer
boolean read_numchunk(uint8_t *buf, int len) {
  int i;
  int val;
  int Serial_len;

  if(!__g_bHeaderOK) {
    if(Serial.available()) {
      val = (uint8_t)Serial.read();

      if(!__g_header_cnt
        && val == (SYNC_CODE >> 8 & 0xff)) {
        __g_header_cnt++;
      }
      else if(__g_header_cnt == 1
        && val == (SYNC_CODE & 0xff)) {
        __g_bHeaderOK = true;
        __g_header_cnt = 0;
      }
      else
        __g_header_cnt = 0;
    }
  }
  else {

    __g_buf_count = 0;
    do {
      while(!Serial.available());

      buf[__g_buf_count] = (uint8_t)Serial.read();
    }
    while(++__g_buf_count < len);

    __g_bHeaderOK = false;
    return true;
  }

  return false;
}

// read serial data
int serial_read(void)
{
  int key;

  if (Serial.available() > 0) {
    key = Serial.read();

    return key;
  }

  return 0;
}


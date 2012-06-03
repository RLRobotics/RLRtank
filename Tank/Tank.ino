// Author: Roger <rlucas@rlrobotics.ind.br>
// Site: www.rlrobotics.ind.br
// Date: 20/05/2012
//
#include <Wire.h>
#include "Ultrasonic.h"
#include "nunchuck_funcs.h"
#include "Tank.h"
#include "utils.h"
#include "hbridge.h"

boolean cbut_state = false;
boolean zbut_state = false;
boolean bEnable = false;
unsigned long time=0;

#define EN1 8
#define EN2 9
#define EN3 10
#define EN4 11
#define ENA 5
#define ENB 6

Hbridge hbridge(EN1, EN2, EN3, EN4, ENA, ENB);

void setup()
{
  Serial.begin(9600);
  Serial.println("Tank ON");
}

void loop()
{
  long cm;
  numchuck_t n;

  if(after(15, &time))
  {
    if(read_numchunk((uint8_t*)&n, sizeof(n)))
    {
      if(n.zbut) {
        if(!zbut_state) {
          //Serial.println("ZBUT");
          hbridge.stop();
          zbut_state = true;
          bEnable = !bEnable;
        }
      }
      else {
        zbut_state = false;

        if(n.cbut) {
          if(!cbut_state) {
            if(bEnable) {
              //Serial.println("CBUT");
              hbridge.stop();
              cbut_state = true;
              hbridge.rotate_axis = !hbridge.rotate_axis;
              digitalWrite(LEDPIN, hbridge.rotate_axis);
            }
          }
        }
        else
          cbut_state = false;
      }

      if(n.joyx >= 160 && n.joyx <= 180
        && n.joyy >= 160 && n.joyy <= 180) {
        if(bEnable) 
        {
          //Serial.println("STOP");
          hbridge.stop();
        }
      }
      else
      {
        if(n.joyx > 40 && n.joyx < 85) {
          if(bEnable) {
            hbridge.left(75, 150);
          }
        }
        else if(n.joyx > 200) {
          if(bEnable) {
            hbridge.right(150, 75);
          }
        }
        else if(n.joyy > 40 && n.joyy < 85) {
          if(bEnable) {
            hbridge.backward(150, 150);
            //Serial.println("BACKWARD");
          }
        }
        else if(n.joyy > 200) {
          if(bEnable) {
            hbridge.forward(150, 150);
            //Serial.println("FORWARD");
          }
        }
      }
    }
  }
}


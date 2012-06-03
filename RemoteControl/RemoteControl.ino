// Author: Rogerio Lucas <rlucas@rlrobotics.ind.br>
// Date: 20/09/2011
//
#include <Wire.h>
#include "RemoteControl.h"
#include "utils.h"
#include "nunchuck_funcs.h"

int ledPin = 13;
unsigned long time = 0;

void setup()
{
  Serial.begin(9600);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
}

void loop()
{
  numchuck_t n;

  // Aguarda 80 milesegundos ate a proxima leitura
  if(after(80, &time))
  {
    nunchuck_get_data();
    n.accx  = (uint8_t)nunchuck_accelx(); // ranges from approx 70 - 182
    n.accy  = (uint8_t)nunchuck_accely(); // ranges from approx 65 - 173
    n.joyx = (uint8_t)nunchuck_joyx();
    n.joyy = (uint8_t)nunchuck_joyy();
    n.zbut = (uint8_t)nunchuck_zbutton();
    n.cbut = (uint8_t)nunchuck_cbutton();

    // Codigos de controle 
    Serial.write(SYNC_CODE >> 8 & 0xff);
    Serial.write(SYNC_CODE & 0xff);
    
    // Valores Numchuck (joystick + acelerometro)
    Serial.write((uint8_t*)&n, sizeof(n));
  }
}









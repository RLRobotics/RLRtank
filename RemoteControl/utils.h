// Author: Rogerio Lucas <rlucas@rlrobotics.ind.br>
// Date: 20/09/2011
//
#ifndef D_UTILS_H
#define D_UTILS_H

#define printf(a) Serial.println(a)
#define SYNC_CODE 0xfeef
#define SERIAL_TIMEOUT 1000
#pragma pack(1)

typedef struct {
  uint8_t accx : 8;
  uint8_t accy : 8;
  uint8_t joyx : 8;
  uint8_t joyy : 8;
  uint8_t zbut : 8;
  uint8_t cbut : 8;
} numchuck_t;

byte serial_read(void);
void nb_delay(unsigned long ms);
boolean after(unsigned long value, unsigned long *t);

#endif

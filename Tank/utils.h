// Author: Roger <rlucas@rlrobotics.ind.br>
// Site: www.rlrobotics.ind.br
// Date: 20/05/2012
//
#ifndef D_UTILS_H
#define D_UTILS_H

#define SYNC_CODE 0xfeef
#define SERIAL_TIMEOUT 1000

enum {
  IFORWARD=1, IBACKWARD, ILEFT, IRIGHT, ISTOP, IZ, IC};

#define printf(a) Serial.println(a)

#pragma pack(1)

typedef struct {
  uint8_t accx : 8;
  uint8_t accy : 8;
  uint8_t joyx : 8;
  uint8_t joyy : 8;
  uint8_t zbut : 8;
  uint8_t cbut : 8;
} numchuck_t;

int serial_read(void);
boolean read_numchunk(numchuck_t *w);
void nb_delay(unsigned long ms);
boolean after(unsigned long value, unsigned long *t);

#endif

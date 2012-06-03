// Author: Roger <rlucas@rlrobotics.ind.br>
// Site: www.rlrobotics.ind.br
// Date: 20/05/2012
//
#ifndef D_HBRIDGE_H
#define D_HBRIDGE_H

#include "Arduino.h"

enum {
  DSTOP=1, DFORWARD, DBACKWARD, DLEFT, DRIGHT, DXLEFT, DXRIGHT};

// default min and max speed
#define HB_SPEED_MIN 64
#define HB_SPEED_MAX 200

class Hbridge
{
  private:
    int _speed_min, _speed_max;
    int last_speed, last_dir;
    int back_forward;
    int en1, en2, en3, en4, ena, enb;

  public:
    boolean rotate_axis;

    Hbridge(int en1, int en2, int en3, int en4, int ena, int enb);
    void forward(int, int);
    void backward(int, int);
    void left(int, int);
    void right(int, int);
    void stop(void);
    boolean speed(int, int);
    void speed_min(int);
    void speed_max(int);
};

#endif

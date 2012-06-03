// Author: Roger <rlucas@rlrobotics.ind.br>
// Site: www.rlrobotics.ind.br
// Date: 20/05/2012
//
#include "hbridge.h"

Hbridge::Hbridge(
  int _en1,
  int _en2,
  int _en3,
  int _en4,
  int _ena,
  int _enb)
{
  last_dir = 0;
  en1 = _en1;
  en2 = _en2;
  en3 = _en3;
  en4 = _en4;
  ena = _ena;
  enb = _enb;

  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(en4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
}

// move forward
void Hbridge::forward(int a, int b)
{
  if(last_dir == DFORWARD)
    return;

  last_dir = DFORWARD;
  back_forward = DFORWARD;

  digitalWrite(en3, HIGH);
  digitalWrite(en1, HIGH);
  digitalWrite(en4, LOW);
  digitalWrite(en2, LOW);
  speed(a, b);
}

// move backward
void Hbridge::backward(int a, int b)
{
  if(last_dir == DBACKWARD)
    return;

  last_dir = DBACKWARD;
  back_forward = DBACKWARD;

  digitalWrite(en4, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(en3, LOW);
  digitalWrite(en1, LOW);
  speed(a, b);
}

// turn left
void Hbridge::left(int a, int b)
{
  if(last_dir == DLEFT)
    return;

  if(rotate_axis) {
    digitalWrite(en3, LOW);
    digitalWrite(en1, HIGH);
    digitalWrite(en4, HIGH);
    digitalWrite(en2, LOW);
    speed(a, b);
    return;
  }

  if(back_forward == DFORWARD) {
    digitalWrite(en3, HIGH);
    digitalWrite(en1, HIGH);
    digitalWrite(en4, LOW);
    digitalWrite(en2, LOW);
    speed(a, b);
  }
  else if (back_forward == DBACKWARD) {
    digitalWrite(en4, HIGH);
    digitalWrite(en2, HIGH);
    digitalWrite(en3, LOW);
    digitalWrite(en1, LOW);
    speed(a, b);
  }
  last_dir = DLEFT;
}

// turn right
void Hbridge::right(int a, int b)
{
  if(last_dir == DLEFT)
    return;

  if(rotate_axis) {
    digitalWrite(en3, HIGH);
    digitalWrite(en1, LOW);
    digitalWrite(en4, LOW);
    digitalWrite(en2, HIGH);
    speed(a, b);
    return;
  }

  if(back_forward == DFORWARD) {
    digitalWrite(en3, HIGH);
    digitalWrite(en1, HIGH);
    digitalWrite(en4, LOW);
    digitalWrite(en2, LOW);
    speed(a, b);
  }
  else if (back_forward == DBACKWARD) {
    digitalWrite(en4, HIGH);
    digitalWrite(en2, HIGH);
    digitalWrite(en3, LOW);
    digitalWrite(en1, LOW);
    speed(a, b);
  }
  last_dir = DLEFT;
}

// stop motors
void Hbridge::stop()
{
  last_dir = DSTOP;

  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite(en3, LOW);
  digitalWrite(en4, LOW);

  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

// speed direction of motors
boolean Hbridge::speed(int a, int b) {

  analogWrite(ena, a);
  analogWrite(enb, b);

  return true;
}
 

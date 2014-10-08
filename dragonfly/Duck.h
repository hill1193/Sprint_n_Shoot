// Duck.h
//
#ifndef __DUCK_H__
#define __DUCK_H__

#include "EventKeyboard.h"
#include "Object.h"
#include "EventCollision.h"
#include "Hero.h"

class Duck : public Hero {

 friend class Hero;
 
 private:
  int fire_countdown;
  PowerupType power;
  int power_countdown;
  void hit(EventCollision *p_c);
  void step();
  int timer;

 public:
  Duck();
  ~Duck();
  int eventHandler(Event *p_e);
};
#endif

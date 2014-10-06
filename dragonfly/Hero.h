// Hero.h
//

#include "EventKeyboard.h"
#include "Object.h"

class Hero : public Object {

 private:
  int fire_slowdown;
  int fire_countdown;
  void kbd(EventKeyboard *keyboard_event);
  void fire();
  void step();
  void jump();
  void duck();

 public:
  Hero();
  ~Hero();
  int eventHandler(Event *p_e);
};

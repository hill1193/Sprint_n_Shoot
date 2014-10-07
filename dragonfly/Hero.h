// Hero.h
//

#include "EventKeyboard.h"
#include "Object.h"

enum PowerupType {
	INVINCIBILITY,
	RAPID_FIRE,
};

class Hero : public Object {

 private:
  int fire_slowdown;
  int fire_countdown;
  PowerupType power;
  int power_countdown;
  void kbd(EventKeyboard *keyboard_event);
  void hit(EventCollision *p_c);
  void fire();
  void step();
  void jump();
  void duck();

 public:
  Hero();
  ~Hero();
  int eventHandler(Event *p_e);
};

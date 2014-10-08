// Hero.h
//

#ifndef __HERO_H__
#define __HERO_H__

#include "EventKeyboard.h"
#include "Object.h"
#include "EventCollision.h"

#define FLOOR_Y world_manager.getBoundary().getVertical()-8  // Y-coordinate of floor
#define GRAVITY 0.05  // Strength of gravity (i.e. delta y velocity per step in air)
#define FIRE_RATE 45 // Normal delay after shooting
#define RAPID_FIRE_RATE 10 // Delay after shooting with RAPID_FIRE power
#define NUMBER_POWERS 2 // Number of different powerup pbjects

enum PowerupType {
	INVINCIBILITY,
	RAPID_FIRE,
	NO_POWER,
};

class Hero : public Object {

 private:
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
  Hero(string sprite);
  ~Hero();
  int eventHandler(Event *p_e);
  
};

#endif

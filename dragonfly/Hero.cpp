//
// Hero.cpp
//

// Engine includes.
#include "EventStep.h"
#include "EventView.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Bullet.h"
#include "GameOver.h"
#include "Hero.h"

#define FLOOR_Y world_manager.getBoundary().getVertical()-8  // Y-coordinate of floor
#define GRAVITY 0.5  // Strength of gravity (i.e. delta y velocity per step in air)
#define FIRE_RATE 45 // Normal delay after shooting
#define RAPID_FIRE_RATE 10 // Delay after shooting with RAPID_FIRE power

Hero::Hero() {

  // Link to "hero" sprite.
  ResourceManager &resource_manager = ResourceManager::getInstance();
  LogManager &log_manager = LogManager::getInstance();
  Sprite *p_temp_sprite;
  p_temp_sprite = resource_manager.getSprite("hero");
  if (!p_temp_sprite) {
    log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "hero");
  } else {
    setSprite(p_temp_sprite);
	setSpriteSlowdown(3);
	setTransparency();
  }

  // Player controls hero, so register with keyboard.
  registerInterest(DF_KEYBOARD_EVENT);

  // Need to update fire rate control each step.
  registerInterest(DF_STEP_EVENT);

  // Set object type.
  setType("Hero");
  
  // Set object ID.
  setId(5);

  // Set starting location.
  WorldManager &world_manager = WorldManager::getInstance();
  Position pos(7, world_manager.getBoundary().getVertical()/2);
  setPosition(pos);

  // Set firing variables.
  fire_slowdown = 15;
  fire_countdown = fire_slowdown;
}

Hero::~Hero() {

  // Create GameOver object.
  GameOver *p_go = new GameOver;

}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_KEYBOARD_EVENT) {
    EventKeyboard *p_keyboard_event = static_cast <EventKeyboard *> (p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == DF_STEP_EVENT) {
    step();
    return 1;
  }
  
  if (p_e->getType() == DF_COLLISION_EVENT) {
	EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
	hit(p_collision_event);
	return 1;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(EventKeyboard *p_keyboard_event) {
  WorldManager &world_manager = WorldManager::getInstance();

  switch(p_keyboard_event->getKey()) {
  case KEY_UP:       // up arrow
    jump();
    break;
  case KEY_DOWN:     // down arrow
    duck();
    break;
  case ' ':          // fire
    fire();
    break;
  case 'q':          // quit
    world_manager.markForDelete(this);
    break;
  };

  return;
}

void Hero::hit(EventCollision *p_c) {
	if (power == INVINCIBILITY) return;  // Ignore all collisions when invincible

	// If wall or enemy, die
	// If powerup, set power state and countdown
}

// Move up or down.
void Hero::jump() {
  WorldManager &world_manager = WorldManager::getInstance();
  if (pos.getY() == FLOOR_Y) // Have to be on the ground to jump
	setYVelocity(-5);
	
}

// Fire bullet.
void Hero::fire() {
  if (fire_countdown > 0)
    return;
  if (power != RAPID_FIRE)
    fire_countdown = FIRE_RATE;
  else fire_countdown = RAPID_FIRE_RATE;
  new Bullet(getPosition());
}

// Decrease fire/power timers and simulate gravity
void Hero::step() {
  fire_countdown--;
  power_countdown--;
  
  if (fire_countdown < 0)
    fire_countdown = 0;
  if (power_countdown < 0) {
    power_countdown = 0;
	power = NO_POWER;
  }	
  
  if (pos.getY() != FLOOR_Y)
	setYVelocity(getYVelocity() + GRAVITY);
  else setYVelocity(0);
}

void Hero::duck() {

}

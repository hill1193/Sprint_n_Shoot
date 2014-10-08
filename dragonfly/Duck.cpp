//
// Duck.cpp
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
#include "Duck.h"

Duck::Duck() {
  timer = 25;
  // Link to "duck" sprite.
  ResourceManager &resource_manager = ResourceManager::getInstance();
  LogManager &log_manager = LogManager::getInstance();
  Sprite *p_temp_sprite;
  p_temp_sprite = resource_manager.getSprite("duck");
  if (!p_temp_sprite) {
    log_manager.writeLog("Duck::Duck(): Warning! Sprite '%s' not found", "duck");
  } else {
    setSprite(p_temp_sprite);
	setSpriteSlowdown(3);
	setTransparency();
  }

  // Need to update fire rate control each step.
  registerInterest(DF_STEP_EVENT);

  // Set object type.
  setType("Hero");
  
  // Set object ID.
  setId(6);

  // Set starting location.
  WorldManager &world_manager = WorldManager::getInstance();
  Position pos(7, FLOOR_Y);
  setPosition(pos);

  // Set firing variables.
  fire_countdown = 0;
}

Duck::~Duck() {

}

// Handle event.
// Return 0 if ignored, else 1.
int Duck::eventHandler(Event *p_e) {

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


void Duck::hit(EventCollision *p_c) {
	if (power == INVINCIBILITY) return;  // Ignore all collisions when invincible

	// If wall or enemy, die
	// If powerup, set power state and countdown
}


// Decrease fire/power timers and simulate gravity
void Duck::step() {
  WorldManager &world_manager = WorldManager::getInstance();
  fire_countdown--;
  power_countdown--;
  timer--;
  
  if (fire_countdown < 0)
    fire_countdown = 0;
  if (power_countdown < 0) {
    power_countdown = 0;
	power = NO_POWER;
  }	
  
   if (this->getPosition().getY() != FLOOR_Y)
	setYVelocity(getYVelocity() + GRAVITY);
  else setYVelocity(0);
  
    if(this->getPosition().getY() > FLOOR_Y) {
		Position temp_pos = getPosition();
		temp_pos.setY(FLOOR_Y);
		setPosition(temp_pos);
		}
		
    if(timer == 0) {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(this);
    new Hero;
  }
}

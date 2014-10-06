//
// Bullet.cpp
//

// Engine includes.
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

// Game includes.
#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(Position hero_pos) {

  // Link to "bullet" sprite.
  ResourceManager &resource_manager = ResourceManager::getInstance();
  
  Sprite *p_temp_sprite;
	
	p_temp_sprite = resource_manager.getSprite("bullet");
	setXVelocity(1);		// move 1 space right every frame
	
  if (!p_temp_sprite) {
    LogManager &log_manager = LogManager::getInstance();
    log_manager.writeLog("Bullet::Bullet(): Warning! Sprite '%s' not found", "bullet");
  } else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(5);		
  }

  // Set starting location, based on hero's position passed in.
  Position pos(hero_pos.getX()+3, hero_pos.getY());
  setPosition(pos);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_OUT_EVENT) {
    out();
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

// If bullet moves outside world, mark self for deletion.
void Bullet::out() {
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.markForDelete(this);
}

// If bullet hits Enemy, mark Enemy and bullet for deletion.
void Bullet::hit(EventCollision *p_c) {
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.markForDelete(p_c->getObject1());
  world_manager.markForDelete(p_c->getObject2());
}

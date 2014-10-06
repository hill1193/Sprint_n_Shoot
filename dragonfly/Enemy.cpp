//
// Enemy.cpp
//
 
#include <stdlib.h>		// for random()

// Engine includes.
#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "Points.h"
#include "Enemy.h"
#include "Hero.h"

Enemy::Enemy() {
  LogManager &log_manager = LogManager::getInstance();
  ResourceManager &resource_manager = ResourceManager::getInstance();

  // Setup "enemy" sprite.
  Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("enemy");
	setXVelocity(-1.00);
	// Set object type.
	setType("Enemy");
	}

	
  else {
	p_temp_sprite = resource_manager.getSprite("enemy");
	setXVelocity(-0.25);
	registerInterest(NUKE_EVENT);
  }
  if (!p_temp_sprite) {
    log_manager.writeLog("Enemy::Enemy(): Warning! Sprite '%s' not found",
			 "enemy");
  } else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(4);		
  }


  moveToStart();

}

Enemy::~Enemy() {
  // Send "view" event with points to interested ViewObjects.
  // Add 10 points.
  EventView ev(POINTS_STRING, 10, true);
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.onEvent(&ev);
}

// Handle event.
// Return 0 if ignored, else 1.
int Enemy::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == DF_COLLISION_EVENT) {
    EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == NUKE_EVENT) {
 
    // Create explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());
 
    // Delete self.
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(this);
 
    // Enemys appear stay around perpetually
    new Enemy;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// If moved off left edge, move back to far right.
void Enemy::out() {

  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;

  // Otherwise, move back to far right.
  moveToStart();

  // Spawn new Enemy to make the game get harder.
  new Enemy;

}

// If enemy and player collide, mark both for deletion.
void Enemy::hit(EventCollision *p_c) {

  // If Enemy on Enemy, ignore.
  if ((p_c -> getObject1() -> getType() == "Enemy") &&
      (p_c -> getObject2() -> getType() == "Enemy"))
    return;
	
  // If Fast on Enemy, Fast destroys Enemy
  if ((p_c -> getObject1() -> getType() == "Fast") &&
      (p_c -> getObject2() -> getType() == "Enemy")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c -> getObject2());
		}
  if ((p_c -> getObject1() -> getType() == "Enemy") &&
      (p_c -> getObject2() -> getType() == "Fast")) {
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c -> getObject1());
		}

  // If Bullet ...
  if ((p_c -> getObject1() -> getType() == "Bullet") ||
      (p_c -> getObject2() -> getType() == "Bullet")) {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Enemys appear stay around perpetually.
    new Enemy;
  }

  // If Hero, mark both objects for destruction.
  if (((p_c -> getObject1() -> getType()) == "Hero") || 
      ((p_c -> getObject2() -> getType()) == "Hero")) {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject1());
    world_manager.markForDelete(p_c -> getObject2());
  }

}

// Move enemy to starting location on right side of screen.
void Enemy::moveToStart() {
  WorldManager &world_manager = WorldManager::getInstance();
  Position temp_pos;

  // Get world boundaries.
  int world_horiz = world_manager.getBoundary().getHorizontal();
  int world_vert = world_manager.getBoundary().getVertical();

  // x is off right side of screen.
  temp_pos.setX(world_horiz + random()%world_horiz + 3);

  // y is in vertical range.
  temp_pos.setY(random()%(world_vert-4) + 4);

  // If collision, move right slightly until empty space.
  ObjectList collision_list = world_manager.isCollision(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1);
    collision_list = world_manager.isCollision(this, temp_pos);
  }

  world_manager.moveObject(this, temp_pos);
}

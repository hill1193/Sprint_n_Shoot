//
// Wall.cpp
//
 
#include <stdlib.h>		// for random()

// Engine includes.
#include "EventCollision.h"
#include "EventOut.h"
#include "EventView.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "Points.h"
#include "Wall.h"
#include "Hero.h"

Wall::Wall() {
  LogManager &log_manager = LogManager::getInstance();
  ResourceManager &resource_manager = ResourceManager::getInstance();

  // Setup "wall" sprite.
  Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("wall");
	setXVelocity(-1.00);
	// Set object type.
	setType("Wall");
	

  if (!p_temp_sprite) {
    log_manager.writeLog("Wall::Wall(): Warning! Sprite '%s' not found",
			 "wall");
  } else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(4);		
  }


  moveToStart();

}

Wall::~Wall() {
  // Send "view" event with points to interested ViewObjects.
  // Add 10 points.
  EventView ev(POINTS_STRING, 10, true);
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.onEvent(&ev);
}

// Handle event.
// Return 0 if ignored, else 1.
int Wall::eventHandler(Event *p_e) {

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

// If moved off left edge, move back to far right.
void Wall::out() {

  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;

  // Otherwise, move back to far right.
  moveToStart();

}

// If wall and player collide, mark both for deletion.
void Wall::hit(EventCollision *p_c) {

  // If Wall on Wall, ignore.
  if ((p_c -> getObject1() -> getType() == "Wall") &&
      (p_c -> getObject2() -> getType() == "Wall"))
    return;
	

  // If Bullet ...
  if (p_c -> getObject1() -> getType() == "Bullet") {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject1());
	}
  if (p_c -> getObject2() -> getType() == "Bullet") {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject2());
  }

  // If Hero, mark both objects for destruction.
  if ((p_c -> getObject1() -> getType()) == "Hero") {
	WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject1());
	}
  if ((p_c -> getObject2() -> getType()) == "Hero") {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject2());
  }

}

// Move wall to starting location on right side of screen.
void Wall::moveToStart() {
  WorldManager &world_manager = WorldManager::getInstance();
  Position temp_pos;

  // Get world boundaries.
  int world_horiz = world_manager.getBoundary().getHorizontal();
  int world_vert = world_manager.getBoundary().getVertical();

  // x is off right side of screen.
  temp_pos.setX(world_horiz + random()%world_horiz + 3);

  // y is in vertical range.
  if (random() % 2 == 1)
	temp_pos.setY(FLOOR_Y + 2);
  else
    temp_pos.setY(FLOOR_Y - 3);

  // If collision, move right slightly until empty space.
  ObjectList collision_list = world_manager.isCollision(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1);
    collision_list = world_manager.isCollision(this, temp_pos);
  }

  world_manager.moveObject(this, temp_pos);
}

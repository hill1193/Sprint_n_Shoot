#include "Powerup.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Hero.h"
#include <stdlib.h>

Powerup::Powerup() {
	ResourceManager &resource_manager = ResourceManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();
	
	Sprite *p_temp_sprite;
	
	int power_type = random()%NUMBER_POWERS;
	
	if (power_type == 0) {
		p_temp_sprite = resource_manager.getSprite("invincibility");
		power = INVINCIBILITY;
	} 
	if (power_type == 1) {
		p_temp_sprite = resource_manager.getSprite("rapid_fire");
		power = RAPID_FIRE;
	}
	
	if (!p_temp_sprite) {
		log_manager.writeLog("Powerup::Powerup(): Warning! Sprite not found");	
	} else {
		setSprite(p_temp_sprite);
		setTransparency();
    }
	
	setType("Powerup");
	
	setXVelocity(-1);
	moveToStart();
}

void Powerup::setPower(PowerupType new_power) {
	this->power = new_power;
}

PowerupType Powerup::getPower() const {
	return this->power;
}

void Powerup::moveToStart() {
  WorldManager &world_manager = WorldManager::getInstance();
  Position temp_pos;

  // Get world boundaries.
  int world_horiz = world_manager.getBoundary().getHorizontal();
  int world_vert = world_manager.getBoundary().getVertical();

  // x is off right side of screen.
  temp_pos.setX(world_horiz + random()%world_horiz + 3);

  // y is in vertical range.
  if (random() % 2 == 1)
	temp_pos.setY(FLOOR_Y - 2);
  else
    temp_pos.setY(FLOOR_Y);

  // If collision, move right slightly until empty space.
  ObjectList collision_list = world_manager.isCollision(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1);
    collision_list = world_manager.isCollision(this, temp_pos);
  }

  world_manager.moveObject(this, temp_pos);
}

int Powerup::eventHandler(Event *p_e) {
	if (p_e->getType() == DF_COLLISION_EVENT) {
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}
}

void Powerup::hit(EventCollision *p_c) {
	if ((p_c->getObject1()->getType() == "Hero") ||
		(p_c->getObject2()->getType() == "Hero")) {
			WorldManager &world_manager = WorldManager::getInstance();
			world_manager.markForDelete(this);
	}
}
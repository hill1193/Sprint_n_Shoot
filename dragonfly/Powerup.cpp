#include "Powerup.h"
#include <stdlib.h>

Powerup::Powerup() {
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite;
	
	int power_type = random()%NUMBER_POWER;
	
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
	
	setXVelocity(-1);
}

void Powerup::setPowerup(PowerupType new_power) {
	this->power = new_power;
}

PowerupType Powerup::getPowerup() const {
	return this->power;
}

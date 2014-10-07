#include "Powerup.h"

Powerup::Powerup() {
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite;
	p_temp_sprite = resource_manager.getSprite("invincibility");
	if (!p_temp_sprite) {
    log_manager.writeLog("Powerup::Powerup(): Warning! Sprite '%s' not found", "invincibility");	
	} else {
		setSprite(p_temp_sprite);
		setTransparency();
    }
	power = INVINCIBILITY;
	setXVelocity(-1);
}

void Powerup::setPowerup(PowerupType new_power) {
	this->power = new_power;
}

PowerupType Powerup::getPowerup() const {
	return this->power;
}

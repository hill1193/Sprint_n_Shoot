#include "Object.h"
#include "Hero.h"

#define POWER_DURATION 300


class Powerup : public Object {
	private:
		PowerupType power;
		void moveToStart();
		void hit(EventCollision *p_c);
	public:
		Powerup();
		void setPower(PowerupType new_power);
		PowerupType getPower() const;
		int eventHandler(Event *p_e);
};

#include "Object.h"
#include "Hero.h"


class Powerup : public Object {
	private:
		PowerupType power;
		void moveToStart();
	public:
		Powerup();
		void setPower(PowerupType new_power);
		PowerupType getPower() const;
};

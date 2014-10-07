#include "Object.h"
#include "Hero.h"


class Powerup : public Object {
	private:
		PowerupType power;
	public:
		Powerup();
		void setPower(PowerupType new power);
		PowerupType getPower() const;
};

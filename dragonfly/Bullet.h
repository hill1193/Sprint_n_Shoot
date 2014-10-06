//
// Bullet.h
//

#include "EventCollision.h"
#include "Object.h"

class Bullet : public Object {

 private:
  void out();
  void hit(EventCollision *p_c);

 public:
  Bullet(Position hero_pos);
  int eventHandler(Event *p_e);
};

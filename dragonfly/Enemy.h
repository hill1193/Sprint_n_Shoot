//
// Enemy.h
//
 
#include "Object.h"
#include "EventCollision.h"
 
class Enemy : public Object {
 
 private:
  void moveToStart();
  void out();
  void hit(EventCollision *p_c);

 public:
  Enemy();
  ~Enemy();
  int eventHandler(Event *p_e);
};

//
// Wall.h
//
 
#include "Object.h"
#include "EventCollision.h"
 
class Wall : public Object {
 
 private:
  void moveToStart();
  void out();
  void hit(EventCollision *p_c);

 public:
  Wall();
  ~Wall();
  int eventHandler(Event *p_e);
};

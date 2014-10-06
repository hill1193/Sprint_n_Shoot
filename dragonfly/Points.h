//
// Points.h
// 

#include "Event.h"		
#include "ViewObject.h"

#define POINTS_STRING "Points"

class Points : public ViewObject {

 public:
  Points();
  int eventHandler(Event *p_e);
};

//
// Points.cpp
//

// Engine includes
#include "Event.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"

// Game includes.
#include "Points.h"

Points::Points() {
  setLocation(TOP_RIGHT);
  setViewString(POINTS_STRING);
  setColor(COLOR_YELLOW);
  // Need to update score each second, so count "step" events.
  registerInterest(DF_STEP_EVENT);
}

// Handle event.
// Return 0 if ignored, else 1.
int Points::eventHandler(Event *p_e) {

  // Parent handles event if score update.
  if (ViewObject::eventHandler(p_e)) {
    return 1;
  }

  // If step, increment score every second (30 steps).
  if (p_e->getType() == DF_STEP_EVENT) {
    if (static_cast <EventStep *> (p_e) -> getStepCount() % 30 == 0)
      setValue(getValue() + 1);
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

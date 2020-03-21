#include "object.h"

Object::Object() {
  active = true;
}

Object::~Object() {}

void Object::selfDestruct() {
  active = false;
}

bool Object::isActive() {
  return active;
}

DisplayableObject::DisplayableObject() {
  depth = 0.0f;
}

DisplayableObject::~DisplayableObject() {}

void DisplayableObject::setDepth(float _depth) {
  depth = _depth;
}

void MouseObject::setCursorPosition(float x, float y) {
  mousePointer = {x, y};
}

MouseObject::~MouseObject() {}

KeyboardObject::~KeyboardObject() {}

IdleObject::~IdleObject() {}

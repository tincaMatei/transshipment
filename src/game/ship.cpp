#include "game/ship.h"

Ship::Ship(float _speed) {
  elapsedTime = 0.0f;
  speed = _speed;
  freezed = false;
}

Ship::~Ship() {}

void Ship::addTime(float ammount) {
  elapsedTime += ammount;
}

void Ship::freezeShip() {
  freezed ^= 1;
}

bool Ship::isFreezed() {
  return freezed;
}

void Ship::destroyShip() {
  destroyed = true;
}

bool Ship::isDestroyed() {
  return destroyed;
}

#include "game/ship.h"

Ship::Ship(float _speed, float _unloadSpeed, int _maxFuel, int _capacity) {
  elapsedTime = 0.0f;
  
  speed = _speed;
  unloadSpeed = _unloadSpeed;
  maxFuel = fuel = _maxFuel;
  
  freezed = false;
  destroyed = false;
  
  for(int i = 0; i < MAX_RESOURCES; ++i)
    cargo[i] = request[i] = 0;
  
  totalAmmount = 0;
  totalCapacity = _capacity;
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

int Ship::getCargo(int poz) {
  return cargo[poz];
}

int Ship::getRequest(int poz) {
  return request[poz];
}

void Ship::addRequest(Resource res, int ammount) {
  request[res] += ammount;
}

void Ship::removeRequest(Resource res, int ammount) {
  request[res] -= ammount;
  if(request[res] < 0)
    request[res] = 0;
}

int Ship::getMaxFuel() {
  return maxFuel;
}

int Ship::getFuel() {
  return fuel;
}

int Ship::getCargoSize() {
  return totalCapacity;
}

int Ship::getCargoOccupied() {
  return totalAmmount;
}

#ifndef __SHIP_H
#define __SHIP_H

#include "object.h"
#include <deque>

enum Action {
  STAND = 0,
  GO_LEFT = 1,
  GO_RIGHT = 2,
  GO_UP = 3,
  GO_DOWN = 4
};

const int MAX_RESOURCES = 6;

enum Resource {
  IRON,
  COPPER,
  ICE_ROCK,
  FLAME_ROCK,
  PETROL,
  URANIUM
};

class Ship : public DisplayableObject,
             public MouseObject,
             public IdleObject {
protected:
  // Coordinates of the ship
  int l, c;
  // Fuel properties
  int fuel, maxFuel;
  // Elapsed time since last move
  float elapsedTime;
  // Speed of the ship
  float speed, unloadSpeed;
  // Properties of the ship
  // If we set the path of a ship, all other ships are freezed from moving
  bool freezed, destroyed;
  // The path of the ship
  std::deque<int> path;
  // The intended path of the ship aka the path drawn when trying to
  // decide the path
  std::deque<int> intendedPath;
  // Ship total cargo size
  int totalAmmount, totalCapacity;
  // Cargo of the ship
  int cargo[MAX_RESOURCES], request[MAX_RESOURCES];
public:
  Ship(float _speed, float _unloadSpeed, int _maxFuel, int _capacity);
  ~Ship();
  // Add time to elapsedTime
  void addTime(float ammount);
  // Freeze the ship
  void freezeShip();
  // Check if the ship freezes the game
  bool isFreezed();
  // Destroy the ship 
  virtual void destroyShip();
  // Check if the ship is destroyed
  bool isDestroyed();
  
  int getCargo(int poz);
  
  int getRequest(int poz);
  
  int getFuel();
  
  int getMaxFuel();
  
  int getCargoOccupied();
  
  int getCargoSize();
  
  virtual void display(SDL_Renderer* renderer) = 0;
  
  virtual void update() = 0;
  
  virtual void mouseButtonPress(int key) = 0;
  
  virtual void mouseButtonRelease(int key) = 0;
  
  virtual void mouseMotion(float _x, float _y) = 0;

  virtual void loadResource(Resource res, int ammount) = 0;
  
  virtual void unloadResource(Resource res, int ammount) = 0;
  
  virtual void addRequest(Resource res, int ammount);
  
  virtual void removeRequest(Resource res, int ammount);
};

int getShipPrice(int id);

#endif

#ifndef __STANDARD_SHIP_H
#define __STANDARD_SHIP_H

#include "game/ship.h"
#include "geometry.h"
#include "game/map.h"
#include "game/wallet.h"
#include "graphicshandler.h"

class StandardShip : public Ship {
private:
  bool modifying;
  Polygon* shape;
  Map* gameMap;
  Wallet* wallet;
  
  TextureContext* textureContext;
  int lT, cT;
  
  // Display a path with the last color set by SDL
  void displayPath(SDL_Renderer* renderer,
                   const std::deque<int> &drawpath);
  
  void islandAction();
  
  void moveShip();
  
  void doInventoryRestrictions();
public:
  StandardShip(float _speed, float _unloadspeed, int _l, int _c, 
               Map* _gameMap, int _capacity, int _maxFuel,
               Wallet* _wallet,
               TextureContext* _textureContext, int _lT, int _cT);
  
  ~StandardShip();
  
  
  virtual void destroyShip();
  
  virtual void display(SDL_Renderer* renderer);
  
  virtual void update();
  
  virtual void mouseButtonPress(int key);
  
  virtual void mouseButtonRelease(int key);
  
  virtual void mouseMotion(float _x, float _y);

  virtual void loadResource(Resource res, int ammount);
  
  virtual void unloadResource(Resource res, int ammount);
};

#endif

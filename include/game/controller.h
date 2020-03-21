#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "object.h"
#include <SDL2/SDL.h>
#include "game/map.h"
#include <vector>
#include "game/cell.h"
#include "game/standardship.h"
#include "timer.h"

class Controller : public DisplayableObject,
                   public MouseObject,
                   public KeyboardObject,
                   public IdleObject {
private:
  // Map of the entire world
  Map* gameMap;
  // stopwatch used for measuring times
  Timer stopWatch;
  
  // Two test ships
  StandardShip* testShip;
  StandardShip* testShip2;
  
public:
  Controller();
  ~Controller();
  
  void display(SDL_Renderer* renderer);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float xMouse, float yMouse);
  
  void keyPress(int key, bool repeat = false);
  
  void keyRelease(int key);
  
  void keyHold(const Uint8* state);
  
  void update();
};

#endif

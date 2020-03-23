#ifndef __BUTTON_H
#define __BUTTON_H

#include <SDL2/SDL.h>
#include "object.h"
#include "geometry.h"
#include "debugtools.h"
#include "graphicshandler.h"

class Button : public DisplayableObject, 
               public MouseObject {
protected:
  bool pressing, hovering, pressed;

  Polygon* body;
  
  TileSetRenderer* tsr;
  
  float x1, y1, w, h;
public:
  Button(float _x, float _y, float _w, float _h, TileSetRenderer* tsr = NULL);
  
  ~Button();
  
  bool isPressed();
  
  virtual void display(SDL_Renderer* renderer);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float _x, float _y);
  
  void resetButton();
};

#endif

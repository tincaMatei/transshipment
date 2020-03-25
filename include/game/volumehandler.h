#ifndef __VOLUMEHANDLER_H
#define __VOLUMEHANDLER_H

#include "object.h"
#include "game/button.h"
#include "graphicshandler.h"

class VolumeHandler : public DisplayableObject,
                      public MouseObject,
                      public IdleObject {
private:
  int* volumebar;
  
  Button* decreaseVol;
  Button* increaseVol;
  TextureContext* textureContext;
public:
  VolumeHandler(int* volume, TextureContext* _textureContext);
  
  ~VolumeHandler();
  
  void display(SDL_Renderer* renderer);
  
  void update();
  
  void mouseMotion(float _x, float _y);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
};

#endif

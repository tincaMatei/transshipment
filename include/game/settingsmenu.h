#ifndef __SETTINGSMENU_H
#define __SETTINGSMENU_H

#include "object.h"
#include "game/button.h"
#include "graphicshandler.h"

class SettingsMenu : public DisplayableObject, 
                     public MouseObject,
                     public IdleObject {
private:
  bool active, quit;
  
  Button* closeButton;
  Button* quitButton;
  
  TextureContext* textureContext;
public:
  SettingsMenu(TextureContext* _textureContext);
  ~SettingsMenu();
  
  void display(SDL_Renderer* renderer);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float _x, float _y);
  
  void toggleActive();
  
  void update();
  
  bool isActive();
  
  bool shouldClose();
};

#endif

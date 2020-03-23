#ifndef __SHIPGUI_H
#define __SHIPGUI_H

#include "graphicshandler.h"
#include "game/ship.h"
#include "game/button.h"
#include "game/island.h"
#include "game/wallet.h"
#include <vector>

class ShipGui : public DisplayableObject,
                public MouseObject,
                public IdleObject {
private:
  Ship* targetShip;
  Island* targetIsland;
  
  FontRenderer* fontRenderer;
  
  Button* invButton[MAX_RESOURCES][2];
  Button* exitGuiButton;
  
  TextureContext* textureContext;
  
  std::vector<Button*> buyButton;
  
  Wallet* wallet;
  
  void displayShip(SDL_Renderer* renderer);
  
  void displayIsland(SDL_Renderer* renderer);
  
  void displayStats(SDL_Renderer* renderer);
public:
  ShipGui(Wallet* _wallet, TextureContext* _textureContext);
  
  ~ShipGui();
  
  void setShip(Ship* _ship);
  
  void display(SDL_Renderer* renderer);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float _x, float _y);
  
  void update();
  
  void setIsland(Island* _island);
  
  std::vector<Button*> getButtons();
};

#endif

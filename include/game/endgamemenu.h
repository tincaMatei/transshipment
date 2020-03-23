#ifndef __ENDGAMEMENU_H
#define __ENDGAMEMENU_H

#include "object.h"
#include "game/button.h"
#include "graphicshandler.h"
#include "game/wallet.h"

class EndGameMenu : public DisplayableObject,
                    public MouseObject,
                    public IdleObject {
private:
  bool quit, restart, active;

  std::vector<Button*> buttons;

  Button* restartButton;
  Button* quitButton;
  
  TextureContext* textureContext;
  
  FontRenderer* fontRenderer;
  
  Wallet* wallet;
public:
  EndGameMenu(Wallet* _wallet, TextureContext* _textureContext);
  ~EndGameMenu();
  
  void update();
  
  void display(SDL_Renderer* renderer);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float _x, float _y);
  
  void spawn();
  
  bool shouldClose();
  
  bool shouldRestart();
};

#endif

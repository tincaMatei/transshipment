#ifndef __MAINMENU_H
#define __MAINMENU_H

#include <vector>
#include <SDL2/SDL.h>
#include "room.h"
#include "game/button.h"
#include "graphicshandler.h"

class MainMenu : public Room {
private:
  Button* playButton;
  Button* quitButton;
  
  std::vector<Button*> buttons;
  TextureContext* textureContext;
public:
  MainMenu(TextureContext* _textureContext);
  ~MainMenu();
  
  void render(SDL_Renderer* renderer);
  
  bool runGameLoop();
  
  void initialize();
};

#endif

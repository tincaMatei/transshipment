#ifndef __HELPROOM_H
#define __HELPROOM_H

#include "room.h"
#include "graphicshandler.h"
#include "game/button.h"

class HelpRoom : public Room {
private:
  Button* cancelButton;
  TextureContext* textureContext;
public:
  HelpRoom(TextureContext* textureContext);
  ~HelpRoom();
  
  void render(SDL_Renderer* renderer);
  
  void initialize();
  
  bool runGameLoop();
};

#endif

#ifndef __GAMEROOM_H
#define __GAMEROOM_H

#include "room.h"
#include "game/controller.h"
#include "graphicshandler.h"

class GameRoom : public Room {
private:
  Controller* controller;
  TextureContext* textureContext;
public:
  GameRoom(TextureContext* _textureContext);
  ~GameRoom();
  
  void initialize();
  
  bool runGameLoop();
  
  void render(SDL_Renderer* renderer);
};

#endif

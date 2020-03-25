#include "game/gameroom.h"

GameRoom::GameRoom(TextureContext* _textureContext, int *_volume) {
  controller = NULL;
  textureContext = _textureContext;
  volume = _volume;
}

GameRoom::~GameRoom() {
  if(controller != NULL) {
    delete controller;
    controller = NULL;
  }
}

void GameRoom::initialize() {
  if(controller != NULL) {
    delete controller;
    controller = NULL;
  }
  controller = new Controller(textureContext, volume);
}

bool GameRoom::runGameLoop() {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      transition = -1;
      return false;
    } else if(event.type == SDL_MOUSEMOTION)
      controller->mouseMotion((float)event.motion.x, (float)event.motion.y);
    else if(event.type == SDL_MOUSEBUTTONDOWN)
      controller->mouseButtonPress(event.button.button);
    else if(event.type == SDL_MOUSEBUTTONUP)
      controller->mouseButtonRelease(event.button.button);
    else if(event.type == SDL_KEYDOWN)
      controller->keyPress(event.key.keysym.sym);
    else if(event.type == SDL_KEYUP)
      controller->keyRelease(event.key.keysym.sym);
  }
  
  controller->update();
  if(controller->shouldClose()) {
    transition = MENU_ROOM;
    return false;
  } else if(controller->shouldRestart()) {
    transition = GAME_ROOM;
    return false;
  }
  
  return true;
}

void GameRoom::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
  
  controller->display(renderer);
}

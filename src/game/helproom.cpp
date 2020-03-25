#include "game/helproom.h"

HelpRoom::HelpRoom(TextureContext* _textureContext) {
  textureContext = _textureContext;
  cancelButton = new Button(400.0f, 570.0f, 100.0f, 40.0f, textureContext->cancelmenu);
}

HelpRoom::~HelpRoom() {
  delete cancelButton;
  cancelButton = NULL;
  textureContext = NULL;
}

void HelpRoom::initialize() {
  cancelButton->resetButton();
}

void HelpRoom::render(SDL_Renderer* renderer) {
  SDL_Rect rect = {0, 0, 800, 600};
  textureContext->helpmenu->renderTexture(renderer, 0, 0, rect);
  cancelButton->display(renderer);
}

bool HelpRoom::runGameLoop() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      transition = -1;
      return false;
    } else if(event.type == SDL_MOUSEMOTION)
      cancelButton->mouseMotion(event.motion.x, event.motion.y);
    else if(event.type == SDL_MOUSEBUTTONDOWN)
      cancelButton->mouseButtonPress(event.button.button);
    else if(event.type == SDL_MOUSEBUTTONUP)
      cancelButton->mouseButtonRelease(event.button.button);
  }

  if(cancelButton->isPressed()) {
    transition = MENU_ROOM;
    return false;
  }
  
  return true;
}

#include "game/mainmenu.h"

MainMenu::MainMenu(TextureContext* _textureContext) {
  textureContext = _textureContext;
  playButton = new Button(400, 300, 200, 80, textureContext->playmenu);
  quitButton = new Button(400, 400, 200, 80, textureContext->quitmenu);
  
  buttons.push_back(playButton);
  buttons.push_back(quitButton);
}

MainMenu::~MainMenu() {
  delete playButton;
  delete quitButton;
  
  playButton = quitButton = NULL;
}

void MainMenu::initialize() {
  playButton->resetButton();
  quitButton->resetButton();
}

void MainMenu::render(SDL_Renderer* renderer) {
  SDL_Rect rect = {0, 0, 800, 600};
  textureContext->wholemenu->renderTexture(renderer, 0, 0, rect);
  playButton->display(renderer);
  quitButton->display(renderer);
}

bool MainMenu::runGameLoop() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      transition = -1;
      return false;
    } else if(event.type == SDL_MOUSEMOTION)
      for(int i = 0; i < buttons.size(); ++i)
        buttons[i]->mouseMotion(event.motion.x, event.motion.y);
    else if(event.type == SDL_MOUSEBUTTONDOWN)
      for(int i = 0; i < buttons.size(); ++i)
        buttons[i]->mouseButtonPress(event.button.button);
    else if(event.type == SDL_MOUSEBUTTONUP)
      for(int i = 0; i < buttons.size(); ++i)
        buttons[i]->mouseButtonRelease(event.button.button);
  }
  
  if(playButton->isPressed()) {
    transition = GAME_ROOM;
    return false;
  } else if(quitButton->isPressed()) {
    transition = -1;
    return false;
  }
  
  return true;
}

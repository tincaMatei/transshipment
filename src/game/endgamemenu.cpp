#include "game/endgamemenu.h"

EndGameMenu::EndGameMenu(Wallet* _wallet, TextureContext* _textureContext) {
  quit = restart = active = false;
  
  textureContext = _textureContext;
  restartButton = new Button(400, 300, 100, 40, textureContext->playmenu);
  quitButton  = new Button(400, 350, 100, 40, textureContext->quitmenu);
  
  buttons.push_back(restartButton);
  buttons.push_back(quitButton);
  
  fontRenderer = new FontRenderer("media/FFFFORWA.TTF", 14);
  wallet = _wallet;
}

EndGameMenu::~EndGameMenu() {
  delete restartButton;
  delete quitButton;
  delete fontRenderer;
  
  restartButton = quitButton = NULL;
  fontRenderer = NULL;
  wallet = NULL;
  
  for(int i = 0; i < buttons.size(); ++i)
    buttons[i] = NULL;
}

void EndGameMenu::display(SDL_Renderer* renderer) {
  if(active) {
    SDL_Rect rect = {200, 200, 400, 200};
    textureContext->endgamegui->renderTexture(renderer, 0, 0, rect);
    
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    fontRenderer->renderText(renderer, 400, 230, "You went bankrupt!");
    std::string a = FontRenderer::inttostring(wallet->getPeak());
    fontRenderer->renderText(renderer, 400, 256, "Peak balance: " + a + "$");
    
    restartButton->display(renderer);
    quitButton->display(renderer);
  }
}

void EndGameMenu::update() {
  if(active) {
    if(restartButton->isPressed()) {
      restartButton->resetButton();
      restart = true;
    }
    if(quitButton->isPressed()) {
      quitButton->resetButton();
      quit = true;
    }
  }
}

void EndGameMenu::mouseButtonPress(int key) {
  if(active) {
    restartButton->mouseButtonPress(key);
    quitButton->mouseButtonPress(key);
  }
}

void EndGameMenu::mouseButtonRelease(int key) {
  if(active) {
    restartButton->mouseButtonRelease(key);
    quitButton->mouseButtonRelease(key);
  }
}

void EndGameMenu::mouseMotion(float _x, float _y) {
  if(active) {
    restartButton->mouseMotion(_x, _y);
    quitButton->mouseMotion(_x, _y);
  }
}

void EndGameMenu::spawn() {
  active = true;
}

bool EndGameMenu::shouldClose() {
  return quit;
}

bool EndGameMenu::shouldRestart() {
  return restart;
}

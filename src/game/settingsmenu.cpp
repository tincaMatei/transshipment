#include "game/settingsmenu.h"

SettingsMenu::SettingsMenu(TextureContext* _textureContext) {
  active = false;
  quit = false;
  
  textureContext = _textureContext;
  closeButton = new Button(400, 450, 100, 40, textureContext->cancelmenu);
  quitButton  = new Button(400, 500, 100, 40, textureContext->quitmenu);
}

SettingsMenu::~SettingsMenu() {
  delete closeButton;
  delete quitButton;
  
  textureContext = NULL;
  closeButton = quitButton = NULL;
}

void SettingsMenu::display(SDL_Renderer* renderer) {
  if(active) {
    SDL_Rect rect = {200, 50, 400, 500};
    textureContext->settingsmenugui->renderTexture(renderer, 0, 0, rect);
    
    closeButton->display(renderer);
    quitButton->display(renderer);
  }
}

void SettingsMenu::mouseButtonPress(int key) {
  if(active) {
    closeButton->mouseButtonPress(key);
    quitButton->mouseButtonPress(key);
  }
}

void SettingsMenu::mouseButtonRelease(int key) {
  if(active) {
    closeButton->mouseButtonRelease(key);
    quitButton->mouseButtonRelease(key);
  }
}

void SettingsMenu::mouseMotion(float _x, float _y) {
  if(active) {
    closeButton->mouseMotion(_x, _y);
    quitButton->mouseMotion(_x, _y);
  }
}

void SettingsMenu::update() {
  if(active) {
    if(closeButton->isPressed()) {
      closeButton->resetButton();
      active = false;
    } else if(quitButton->isPressed()) {
      quitButton->resetButton();
      active = false;
      quit = true;
    }
  }
}

void SettingsMenu::toggleActive() {
  active ^= 1;
}

bool SettingsMenu::shouldClose() {
  return quit;
}

bool SettingsMenu::isActive() {
  return active;
}

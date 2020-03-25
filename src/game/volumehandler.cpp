#include "game/volumehandler.h"
#include <SDL2/SDL_mixer.h>

VolumeHandler::VolumeHandler(int* volume, TextureContext* _textureContext) {
  volumebar = volume;
  
  textureContext = _textureContext;
  
  increaseVol = new Button(556, 200, 16, 16, _textureContext->plusButton);
  decreaseVol = new Button(420, 200, 16, 16, _textureContext->minusButton);
}

VolumeHandler::~VolumeHandler() {
  delete increaseVol;
  delete decreaseVol;
  increaseVol = NULL;
  decreaseVol = NULL;
  textureContext = NULL;
}

void VolumeHandler::display(SDL_Renderer* renderer) {
  increaseVol->display(renderer);
  decreaseVol->display(renderer);
  
  int x1, y1;
  x1 = 408;
  y1 = 168;
  
  for(int i = 0; i < *volumebar; ++i) {
    SDL_Rect rect = {x1 + 16 * i, y1, 16, 16};
    textureContext->volumedot->renderTexture(renderer, 0, 0, rect);
  }
}

void VolumeHandler::mouseMotion(float _x, float _y) {
  increaseVol->mouseMotion(_x, _y);
  decreaseVol->mouseMotion(_x, _y);
}

void VolumeHandler::mouseButtonPress(int key) {
  increaseVol->mouseButtonPress(key);
  decreaseVol->mouseButtonPress(key);
}

void VolumeHandler::mouseButtonRelease(int key) {
  increaseVol->mouseButtonRelease(key);
  decreaseVol->mouseButtonRelease(key);
}

void VolumeHandler::update() {
  if(increaseVol->isPressed()) {
    increaseVol->resetButton();
    (*volumebar)++;
    if(*volumebar > 10)
      *volumebar = 10;
    else
      Mix_VolumeMusic(MIX_MAX_VOLUME * (*volumebar) / 10);
  }
  
  if(decreaseVol->isPressed()) {
    decreaseVol->resetButton();
    (*volumebar)--;
    if(*volumebar < 0)
      *volumebar = 0;
    else
      Mix_VolumeMusic(MIX_MAX_VOLUME * (*volumebar) / 10);
  }
}

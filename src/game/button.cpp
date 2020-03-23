#include "game/button.h"

Button::Button(float _x, float _y, float _w, float _h, TileSetRenderer* _tsr) {
  hovering = pressed = pressing = false;
  tsr = _tsr;
  body = new Polygon(_x, _y, _w, _h);
  x1 = _x - _w / 2;
  y1 = _y - _h / 2;
  w = _w;
  h = _h;
}

Button::~Button() {
  delete body;
  body = NULL;
  tsr = NULL;
}

void Button::display(SDL_Renderer* renderer) {
  if(tsr != NULL) {
    SDL_Rect rect = {(int)x1, (int)y1, w, h};
    if(pressing)
      tsr->renderTexture(renderer, 2, 0, rect);
    else if(hovering)
      tsr->renderTexture(renderer, 1, 0, rect);
    else
      tsr->renderTexture(renderer, 0, 0, rect);
  } else {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    debugPolygon(renderer, body);
  }
}

void Button::mouseButtonPress(int key) {
  if(hovering && key == SDL_BUTTON_LEFT)
    pressing = true;
}

void Button::mouseButtonRelease(int key) {
  if(key == SDL_BUTTON_LEFT && pressing && hovering)
    pressed = true;
  if(key == SDL_BUTTON_LEFT)
    pressing = false;
}

void Button::mouseMotion(float _x, float _y) {
  mousePointer = {_x, _y};
  Polygon* poly = new Polygon(_x, _y);
  
  if(body->collides(poly))
    hovering = true;
  else
    hovering = false;
}

void Button::resetButton() {
  pressed = false;
}

bool Button::isPressed() {
  return pressed;
}

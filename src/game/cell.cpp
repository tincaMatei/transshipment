#include <SDL2/SDL.h>
#include "game/cell.h"
#include "debugtools.h"

Cell::Cell(int _l, int _c) {
  l = _l;
  c = _c;
  
  float x1, x2, y1, y2;
  
  x1 = 16.0f + _c * 32.0f;
  x2 = x1 + 32.0f - 1.0f;
  y1 = 136.0f + 32.0f * _l;
  y2 = y1 + 32.0f - 1.0f;
  
  body = new Polygon((x1 + x2) / 2.0f, (y1 + y2) / 2.0f, 31.0f, 31.0f);
  hovering = false;
  
  ship = NULL;
  shipwreck = false;
}

Cell::~Cell() {
  ship = NULL;
  delete body;
  body = NULL;
}

void Cell::display(SDL_Renderer* renderer) {
  if(shipwreck) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff); 
  } else {
    if(type == WATER)
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
    else if(type == ISLAND)
      SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
    else if(type == PORT)
      SDL_SetRenderDrawColor(renderer, 0xff, 0x3f, 0x00, 0x00);
    
    if(hovering)
      SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
  }
  debugPolygon(renderer, body);
}

void Cell::mouseButtonPress(int key) {
}

void Cell::mouseButtonRelease(int key) {
}

void Cell::mouseMotion(float _x, float _y) {
  mousePointer = {_x, _y};
  
  Polygon* dot = new Polygon(mousePointer.x, mousePointer.y);
  
  if(body->collides(dot))
    hovering = true;
  else
    hovering = false;
  
  delete dot;
  dot = NULL;
}

bool Cell::isHovering() {
  return hovering;
}

Polygon* Cell::getShape() {
  return body;
}

void Cell::setShip(Ship* _ship) {
  if(ship == NULL) {
    ship = _ship;
    if(ship != NULL && shipwreck) {
      ship->destroyShip();
      ship = NULL;
    } else if(ship != NULL && type != WATER) {
      ship->destroyShip();
      ship = NULL;
      shipwreck = true;
    }
  } else if(_ship != NULL) {
    shipwreck = true;
    _ship->destroyShip();
    ship->destroyShip();
    ship = NULL;
  } else {
    ship = NULL;
  }
}

Ship* Cell::getShip() {
  return ship;
}

bool Cell::getShipwreck() {
  return shipwreck;
}

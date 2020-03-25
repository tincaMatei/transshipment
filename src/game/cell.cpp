#include <SDL2/SDL.h>
#include "game/cell.h"
#include "debugtools.h"

Cell::Cell(int _l, int _c, TextureContext* _textureContext) : 
      Button(0.0f, 0.0f, 0.0f, 0.0f) {
  l = _l;
  c = _c;
  
  x1 = 16.0f + _c * 32.0f;
  x2 = x1 + 32.0f - 1.0f;
  y1 = 136.0f + 32.0f * _l;
  y2 = y1 + 32.0f - 1.0f;
  
  // God forgive
  delete body;
  body = new Polygon((x1 + x2) / 2.0f, (y1 + y2) / 2.0f, 31.0f, 31.0f);
  
  ship = NULL;
  island = NULL;
  hovering = false;
  shipwreck = false;
  textureContext = _textureContext;
  
  lT = cT = 0;
}

Cell::~Cell() {
  ship = NULL;
  delete body;
  body = NULL;
  island = NULL;
}

void Cell::display(SDL_Renderer* renderer) {
  textureContext->mapTiles->
                  renderTexture(renderer, lT, cT, {(int)x1, (int)y1, 32, 32});

  if(hovering) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    debugPolygon(renderer, body);
  }
}

void Cell::assignTile(int _lT, int _cT) {
  lT = _lT;
  cT = _cT;
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
      //ship->destroyShip();
      //ship = NULL;
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

void Cell::markShipwreck() {
  ship = NULL;
  shipwreck = true;
}

Ship* Cell::getShip() {
  return ship;
}

bool Cell::getShipwreck() {
  return shipwreck;
}

void Cell::setIsland(Island* _island) {
  island = _island;
}

bool Cell::resourceAvailable(Resource res) {
  if(island != NULL)
    return island->resourceAvailable(res);
  return false;
}

Island* Cell::getIsland() {
  return island;
}

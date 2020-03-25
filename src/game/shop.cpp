#include "game/shop.h"

Shop::Shop(Wallet* _wallet, Map* _gameMap, std::vector<Button*> _buttons,
           TextureContext* _textureContext) {
  wallet = _wallet;
  gameMap = _gameMap;
  buyButtons = _buttons;
  textureContext = _textureContext;
}

Shop::~Shop() {
  wallet = NULL;
  gameMap = NULL;
  for(int i = 0; i < buyButtons.size(); ++i)
    buyButtons[i] = NULL;
  for(int i = 0; i < boughtShips.size(); ++i)
    boughtShips[i] = NULL;
}

void Shop::addShip(int shipId) {
  int l = 0, c = 1;
  while(l < MAX_MAP_CELL_HEIGHT && gameMap->cellMap[l][c]->getShip() != NULL)
    ++l;
  
  if(l == MAX_MAP_CELL_HEIGHT)
    return;
  
  wallet->loseMoney(getShipPrice(shipId));
  
  if(shipId == 0) {
    boughtShips.push_back(
      new StandardShip(500.0f, 500.0f, l, c, gameMap, 5, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 1) {
    boughtShips.push_back(
      new StandardShip(500.0f, 500.0f, l, c, gameMap, 10, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 2) {
    boughtShips.push_back(
      new StandardShip(250.0f, 500.0f, l, c, gameMap, 5, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 3) {
    boughtShips.push_back(
      new StandardShip(500.0f, 100.0f, l, c, gameMap, 20, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 4) {
    boughtShips.push_back(
      new StandardShip(100.0f, 500.0f, l, c, gameMap, 5, 100, wallet, textureContext, shipId, 0));
  } else {
    boughtShips.push_back(
      new StandardShip(300.0f, 300.0f, l, c, gameMap, 10, 150, wallet, textureContext, shipId, 0));
  }
}

void Shop::update() {
  for(int i = 0; i < buyButtons.size(); ++i)
    if(buyButtons[i]->isPressed()) {
      buyButtons[i]->resetButton();
      addShip(i);
    }
}

std::vector<StandardShip*> Shop::finishContract() {
  std::vector<StandardShip*> rez = boughtShips;
  boughtShips.clear();
  return rez;
}

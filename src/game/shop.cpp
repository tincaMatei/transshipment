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
  
  if(shipId == 0) {
    wallet->loseMoney(2000);
    boughtShips.push_back(
      new StandardShip(500.0f, 500.0f, l, c, gameMap, 5, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 1) {
    wallet->loseMoney(3500);
    boughtShips.push_back(
      new StandardShip(500.0f, 500.0f, l, c, gameMap, 10, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 2) {
    wallet->loseMoney(3500);
    boughtShips.push_back(
      new StandardShip(250.0f, 500.0f, l, c, gameMap, 5, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 3) {
    wallet->loseMoney(4000);
    boughtShips.push_back(
      new StandardShip(500.0f, 100.0f, l, c, gameMap, 20, 70, wallet, textureContext, shipId, 0));
  } else if(shipId == 4) {
    wallet->loseMoney(8000);
    boughtShips.push_back(
      new StandardShip(100.0f, 500.0f, l, c, gameMap, 5, 100, wallet, textureContext, shipId, 0));
  } else {
    wallet->loseMoney(7000);
    boughtShips.push_back(
      new StandardShip(500.0f, 500.0f, l, c, gameMap, 5, 150, wallet, textureContext, shipId, 0));
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

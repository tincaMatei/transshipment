#ifndef __SHOP_H
#define __SHOP_H

#include "object.h"
#include "game/button.h"
#include "game/standardship.h"
#include "game/map.h"
#include "game/wallet.h"
#include "graphicshandler.h"

class Shop : public IdleObject {
private:
  std::vector<Button*> buyButtons;
  
  Map* gameMap;
  
  Wallet* wallet;
  
  void addShip(int shipId);
  
  TextureContext* textureContext;
public:
  Shop(Wallet* _wallet, Map* _gameMap, std::vector<Button*> _buyButtons,
       TextureContext* _textureContext);
  
  ~Shop();
  
  std::vector<StandardShip*> boughtShips;
  
  void update();
  
  std::vector<StandardShip*> finishContract();
};

#endif

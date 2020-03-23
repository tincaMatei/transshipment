#ifndef __REQUESTER_H
#define __REQUESTER_H

#include <vector>
#include <random>
#include "game/island.h"
#include "game/wallet.h"

struct IslandOrder {
  Island* client;
  
  int deadline, cut;
  bool activeOrder;
};

class Requester : IdleObject {
private:
  Wallet* wallet;

  std::vector<IslandOrder> islands;
  
  int orders, activeOrders;
  float passedTime, lastOrderT;
  
  float getGameDifficultyFactor();
  
  std::mt19937 mt_rand;
public:
  Requester(Wallet* _wallet, std::vector<Island*> _islands);
  
  ~Requester();
  
  void update();
  
  void addTime(float ammount);
};

#endif

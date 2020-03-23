#include "game/requester.h"
#include <SDL2/SDL.h>
#include <algorithm>

Requester::Requester(Wallet* _wallet, std::vector<Island*> _islands) {
  mt_rand = std::mt19937(SDL_GetTicks());
  for(int i = 0; i < _islands.size(); ++i)
    if(_islands[i]->getType() == REQUESTER)
      islands.push_back({_islands[i], 0, 0, false});
  wallet = _wallet;
  
  orders = activeOrders = 0;
  
  passedTime = 0.0f;
  lastOrderT = -20000.0f;
}

Requester::~Requester() {
  wallet = NULL;
  for(int i = 0; i < islands.size(); ++i)
    islands[i].client = NULL;
}

float Requester::getGameDifficultyFactor() {
  return passedTime / (600000.0f) + (float)orders / 100.0f;
}

void Requester::update() {
  float factor = getGameDifficultyFactor();
  float waitTime = (factor * (-20.0f) + 30.0f) * 1000.0f;

  
  if(waitTime < 10.0f)
    waitTime = 10.0f;
    
  for(int i = 0; i < islands.size(); ++i)
    if(islands[i].activeOrder) {
      if(passedTime >= islands[i].deadline) {
        islands[i].client->clearRequest();
        islands[i].activeOrder = false;
        activeOrders--;
      } else if(islands[i].client->isResolved()) {
        islands[i].client->setRemaining(-1.0f);
        wallet->gainMoney(islands[i].cut);
        islands[i].activeOrder = false;
        activeOrders--;
      } else if(islands[i].activeOrder) {
        islands[i].client->setRemaining(islands[i].deadline - passedTime);
      }
    }
  
  if(lastOrderT + waitTime <= passedTime) {
    lastOrderT += waitTime;
    
    if(activeOrders < islands.size()) {
      int clientId = mt_rand() % (islands.size() - activeOrders);
      
      for(int i = 0; i < islands.size(); ++i) {
        if(!islands[i].activeOrder) {
          if(clientId == 0) {
            islands[i].activeOrder = true;
            islands[i].cut = 200;
            
            int totalQuantity = (int)floor(factor * 10 + 1.0f);
            int nrRes = 0;
            std::vector<Resource> resources;
            
            if(factor < 0.2f) // Only first 3 resources
              nrRes = 3;
            else if(factor < 0.4f)
              nrRes = 4;
            else if(factor < 0.5f)
              nrRes = 5;
            else
              nrRes = 6;
            
            for(int i = 0; i < nrRes; ++i)
              resources.push_back(Resource(i));
            
            std::random_shuffle(resources.begin(), resources.end());
            
            for(int j = 0; j < nrRes && totalQuantity > 0; ++j) {
              int ammount = 1 + mt_rand() % totalQuantity;
              totalQuantity -= ammount;
              
              islands[i].cut += (getSellPrice(resources[j]) - getBuyPrice(resources[j])) * ammount;
              
              float deadlineCut = 2 * 60000.0f - factor * 60000.0f;
              if(deadlineCut < 60000.0f)
                deadlineCut = 60000.0f;
              
              islands[i].deadline = passedTime + deadlineCut;
              islands[i].client->pushRequest(resources[j], ammount);
            }
          }
          clientId--;
        }
      }
      
      activeOrders++;
      orders++;
    }
  }
}

void Requester::addTime(float ammount) {
  passedTime += ammount;
}

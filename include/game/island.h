#ifndef __ISLAND_H
#define __ISLAND_H

#include "game/ship.h"
#include "game/wallet.h"

enum IslandType {
  SUPPLIER,
  REQUESTER,
  GASSTATION,
  PORT
};

class Island {
private:
  IslandType type;

  Wallet* wallet;

  int resources;
  
  int request[MAX_RESOURCES];
  
  int totalRequest;
  
  float remainingTime;
public:
  Island(IslandType _type, Wallet* _wallet);
  
  bool resourceAvailable(Resource res);
  
  void giveResource(Resource res);
  
  IslandType getType();
  
  void pushRequest(Resource res, int ammount);
  
  int requestFuel(int ammount);
  
  void requestResource(Resource res);
  
  int getRequest(Resource res);
  
  void resolveRequest(Resource res);

  bool isResolved();
  
  void clearRequest();
  
  void setRemaining(float _x);
  
  float getRemaining();
};

int getBuyPrice(Resource res);

int getSellPrice(Resource res);

#endif

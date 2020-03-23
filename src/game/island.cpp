#include "game/island.h"

int resourceSellPrice[MAX_RESOURCES] = {100, 100, 200, 200, 200, 500};
int resourceBuyPrice[MAX_RESOURCES]  = { 80,  80, 160, 160, 160, 400};
const int FUEL_UNIT_PRICE = 10;

Island::Island(IslandType _type, Wallet* _wallet) {
  type = _type;
  resources = 0;
  wallet = _wallet;
  totalRequest = 0;
  
  remainingTime = -1.0f;
  
  for(int i = 0; i < MAX_RESOURCES; ++i)
    request[i] = 0;
  
  if(_type == SUPPLIER)
    resources = (1 << 6) - 1;
}

IslandType Island::getType() {
  return type;
}

bool Island::resourceAvailable(Resource res) {
  return ((1 << res) & resources) > 0;
}

void Island::giveResource(Resource res) {
  if(type == SUPPLIER)
    resources |= (1 << res);
}

void Island::pushRequest(Resource res, int ammount) {
  if(type == REQUESTER) {
    request[res] += ammount;
    totalRequest += ammount;
  }
}

int Island::requestFuel(int ammount) {
  if(type == GASSTATION) {
    wallet->loseMoney(ammount * FUEL_UNIT_PRICE);
    return ammount;
  }
  return 0;
}

void Island::requestResource(Resource res) {
  wallet->loseMoney(resourceBuyPrice[res]);
}

int Island::getRequest(Resource res) {
  return request[res];
}

void Island::resolveRequest(Resource res) {
  request[res]--;
  wallet->gainMoney(getSellPrice(res));
  totalRequest--;
}

void Island::clearRequest() {
  for(int i = 0; i < MAX_RESOURCES; ++i)
    request[i] = 0;
  totalRequest = 0;
}

bool Island::isResolved() {
  return totalRequest == 0;
}

int getSellPrice(Resource res) {
  return resourceSellPrice[res];
}

int getBuyPrice(Resource res) {
  return resourceBuyPrice[res];
}

void Island::setRemaining(float _x) {
  remainingTime = _x;
}

float Island::getRemaining() {
  return remainingTime;
}

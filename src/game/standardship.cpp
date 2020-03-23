#include "game/standardship.h"
#include "debugtools.h"

int dlShip[] = {0, 0, 0, -1, 1};
int dcShip[] = {0,-1, 1,  0, 0};

StandardShip::StandardShip(float _speed, float _unloadspeed, int _l, int _c, 
                           Map* _gameMap, int _capacity, int _maxFuel,
                           Wallet* _wallet,
                           TextureContext* _textureContext, int _lT, int _cT):
              Ship(_speed, _unloadspeed, _maxFuel, _capacity) {
  gameMap = _gameMap;
  l = _l;
  c = _c;
  
  wallet = _wallet;
  
  modifying = false;
  
  float x1, y1, x2, y2;
  x1 = 16.0f + _c * 32.0f;
  x2 = x1 + 32.0f - 1.0f;
  y1 = 136.0f + 32.0f * _l;
  y2 = y1 + 32.0f - 1.0f;
  
  shape = new Polygon((x1 + x2) / 2.0f, (y1 + y2) / 2.0f, 12.0f, 6);
  gameMap->cellMap[l][c]->setShip(this);
  
  textureContext = _textureContext;
  lT = _lT;
  cT = _cT;
}

StandardShip::~StandardShip() {
  gameMap = NULL;
  delete shape;
  shape = NULL;
}

void StandardShip::displayPath(SDL_Renderer* renderer,
                               const std::deque<int> &drawPath) {
  int ln = l, cn = c;
    for(int i = 0; i < drawPath.size(); ++i) {
    Point a, b;
    
    a = gameMap->cellMap[ln][cn]->getShape()->getCentroid();
    ln = ln + dlShip[drawPath[i]];
    cn = cn + dcShip[drawPath[i]];
    b = gameMap->cellMap[ln][cn]->getShape()->getCentroid();
    
    SDL_RenderDrawLine(renderer, (int)floor(a.x), (int)floor(a.y),
                                 (int)floor(b.x), (int)floor(b.y));
  }
}

void StandardShip::display(SDL_Renderer* renderer) {
  textureContext->itemSkins->renderTexture(renderer, lT, cT, 
                           {16 + c * 32, 136 + 32 * l, 32, 32});
  
  SDL_SetRenderDrawColor(renderer, 0x00, 0xe6, 0xff, 0xff);
  displayPath(renderer, path);
  
  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
  displayPath(renderer, intendedPath);
}

void StandardShip::loadResource(Resource res, int ammount) {
  cargo[res] += ammount;
  totalAmmount += ammount;
  
  if(totalAmmount > totalCapacity) {
    cargo[res] -= totalAmmount - totalCapacity;
    totalAmmount = totalCapacity;
  }
  
  if(cargo[res] > request[res]) {
    totalAmmount -= cargo[res] - request[res];
    cargo[res] = request[res];
  }
}

void StandardShip::unloadResource(Resource res, int ammount) {
  cargo[res] -= ammount;
  totalAmmount -= ammount;
}

void StandardShip::mouseButtonPress(int key) {
  if(key == SDL_BUTTON_LEFT && modifying) {
    modifying = false;
    path = intendedPath;
    intendedPath.clear();
    freezeShip();
  } else if(key == SDL_BUTTON_RIGHT && !modifying &&
            gameMap->cellMap[l][c]->isHovering()) {
    modifying = true;
    freezeShip();
  } else if(key == SDL_BUTTON_RIGHT && modifying) {
    intendedPath.clear();
    modifying = false;
    freezeShip();
  }
}

void StandardShip::mouseButtonRelease(int key) {}

void StandardShip::mouseMotion(float _x, float _y) {
  if(modifying) {
    int i = 0;
    int ln = l, cn = c;
    
    if(gameMap->cellMap[l][c]->isHovering())
      intendedPath.clear();
    
    while(i < intendedPath.size()) {
      ln = ln + dlShip[intendedPath[i]];
      cn = cn + dcShip[intendedPath[i]];
      
      if(gameMap->cellMap[ln][cn]->isHovering())
        while(intendedPath.size() > i + 1)
          intendedPath.pop_back();
      ++i;
    }
    
    if(i == intendedPath.size()) {
      int act = 1;
      bool ok = false;
      int lnn = ln, cnn = cn;
      
      do {
        lnn = ln + dlShip[act];
        cnn = cn + dcShip[act];
        
        if(0 <= lnn && lnn < MAX_MAP_CELL_HEIGHT &&
           0 <= cnn && cnn < MAX_MAP_CELL_WIDTH  &&
           gameMap->cellMap[lnn][cnn]->isHovering())
          ok = true;
        else
          ++act;
      } while(act <= 4 && !ok);
      
      if(act <= 4)
        intendedPath.push_back(act);
    }
  }
}

void StandardShip::islandAction() {
  while(elapsedTime >= unloadSpeed) {
    Island* currentIsland = gameMap->cellMap[l][c]->getIsland();
    if(currentIsland != NULL) {
      if(currentIsland->getType() == GASSTATION) {
        fuel = fuel + currentIsland->requestFuel(maxFuel - fuel);
        elapsedTime -= unloadSpeed;
      } else if(currentIsland->getType() == SUPPLIER) {
        int req = 0;
        while(req < MAX_RESOURCES && (cargo[req] >= request[req] || 
              !currentIsland->resourceAvailable((Resource)req)))
          ++req;
        
        if(req < MAX_RESOURCES && totalAmmount < totalCapacity) {
          loadResource(Resource(req), 1);
          currentIsland->requestResource(Resource(req));
        }
        elapsedTime -= unloadSpeed;
      } else if(currentIsland->getType() == REQUESTER) {
        int req = 0;
        while(req < MAX_RESOURCES && (cargo[req] == 0 || 
                         currentIsland->getRequest(Resource(req)) == 0))
          ++req;
        
        if(req < MAX_RESOURCES) {
          unloadResource(Resource(req), 1);
          currentIsland->resolveRequest(Resource(req));
        }
        elapsedTime -= unloadSpeed;
      } else
        elapsedTime = 0.0f;
    } else
      elapsedTime = 0.0f;
  }
}

void StandardShip::moveShip() {
  while(!path.empty() && elapsedTime >= speed && fuel >= 0) {
    int ln = l + dlShip[path.front()];
    int cn = c + dcShip[path.front()];
    
    shape->translate(32.0f * dcShip[path.front()],
                     32.0f * dlShip[path.front()]);
    
    fuel--;
    if(fuel < 0) {
      destroyShip();
      gameMap->cellMap[l][c]->markShipwreck();
    } else {
      gameMap->moveShip(l, c, ln, cn);
      l = ln;
      c = cn;
      
      path.pop_front();
      elapsedTime -= speed;
      doInventoryRestrictions();
    }
  }
  if(path.empty())
    elapsedTime = 0.0f;
}

void StandardShip::doInventoryRestrictions() {
  if(cargo[URANIUM] > 5)
    destroyShip();
  else if(cargo[PETROL] > 0 && cargo[FLAME_ROCK] > 0)
    destroyShip();
  else if(cargo[FLAME_ROCK] > 0 && cargo[ICE_ROCK] > 0) {
    --cargo[FLAME_ROCK];
    --cargo[ICE_ROCK];
    totalAmmount -= 2;
  }
}

void StandardShip::update() {
  if(path.empty()) {
    islandAction();
  } else {
    moveShip();
  }
}

void StandardShip::destroyShip() {
  wallet->loseMoney(10000);
  destroyed = true;
}

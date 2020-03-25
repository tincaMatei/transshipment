#include "game/map.h"

Map::Map(Wallet* _wallet, TextureContext* textureContext) {
  wallet = _wallet;
  
  int dl[] = {0, 1, 0, -1};
  int dc[] = {1, 0,-1,  0};
  
  std::vector<std::vector<char> > gameMap = generateMap(9);
  
  islands.push_back(new Island(PORT, wallet));
  for(int i = 0; i < 2; ++i)
    islands.push_back(new Island(GASSTATION, wallet));
  for(int i = 0; i < 4; ++i)
    islands.push_back(new Island(REQUESTER, wallet));
  for(int i = 0; i < 3; ++i)
    islands.push_back(new Island(SUPPLIER, wallet));
  
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      cellMap[l][c] = new Cell(l, c, textureContext);
      if(gameMap[l][c] == 0) {
        cellMap[l][c]->type = WATER;
      } else {
        cellMap[l][c]->type = ISLAND;
        cellMap[l][c]->setIsland(islands[gameMap[l][c] - 1]);
      }
    }
  
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      if(cellMap[l][c]->type == WATER) {
        for(int i = 0; i < 4; ++i) {
          int ln = l + dl[i];
          int cn = c + dc[i];
          
          if(0 <= ln && ln < MAX_MAP_CELL_HEIGHT &&
             0 <= cn && cn < MAX_MAP_CELL_WIDTH &&
             gameMap[ln][cn] >= 1) {
            cellMap[l][c]->setIsland(islands[gameMap[ln][cn] - 1]);
          }
        }
      }
    }
}

Map::~Map() {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      delete cellMap[l][c];
      cellMap[l][c] = NULL;
    }
  
  for(int i = 0; i < islands.size(); ++i) {
    delete islands[i];
    islands[i] = NULL;
  }
}

void Map::display(SDL_Renderer* renderer) {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      cellMap[l][c]->display(renderer);
}

void Map::mouseMotion(float xMouse, float yMouse) {
  mousePointer = {xMouse, yMouse};
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      cellMap[l][c]->mouseMotion(xMouse, yMouse);
}

void Map::mouseButtonPress(int key) {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      cellMap[l][c]->mouseButtonPress(key);
}

void Map::mouseButtonRelease(int key) {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      cellMap[l][c]->mouseButtonRelease(key);
}

void Map::moveShip(int l, int c, int ln, int cn) {
  Ship* moved = cellMap[l][c]->getShip();
  cellMap[l][c]->setShip(NULL);
  cellMap[ln][cn]->setShip(moved);
  moved = NULL;
}

std::vector<Island*> Map::getIslands() {
  return islands;
}

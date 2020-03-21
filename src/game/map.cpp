#include "game/map.h"

Map::Map() {
  std::vector<std::vector<char> > gameMap = generateMap(9);
  
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      cellMap[l][c] = new Cell(l, c);
      if(gameMap[l][c] == 1)
        cellMap[l][c]->type = PORT;
      else if(gameMap[l][c] == 0)
        cellMap[l][c]->type = WATER;
      else
        cellMap[l][c]->type = ISLAND;
    }
}

Map::~Map() {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      delete cellMap[l][c];
      cellMap[l][c] = NULL;
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
}

void Map::mouseButtonRelease(int key) {
}

void Map::moveShip(int l, int c, int ln, int cn) {
  Ship* moved = cellMap[l][c]->getShip();
  cellMap[l][c]->setShip(NULL);
  cellMap[ln][cn]->setShip(moved);
  moved = NULL;
}

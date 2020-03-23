#ifndef __MAP_H
#define __MAP_H

#include "object.h"
#include "game/cell.h"
#include "game/mapgen.h"
#include "game/island.h"
#include "game/wallet.h"
#include <vector>
#include "graphicshandler.h"

class Map : public DisplayableObject,
            public MouseObject {
private:
  std::vector<Island*> islands;

  Wallet* wallet;
public:
  // Entire map
  Cell* cellMap[MAX_MAP_CELL_HEIGHT][MAX_MAP_CELL_WIDTH];

  Map(Wallet* _wallet, TextureContext* textureContext);
  
  ~Map();
  
  void display(SDL_Renderer* renderer);
  
  void mouseMotion(float xMouse, float yMouse);
  
  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);

  // Move the ship from (l, c) to (ln, cn)
  void moveShip(int l, int c, int ln, int cn);
  
  std::vector<Island*> getIslands();
};

#endif

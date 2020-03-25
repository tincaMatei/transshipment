#include "game/aesthetics.h"
#include <random>
#include <SDL2/SDL.h>

namespace Aesthetics {

char simpleMap[MAX_MAP_CELL_HEIGHT][MAX_MAP_CELL_WIDTH];

//          D  R   U  L
int dl[] = {1, 0, -1, 0};
int dc[] = {0, 1,  0,-1};

int tileNormal[16][2] = {
{0, 0}, // 0000 -> (null)
{0, 2}, // 0001 ->     D
{1, 1}, // 0010 ->    R
{3, 0}, // 0011 ->    RD
{2, 2}, // 0100 ->   U
{1, 2}, // 0101 ->   U D
{4, 0}, // 0110 ->   UR
{1, 2}, // 0111 ->   URD
{1, 3}, // 1000 ->  L
{3, 1}, // 1001 ->  L  D
{1, 2}, // 1010 ->  L R
{1, 2}, // 1011 ->  L RD
{4, 1}, // 1100 ->  LU
{1, 2}, // 1101 ->  LU D
{1, 2}, // 1110 ->  LUR
{1, 2}, // 1111 ->  LURD
};

//             RD LD UR UL
int diagl[] = { 1, 1,-1,-1};
int diagc[] = { 1,-1, 1,-1};

int tileDiagonal[16][2] = {
{3, 0}, // 0000 -> () () () ()
{0, 1}, // 0001 -> () () () (RD)
{0, 3}, // 0010 -> () () (LD) ()
{0, 2}, // 0011 -> () () (LD) (RD)
{2, 1}, // 0100 -> () (UR) () ()
{1, 1}, // 0101 -> () (UR) () (RD)
{3, 0}, // 0110 -> () (UR) (LD) ()
{3, 0}, // 0111 -> () (UR) (LD) (RD)
{2, 3}, // 1000 -> (UL) () () ()
{3, 0}, // 1001 -> (UL) () () (RD)
{1, 3}, // 1010 -> (UL) () (LD) ()
{3, 1}, // 1011 -> (UL) () (LD) (RD)
{2, 2}, // 1100 -> (UL) (UR) () ()
{4, 0}, // 1101 -> (UL) (UR) () (RD)
{4, 1}, // 1110 -> (UL) (UR) (LD) ()
{3, 0} // 1111 -> (UL) (UR) (LD) (RD)
};

int getIslandNeighbours(Map* gameMap, int l, int c) {
  int mask = 0;
  for(int i = 0; i < 4; ++i) {
    int ln = l + dl[i];
    int cn = c + dc[i];
    
    if(0 <= ln && ln < MAX_MAP_CELL_HEIGHT &&
       0 <= cn && cn < MAX_MAP_CELL_WIDTH && 
       simpleMap[ln][cn] == 1) {
      mask |= (1 << i);
    }
  }
  return mask;
}

int getDiagonalNeighbours(Map* gameMap, int l, int c) {
  int mask = 0;
  for(int i = 0; i < 4; ++i) {
    int ln = l + diagl[i];
    int cn = c + diagc[i];
    
    if(0 <= ln && ln < MAX_MAP_CELL_HEIGHT &&
       0 <= cn && cn < MAX_MAP_CELL_WIDTH && 
       simpleMap[ln][cn] == 1) {
      mask |= (1 << i);
    }
  }
  return mask;
}

int cntBits(int mask) {
  return ((mask & (1 << 0)) > 0) + ((mask & (1 << 1)) > 0) + 
         ((mask & (1 << 2)) > 0) + ((mask & (1 << 3)) > 0);
}

void simplifyMap(Map* gameMap) {
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      if(gameMap->cellMap[l][c]->type == ISLAND)
        simpleMap[l][c] = 1;
      else
        simpleMap[l][c] = 0;

  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c)
      if(cntBits(getIslandNeighbours(gameMap, l, c)) >= 3) {
        simpleMap[l][c] = 1;
      }
}

void aestheticize(Map* gameMap) {
  std::mt19937 mt_rand(SDL_GetTicks());
  
  simplifyMap(gameMap); 
  
  for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
    for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
      if(gameMap->cellMap[l][c]->type == WATER) {
        int m1, m2;
        
        m1 = getIslandNeighbours(gameMap, l, c);
        m2 = getDiagonalNeighbours(gameMap, l, c);
        
        if(m1 == 0 && m2 == 0) {
          int rng = mt_rand() % 100;
          
          if(rng < 80)
            gameMap->cellMap[l][c]->assignTile(2, 0);
          else if(rng < 90)
            gameMap->cellMap[l][c]->assignTile(0, 0);
          else
            gameMap->cellMap[l][c]->assignTile(1, 0);
        } else if(m1 != 0)
          gameMap->cellMap[l][c]->assignTile(tileNormal[m1][0], tileNormal[m1][1]);
        else
          gameMap->cellMap[l][c]->assignTile(tileDiagonal[m2][0], tileDiagonal[m2][1]);
      } else if(gameMap->cellMap[l][c]->getIsland()->getType() == GASSTATION) {
        int rng = mt_rand() % 100;
        
        if(rng < 80)
          gameMap->cellMap[l][c]->assignTile(5, 0);
        else if(rng < 90)
          gameMap->cellMap[l][c]->assignTile(6, 0);
        else
          gameMap->cellMap[l][c]->assignTile(7, 0);
      } else if(gameMap->cellMap[l][c]->getIsland()->getType() == PORT)
        gameMap->cellMap[l][c]->assignTile(3, 2);
      else if(gameMap->cellMap[l][c]->getIsland()->getType() == SUPPLIER) {
        int rng = mt_rand() % 100;
        
        if(rng < 80)
          gameMap->cellMap[l][c]->assignTile(5, 2);
        else if(rng < 90)
          gameMap->cellMap[l][c]->assignTile(6, 2);
        else
          gameMap->cellMap[l][c]->assignTile(7, 2);
      } else if(gameMap->cellMap[l][c]->getIsland()->getType() == REQUESTER) {
        int rng = mt_rand() % 100;
        
        if(rng < 80)
          gameMap->cellMap[l][c]->assignTile(5, 1);
        else if(rng < 90)
          gameMap->cellMap[l][c]->assignTile(6, 1);
        else
          gameMap->cellMap[l][c]->assignTile(7, 1);
      }
    }
}

}

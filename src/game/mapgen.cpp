#include "game/mapgen.h"
#include <random>
#include <ctime>

int splitWidth[5]  = {4, 5, 4, 4, 5};
int splitHeight[3] = {5, 5, 4};

int dl[] = {0, 1, 0, -1};
int dc[] = {1, 0,-1,  0};

bool taken[15];

void initMapGen() {
  for(int i = 0; i < 15; ++i)
    taken[i] = false;
}

std::vector<std::vector<char> > generateMap(int islands) {
  initMapGen();
  std::mt19937 mt_rand(time(NULL));
  
  std::vector<std::vector<char> > gameMap(MAX_MAP_CELL_HEIGHT,
                                          std::vector<char>(MAX_MAP_CELL_WIDTH, 0));
  
  for(int i = 0; i < MAX_MAP_CELL_HEIGHT; ++i)
    gameMap[i][0] = gameMap[i][1] = 1; // Port
  
  for(int i = 0; i < islands; ++i) {
    int lIsland, cIsland;
    int lCellIsland, cCellIsland;
    int lRestr1, cRestr1;
    
    lIsland = 0;
    cIsland = 2;
    
    int mapId = mt_rand() % 15;
    while(taken[mapId])
      mapId = mt_rand() % 15;
    
    taken[mapId] = true;
    
    lCellIsland = mapId / 5;
    cCellIsland = mapId % 5;
    
    for(int i = 0; i < lCellIsland; ++i)
      lIsland += splitHeight[i];
    for(int i = 0; i < cCellIsland; ++i)
      cIsland += splitWidth[i];
    
    lRestr1 = lIsland + 1;
    cRestr1 = cIsland + 1;
    
    int sizeIsland = mt_rand() % ((splitHeight[lCellIsland] - 2) *
                                  (splitWidth[cCellIsland]  - 2))+ 1;
    
    int generated = 0;
    do {
      int l = lRestr1 + mt_rand() % (splitHeight[lCellIsland] - 2);
      int c = cRestr1 + mt_rand() % (splitWidth[cCellIsland]  - 2);
      
      if(generated == 0) {
        ++generated;
        gameMap[l][c] = i + 2;
      } else {
        bool ok = false;
        for(int i = 0; i < 4; ++i)
          if(gameMap[l + dl[i]][c + dc[i]] != 0)
            ok = true;
        if(ok) {
          gameMap[l][c] = i + 2;
          ++generated;
        }
      }
      
    } while(generated < sizeIsland);
  }
  
  return gameMap;
}

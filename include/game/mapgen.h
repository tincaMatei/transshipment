#ifndef __MAPGEN_H
#define __MAPGEN_H

#include <vector>

const int MAX_MAP_CELL_WIDTH  = 24;
const int MAX_MAP_CELL_HEIGHT = 14;

// Generate a map with size MAX_MAP_CELL_WIDTH x MAX_MAP_CELL_HEIGHT
std::vector<std::vector<char> > generateMap(int islands);

#endif

#ifndef __DEBUGTOOLS_H
#define __DEBUGTOOLS_H

#include <SDL2/SDL.h>
#include "geometry.h"

// Draw the contour of the polygon with the last renderer color
void debugPolygon(SDL_Renderer* renderer, Polygon* poly);

#endif

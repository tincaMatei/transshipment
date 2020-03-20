#include "debugtools.h"

void debugPolygon(SDL_Renderer* renderer, Polygon* poly) {
  for(unsigned int i = 0; i < poly->polygon.size(); ++i) {
    int i2 = (i + 1) % poly->polygon.size();
    SDL_RenderDrawLine(renderer, (int)poly->polygon[i].x,  
                                 (int)poly->polygon[i].y, 
                                 (int)poly->polygon[i2].x, 
                                 (int)poly->polygon[i2].y);
  }
  
  if(poly->polygon.size() == 1)
    SDL_RenderDrawPoint(renderer, (int)poly->polygon[0].x, 
                                  (int)poly->polygon[0].y);
}

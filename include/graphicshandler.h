#ifndef __GRAPHICSHANDLER_H
#define __GRAPHICSHANDLER_H

#include <SDL2/SDL.h>

// Small interface that draws colors
class RectangleDrawer {
private:
  SDL_Renderer* renderer;

public:
  RectangleDrawer(SDL_Renderer* _renderer);
  
  // Draw a rectangle at position (x, y) with width w and height h
  // with the last render color used
  void renderRectangle(int x, int y, int w, int h);
  
  // Draw a rectangle at position (x, y) with width w and height h
  // with given color
  void renderRectangle(int x, int y, int w, int h, 
                       unsigned char r, 
                       unsigned char g,
                       unsigned char b);
};

#endif

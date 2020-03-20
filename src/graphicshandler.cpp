#include "graphicshandler.h"

RectangleDrawer::RectangleDrawer(SDL_Renderer* _renderer) {
  renderer = _renderer;
}

void RectangleDrawer::renderRectangle(int x, int y, int w, int h) {
  SDL_Rect rectangle = {x, y, w, h};
  SDL_RenderFillRect(renderer, &rectangle);
}

void RectangleDrawer::renderRectangle(int x, int y, int w, int h,
                                      unsigned char r, 
                                      unsigned char g, 
                                      unsigned char b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 0xff);
  SDL_Rect rectangle = {x, y, w, h};
  SDL_RenderFillRect(renderer, &rectangle);
}


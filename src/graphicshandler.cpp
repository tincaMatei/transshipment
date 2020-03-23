#include "graphicshandler.h"
#include <algorithm>

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

FontRenderer::FontRenderer(const char* filename, int fontsize) {
  usedFont = TTF_OpenFont(filename, fontsize);
  if(usedFont == NULL)
    SDL_Log("Failed to open font: %s\n", TTF_GetError());
}

FontRenderer::~FontRenderer() {
  if(usedFont != NULL) {
    TTF_CloseFont(usedFont);
    usedFont = NULL;
  }
}

std::string FontRenderer::inttostring(int x) {
  bool negative = (x < 0);
  std::string rez;
  
  if(x < 0)
    x = -x;
  
  if(x == 0)
    rez.push_back('0');
  
  while(x > 0) {
    rez.push_back(x % 10 + '0');
    x /= 10;
  }
  
  if(negative)
    rez.push_back('-');
  reverse(rez.begin(), rez.end());
  return rez;
}

void FontRenderer::renderText(SDL_Renderer* renderer, float _x, float _y,
                             std::string text) {
  SDL_Color color;
  SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
  
  SDL_Surface* surface = TTF_RenderText_Solid(usedFont, text.c_str(), color);
  if(surface == NULL)
    SDL_Log("Unable to create font surface: %s\n", TTF_GetError());
  else {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
      SDL_Log("Unable to create texture from surface: %s\n", SDL_GetError());
    else {
      int width = surface->w, height = surface->h;
      SDL_Rect rect = {(int)floor(_x - width / 2.0f),
                       (int)floor(_y - height / 2.0f),
                       width, height};
      SDL_RenderCopy(renderer, texture, NULL, &rect);
      
      SDL_DestroyTexture(texture);
      texture = NULL;
    }
    
    SDL_FreeSurface(surface);
    surface = NULL;
  }
}

TileSetRenderer::TileSetRenderer(const char* filename, 
                                 SDL_Renderer* renderer,
                                 int _tw, int _th) {
  SDL_Surface* surface = IMG_Load(filename);
  texture = NULL;
  
  tileWidth = _tw;
  tileHeight = _th;
  
  if(surface == NULL) {
    SDL_Log("Unable to load image %s: %s\n", filename, SDL_GetError());
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
      SDL_Log("Unable to create texture %s: %s\n", filename, SDL_GetError());
    SDL_FreeSurface(surface);
    surface = NULL;
  }
}

TileSetRenderer::~TileSetRenderer() {
  if(texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}

void TileSetRenderer::renderTexture(SDL_Renderer* renderer, int l, int c, 
                                    SDL_Rect target) {
  if(texture != NULL) {
    SDL_Rect from = {c * tileWidth, l * tileHeight, tileWidth, tileHeight};
    SDL_RenderCopy(renderer, texture, &from, &target);
  }
}

TextureContext::TextureContext(SDL_Renderer* renderer) {
  mapTiles = new TileSetRenderer("media/tiles.png", renderer, 16, 16);
  itemSkins = new TileSetRenderer("media/items.png", renderer, 16, 16);
  plusButton = new TileSetRenderer("media/plusbutton.png", renderer, 16, 16);
  minusButton = new TileSetRenderer("media/minusbutton.png", renderer, 16, 16);
  crossButton = new TileSetRenderer("media/crossbutton.png", renderer, 16, 16);
  guiWindow = new TileSetRenderer("media/gui.png", renderer, 100, 40);
  playmenu = new TileSetRenderer("media/playmenu.png", renderer, 100, 40);
  quitmenu = new TileSetRenderer("media/quitmenu.png", renderer, 100, 40);
  cancelmenu = new TileSetRenderer("media/cancelmenu.png", renderer, 100, 40);
  wholemenu = new TileSetRenderer("media/menu.png", renderer, 800, 600);
}

TextureContext::~TextureContext() {
  delete mapTiles;
  delete itemSkins;
  delete plusButton;
  delete minusButton;
  delete crossButton;
  delete guiWindow;
  delete playmenu;
  delete quitmenu;
  delete cancelmenu;
  delete wholemenu;
  mapTiles = NULL;
  itemSkins = NULL;
  plusButton = NULL;
  minusButton = NULL;
  crossButton = NULL;
  guiWindow = NULL;
  playmenu = NULL;
  quitmenu = NULL;
  cancelmenu = NULL;
  wholemenu = NULL;
}

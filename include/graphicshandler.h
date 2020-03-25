#ifndef __GRAPHICSHANDLER_H
#define __GRAPHICSHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

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

class FontRenderer {
private:
  TTF_Font* usedFont;
public:
  FontRenderer(const char* filename, int fontsize);
  ~FontRenderer();
  
  static std::string inttostring(int x);
  
  void renderText(SDL_Renderer* renderer, float _x, float _y, 
                  std::string text);
};

class TileSetRenderer {
private:
  SDL_Texture* texture;
  
  int tileWidth, tileHeight;
public:
  TileSetRenderer(const char* filename, SDL_Renderer* renderer,
                  int _tw, int _th);
  ~TileSetRenderer();
  
  void renderTexture(SDL_Renderer* renderer, int l, int c, SDL_Rect target);
};

struct TextureContext {
  TileSetRenderer* mapTiles;
  TileSetRenderer* itemSkins;
  TileSetRenderer* plusButton;
  TileSetRenderer* minusButton;
  TileSetRenderer* crossButton;
  TileSetRenderer* guiWindow;
  TileSetRenderer* playmenu;
  TileSetRenderer* quitmenu;
  TileSetRenderer* cancelmenu;
  TileSetRenderer* wholemenu;
  TileSetRenderer* settingsmenugui;
  TileSetRenderer* endgamegui;
  TileSetRenderer* volumedot;
  TileSetRenderer* helpmenu;
  TileSetRenderer* instructionsmenu;
  
  TextureContext(SDL_Renderer* renderer);
  ~TextureContext();
};

#endif

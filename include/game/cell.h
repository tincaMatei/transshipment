#ifndef __CELL_H
#define __CELL_H

#include "geometry.h"
#include "object.h"
#include "game/ship.h"
#include "game/island.h"
#include "game/button.h"
#include "graphicshandler.h"

// Types of the cells
enum CellType {
  WATER,
  ISLAND
};

class Cell : public Button {
private:
  // Coordinates on the map
  int l, c;
  // Ship currently on that cell
  Ship* ship;
  // True if the cell contains a shipwreck
  bool shipwreck;
  // Island on that cell
  Island* island;
  
  TextureContext* textureContext;
  
  int lT, cT;
  
  float x1, x2, y1, y2;
public:
  // Type of the cell
  CellType type;
  
  // Initialize the cell on the _l'th line and _c'th column
  Cell(int _l, int _c, TextureContext* _textureContext);
  ~Cell();
  
  // Return true if the cursor is hovering over the cell
  bool isHovering();
  // Get the shape of the cell
  Polygon* getShape();
  // Set the ship on the current cell
  void setShip(Ship* _ship);
  // Return the ship on the current cell
  Ship* getShip();
  
  void markShipwreck();
  // Return true if the cell contains a shipwreck
  bool getShipwreck();  
  
  void display(SDL_Renderer* renderer);
  
  void setIsland(Island* _island);
  
  bool resourceAvailable(Resource res);
  
  Island* getIsland();
  
  void assignTile(int _lt, int _ct);
};

#endif

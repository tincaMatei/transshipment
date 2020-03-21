#ifndef __CELL_H
#define __CELL_H

#include "geometry.h"
#include "object.h"
#include "game/ship.h"

// Types of the cells
enum CellType {
  WATER,
  PORT,
  ISLAND
};

class Cell : public DisplayableObject,
             public MouseObject {
private:
  // Coordinates on the map
  int l, c;
  // Body of the cell
  Polygon* body;
  // Mouse properties
  bool hovering;
  // Ship currently on that cell
  Ship* ship;
  // True if the cell contains a shipwreck
  bool shipwreck;
  
public:
  // Type of the cell
  CellType type;
  
  // Initialize the cell on the _l'th line and _c'th column
  Cell(int _l, int _c);
  
  ~Cell();
  
  // Return true if the cursor is hovering over the cell
  bool isHovering();
  // Get the shape of the cell
  Polygon* getShape();
  // Set the ship on the current cell
  void setShip(Ship* _ship);
  // Return the ship on the current cell
  Ship* getShip();
  // Return true if the cell contains a shipwreck
  bool getShipwreck();  
  
  void display(SDL_Renderer* renderer);

  void mouseButtonPress(int key);
  
  void mouseButtonRelease(int key);
  
  void mouseMotion(float _x, float _y);
};

#endif

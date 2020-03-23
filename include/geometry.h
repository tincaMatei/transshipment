#ifndef __GEOMETRY_H
#define __GEOMETRY_H

/* TODO:
 * implement rotation
 * implement a bad collision function for the moment
 * implement a good collision function
 */
#include <cmath>
#include <vector>

const float PI = acos(-1);

// Point in plane
struct Point {
	float x, y;
	
  // Creates a point at coordinate (0, 0)
  Point();
  
	// Creates a point at coordinates (_x, _y)
	Point(float _x, float _y);
};

// Struct that holds a polygon
struct Polygon {
  // This holds the vertices of the polygon in trigonometric order
  // (counter clockwise)
  std::vector<Point> polygon;
  
  // Construct the polygon from the given vector
  Polygon(const std::vector<Point> &_polygon);
  
  // Create a polygon with only one vertex
  Polygon(float x, float y);
  
  // Create a rectangle at position (x, y) with width w
  // and height h with sides parallel to the x-axis and y-axis
  // The rectangle with have it's center of mass in (x, y)
  Polygon(float x, float y, float w, float h);
  
  // Create a regulated polygon with center in (x, y)
  // and radius r and n vertices
  Polygon(float x, float y, float r, int n);
  
  ~Polygon();
  
  // Translates the polygon with the vector (x, y)
  void translate(float x, float y);

  // Rotates the polygon with the given angle
  // The center off mass will be point (x, y)
  // The rotation will be in counter-clockwise direction
  void rotate(float angle, float x, float y);
    
  // Rotates the polygon with the given angle
  // The center of rotation will be the center of mass
  // The rotation will be in counter-clockwise direction
  void rotate(float angle);

  // Checks collision between two polygons
  // Note: at the moment, this just returns true if the
  //       bounding boxes of the two polygons intersect
  bool collides(Polygon* otherPolygon);
  
  Point getCentroid();
};

float pointDistance(Point a, Point b);

#endif


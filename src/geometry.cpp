#include "geometry.h"
#include <algorithm>

Point::Point() {
  x = y = 0.0f;
}

Point::Point(float _x, float _y) {
  x = _x;
  y = _y;
}

Polygon::Polygon(const std::vector<Point> &_polygon) {
  polygon = _polygon;
}

Polygon::Polygon(float x, float y) {
  polygon.push_back({x, y});
}

Polygon::Polygon(float x, float y, float w, float h) {
  polygon.push_back({x - w / 2, y - h / 2});
  polygon.push_back({x - w / 2, y + h / 2});
  polygon.push_back({x + w / 2, y + h / 2});
  polygon.push_back({x + w / 2, y - h / 2});
}

Polygon::Polygon(float x, float y, float r, int n) {
  // angleGrowth is negative because the screen is flipped
  float angle = 0.0f, angleGrowth = -2.0f * PI / n;
  for(int i = 0; i < n; ++i) {
    polygon.push_back({(float)(x + r * cos(angle)), 
                       (float)(y + r * sin(angle))});
    angle = angle + angleGrowth;
  }
}

void Polygon::translate(float x, float y) {
  for(unsigned int i = 0; i < polygon.size(); ++i)
    polygon[i] = Point(polygon[i].x + x, polygon[i].y + y);
}

void Polygon::rotate(float angle, float x, float y) {
  for(unsigned int i = 0; i < polygon.size(); ++i) {
    
  }
}

void Polygon::rotate(float angle) {
  Point massCenter;
  for(unsigned int i = 0; i < polygon.size(); ++i)
    massCenter = Point(massCenter.x + polygon[i].x / polygon.size(),
                       massCenter.y + polygon[i].y / polygon.size());
  rotate(angle, massCenter.x, massCenter.y);
}

bool Polygon::collides(Polygon* otherPoly) {
  float x1, y1, x2, y2;
  float ox1, oy1, ox2, oy2;
  
  x1 = y1 = ox1 = oy1 =  1e9;
  x2 = y2 = ox2 = oy2 = -1e9;
  
  for(unsigned int i = 0; i < polygon.size(); ++i) {
    x1 = std::min(x1, polygon[i].x);
    x2 = std::max(x2, polygon[i].x);
    y1 = std::min(y1, polygon[i].y);
    y2 = std::max(y2, polygon[i].y);
  }
  
  for(unsigned int i = 0; i < otherPoly->polygon.size(); ++i) {
    ox1 = std::min(ox1, otherPoly->polygon[i].x);
    ox2 = std::max(ox2, otherPoly->polygon[i].x);
    oy1 = std::min(oy1, otherPoly->polygon[i].y);
    oy2 = std::max(oy2, otherPoly->polygon[i].y);
  }
  
  return std::max(x1, ox1) <= std::min(x2, ox2) &&
         std::max(y1, oy1) <= std::min(y2, oy2);
}

Point Polygon::getCentroid() {
  Point rez(0.0f, 0.0f);
  
  for(int i = 0; i < polygon.size(); ++i) {
    rez.x = rez.x + polygon[i].x / polygon.size();
    rez.y = rez.y + polygon[i].y / polygon.size();
  }
  return rez;
}

float pointDistance(Point a, Point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

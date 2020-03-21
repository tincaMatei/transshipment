#ifndef __OBJECT_H
#define __OBJECT_H

#include <SDL2/SDL.h>
#include "geometry.h"

// TODO: * Implement everything
//       * Decide on the mouse implementation
//       * Make the Audio component of an Object
//       * destructors

// The base of the objects
class Object {
private:
  // This should be false if the object should be removed
  bool active;
public:
  // Object constructor
  Object();
  ~Object();
  
  // Marks the object as inactive
  void selfDestruct();
  
  // Returns 'active'
  bool isActive();
};

// Object's display property
class DisplayableObject : public Object {
  float depth;
public:
  DisplayableObject();
  ~DisplayableObject();
  
  // Set the depth of an object
  // If the depth is higher, it will be rendered later
  // therefore it will be rendered above another overlapping object
  void setDepth(float _depth);

  virtual void display(SDL_Renderer* renderer) = 0;
};

// Object's mouse interface
class MouseObject : public Object {
public:
  ~MouseObject();

  Point mousePointer;
  void setCursorPosition(float x, float y);
  
  // Update the last known pointer position
  virtual void mouseMotion(float x, float y) = 0;

  // Button press/release
  virtual void mouseButtonPress(int key) = 0;
  virtual void mouseButtonRelease(int key) = 0;
  
  // Stuff to do when mouse scrolls up
  // void scrollUp();
  
  // Stuff to do when mouse scrolls down
  // void scrollDown();
};

// Object's keyboard interface
class KeyboardObject : public Object {
public:
  ~KeyboardObject();
  
  // Stuff to do when the given key is pressed
  // If repeat is true, that means that we were holding the key down
  // and the press was counted twice
  // See SDL documentation for key codes
  virtual void keyPress(int key, bool repeat = false) = 0;
  
  // Actions to do for the current keyboard state
  // See SDL documentation for key codes
  virtual void keyHold(const Uint8* state) = 0;
  
  // Same when it's released
  // See SDL documentation for key codes
  virtual void keyRelease(int key) = 0;
};

// Object's idling process
class IdleObject: public Object {
public:
  ~IdleObject();
  
  // This will be called at the end of every game loop
  virtual void update() = 0;
};

#endif

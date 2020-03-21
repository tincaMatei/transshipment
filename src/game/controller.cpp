#include "game/controller.h"

Controller::Controller() {
  gameMap = new Map();
  testShip = new StandardShip(1000.0f, 0, 2, gameMap);
  testShip2 = new StandardShip(1000.0f, 1, 2, gameMap);
  
  stopWatch.startTimer();
}

Controller::~Controller() {
  delete gameMap;
  delete testShip;
  delete testShip2;
}

void Controller::display(SDL_Renderer* renderer) {
  gameMap->display(renderer);
  if(!testShip->isDestroyed())
    testShip->display(renderer);
  if(!testShip2->isDestroyed())
  testShip2->display(renderer);
}

void Controller::mouseButtonPress(int key) {
  if(!testShip->isDestroyed())
    testShip->mouseButtonPress(key);
  if(!testShip2->isDestroyed())
    testShip2->mouseButtonPress(key);
}

void Controller::mouseButtonRelease(int key) {
  if(!testShip->isDestroyed())
    testShip->mouseButtonRelease(key);
  if(!testShip2->isDestroyed())
    testShip2->mouseButtonRelease(key);
}

void Controller::mouseMotion(float xMouse, float yMouse) {
  gameMap->mouseMotion(xMouse, yMouse);
  if(!testShip->isDestroyed())
    testShip->mouseMotion(xMouse, yMouse);
  if(!testShip2->isDestroyed())
    testShip2->mouseMotion(xMouse, yMouse);
}

void Controller::keyPress(int key, bool repeat) {
}

void Controller::keyRelease(int key) {
}

void Controller::keyHold(const Uint8* state) {
}

void Controller::update() {
  if(!testShip->isFreezed() && !testShip2->isFreezed()) {
    if(!testShip->isDestroyed())
      testShip->addTime((float)(stopWatch.getTimeAmmount()));
    if(!testShip2->isDestroyed())
      testShip2->addTime((float)(stopWatch.getTimeAmmount()));
    
    if(!testShip->isDestroyed())
      testShip->update();
    if(!testShip2->isDestroyed())
      testShip2->update();
  }
  stopWatch.resetTimer();
}

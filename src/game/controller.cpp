#include "game/controller.h"

Controller::Controller(TextureContext* textureContext) {
  wallet = new Wallet(10000);
  gameMap = new Map(wallet, textureContext);
  shipGui = new ShipGui(wallet, textureContext);
  requester = new Requester(wallet, gameMap->getIslands());
  shop = new Shop(wallet, gameMap, shipGui->getButtons(), textureContext);
  settingsMenu = new SettingsMenu(textureContext);
  endGameMenu = new EndGameMenu(wallet, textureContext);
  
  quit = restart = globalFreeze = false;
  
  stopWatch.startTimer();
}

Controller::~Controller() {
  delete gameMap;
  delete shipGui;
  delete wallet;
  delete requester;
  delete shop;
  delete settingsMenu;
  delete endGameMenu;
  
  for(int i = 0; i < ships.size(); ++i) {
    delete ships[i];
    ships[i] = NULL;
  }
  
  shipGui = NULL;
  gameMap = NULL;
  requester = NULL;
}

void Controller::display(SDL_Renderer* renderer) {
  gameMap->display(renderer);
  
  for(int i = 0; i < ships.size(); ++i)
    if(!ships[i]->isDestroyed()) {
      ships[i]->display(renderer);
    }
      
  shipGui->display(renderer);
  settingsMenu->display(renderer);
  endGameMenu->display(renderer);
}

void Controller::mouseButtonPress(int key) {
  gameMap->mouseButtonPress(key);
  settingsMenu->mouseButtonPress(key);
  endGameMenu->mouseButtonPress(key);
  
  for(int i = 0; i < ships.size(); ++i)
    if(!ships[i]->isDestroyed())
      ships[i]->mouseButtonPress(key);
  
  shipGui->mouseButtonPress(key);
}

void Controller::mouseButtonRelease(int key) {
  gameMap->mouseButtonRelease(key);
  settingsMenu->mouseButtonRelease(key);
  endGameMenu->mouseButtonRelease(key);
  
  for(int i = 0; i < ships.size(); ++i)
    if(!ships[i]->isDestroyed())
      ships[i]->mouseButtonRelease(key);
  
  shipGui->mouseButtonRelease(key);
}

void Controller::mouseMotion(float xMouse, float yMouse) {
  gameMap->mouseMotion(xMouse, yMouse);
  settingsMenu->mouseMotion(xMouse, yMouse);
  endGameMenu->mouseMotion(xMouse, yMouse);
  
  for(int i = 0; i < ships.size(); ++i)
    if(!ships[i]->isDestroyed())
      ships[i]->mouseMotion(xMouse, yMouse);
  
  shipGui->mouseMotion(xMouse, yMouse);
}

void Controller::keyPress(int key, bool repeat) {
}

void Controller::keyRelease(int key) {
  settingsMenu->toggleActive();
}

void Controller::keyHold(const Uint8* state) {
}

void Controller::update() {
  globalFreeze = settingsMenu->isActive();
  
  if(wallet->getBalance() < 0) {
    endGameMenu->spawn();
    globalFreeze = true;
  }
  
  settingsMenu->update();
  if(settingsMenu->shouldClose())
    quit = true;
  endGameMenu->update();
  if(endGameMenu->shouldClose())
    quit = true;
  if(endGameMenu->shouldRestart())
    restart = true;
  
  bool freezeGame = globalFreeze;
  
  std::vector<StandardShip*> sanitized;
  
  for(int i = 0; i < ships.size(); ++i) {
    if(ships[i]->isDestroyed()) {
      delete ships[i];
      ships[i] = NULL;
    } else {
      sanitized.push_back(ships[i]);
      freezeGame |= ships[i]->isFreezed();
    }
  }
  
  
  ships = sanitized;
  
  if(!freezeGame) {
    requester->update();
    
    for(int l = 0; l < MAX_MAP_CELL_HEIGHT; ++l)
      for(int c = 0; c < MAX_MAP_CELL_WIDTH; ++c) {
        if(gameMap->cellMap[l][c]->isPressed()) {
          if(gameMap->cellMap[l][c]->type == ISLAND)
            shipGui->setIsland(gameMap->cellMap[l][c]->getIsland());
          shipGui->setShip(gameMap->cellMap[l][c]->getShip());
        }
        gameMap->cellMap[l][c]->resetButton();
      }

    int ammount = stopWatch.getTimeAmmount();
    requester->addTime((float)ammount);
    for(int i = 0; i < ships.size(); ++i)
      if(!ships[i]->isDestroyed()) {
        ships[i]->addTime((float)ammount);
        ships[i]->update();
      }
      
    shipGui->update();
    shop->update();
  
    std::vector<StandardShip*> newships = shop->finishContract();
    for(int i = 0; i < newships.size(); ++i)
      ships.push_back(newships[i]);
  }
  stopWatch.resetTimer();
}

bool Controller::shouldClose() {
  return quit;
}

bool Controller::shouldRestart() {
  return restart;
}

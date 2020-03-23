#include "game/shipgui.h"
#include <string>

ShipGui::ShipGui(Wallet* _wallet, TextureContext* _textureContext) {
  targetShip = NULL;
  targetIsland = NULL;
  fontRenderer = new FontRenderer("media/FFFFORWA.TTF", 12);
  
  wallet = _wallet;
  
  for(int i = 0; i < 6; ++i) {
    invButton[i][0] = new Button(98.0f + 50 + i * (64 + 24) + 18,
                                 12.0f + 24 - 10, 16.0f, 16.0f,
                                 _textureContext->minusButton);
    invButton[i][1] = new Button(98.0f + 50 + i * (64 + 24) + 64 - 18,
                                 12.0f + 24 - 10, 16.0f, 16.0f,
                                 _textureContext->plusButton);
    buyButton.push_back(new Button(98.0f + 50 + i * (64 + 24) + 32,
                                   12.0f + 24 - 10, 16.0f, 16.0f,
                                  _textureContext->plusButton));
  }
  
  exitGuiButton = new Button(800.0f - 98.0f - 15.0f, 12.0f + 15.0f, 16.0f, 16.0f,
                             _textureContext->crossButton);
  textureContext = _textureContext;
}

ShipGui::~ShipGui() {
  targetShip = NULL;
  for(int i = 0; i < 6; ++i) {
    delete invButton[i][0];
    delete invButton[i][1];
    invButton[i][0] = invButton[i][1] = NULL;
  }
  delete exitGuiButton;
}

void ShipGui::displayShip(SDL_Renderer* renderer) {
  SDL_Rect rect = {12, 12, 800 - 12 - 98, 2 * 24 + 64};
  textureContext->guiWindow->renderTexture(renderer, 0, 0, rect);
  
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    int x1 = 98 + 50 + i * (64 + 24);
    int y1 = 12 + 24;
    
    invButton[i][0]->display(renderer);
    invButton[i][1]->display(renderer);
    
    // #0077FF
    SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xff, 0xff);
    rect = {x1, y1, 64, 64};
    SDL_RenderFillRect(renderer, &rect);
    
    textureContext->itemSkins->renderTexture(renderer, i, 1, rect);
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    
    std::string a, b;
    
    a = FontRenderer::inttostring(targetShip->getCargo(i));
    b = FontRenderer::inttostring(targetShip->getRequest(i));
    
    fontRenderer->renderText(renderer, x1 + 32, y1 + 64 + 12, a + "/" + b);
  }
  
        
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  
  std::string a, b;
  a = FontRenderer::inttostring(targetShip->getCargoOccupied());
  b = FontRenderer::inttostring(targetShip->getCargoSize());
  
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f,
                                       "Cargo:");
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 2,
                                     a + "/" + b);

  a = FontRenderer::inttostring(targetShip->getFuel());
  b = FontRenderer::inttostring(targetShip->getMaxFuel());
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 3,
                                       "Fuel:");
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 4,
                                     a + "/" + b);
  
  exitGuiButton->display(renderer);
}

void ShipGui::displayIsland(SDL_Renderer* renderer) {
  SDL_Rect rect = {12, 12, 800 - 12 - 98, 2 * 24 + 64};
  textureContext->guiWindow->renderTexture(renderer, 0, 0, rect);
  
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    int x1 = 98 + 50 + i * (64 + 24);
    int y1 = 12 + 24;
    
    // #0077FF
    SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xff, 0xff);
    rect = {x1, y1, 64, 64};
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    
    if(targetIsland->getType() == SUPPLIER &&
       targetIsland->resourceAvailable(Resource(i))) {
      std::string a, b;
    
      a = FontRenderer::inttostring(getBuyPrice(Resource(i)));
      b = FontRenderer::inttostring(getSellPrice(Resource(i)));
      
      fontRenderer->renderText(renderer, x1 + 32, y1 + 64 + 12, a + "$/" + b + "$");
      
      if(targetIsland->resourceAvailable(Resource(i)))
        textureContext->itemSkins->renderTexture(renderer, i, 1, rect);
    } else if(targetIsland->getType() == REQUESTER &&
              targetIsland->getRequest(Resource(i))) {
      std::string a;
    
      a = FontRenderer::inttostring(targetIsland->getRequest(Resource(i)));
      
      fontRenderer->renderText(renderer, x1 + 32, y1 + 64 + 12, a);
      if(targetIsland->getRequest(Resource(i)))
        textureContext->itemSkins->renderTexture(renderer, i, 1, rect);
    } else if(targetIsland->getType() == PORT) {
      textureContext->itemSkins->renderTexture(renderer, i, 0, rect);
      buyButton[i]->display(renderer);
    }
  }
  
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  
  if(targetIsland->getType() != PORT)
    fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 3,
                                       "Island:");
  
  std::string typeIsland;
  if(targetIsland->getType() == SUPPLIER)
    typeIsland = "Supplier";
  else if(targetIsland->getType() == PORT)
    typeIsland = "Port shop";
  else if(targetIsland->getType() == REQUESTER) {
    float rem = targetIsland->getRemaining();
    if(rem > 0.0f) {
      std::string a = FontRenderer::inttostring((int)(rem / 1000));  
      
      fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f, a);
      
    }
    typeIsland = "Client";
  } else
    typeIsland = "Gas station";

  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 4,
                                     typeIsland);

  exitGuiButton->display(renderer);
}

void ShipGui::displayStats(SDL_Renderer* renderer) {
  SDL_Rect rect = {12, 12, 800 - 12 - 98, 2 * 24 + 64};
  textureContext->guiWindow->renderTexture(renderer, 0, 0, rect);
  
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 3,
                                   "Balance:");
  std::string a = FontRenderer::inttostring(wallet->getBalance());
  fontRenderer->renderText(renderer, 45.0f + 25.0f, 12.0f + 24.0f * 4,
                                   a + "$");
}

void ShipGui::display(SDL_Renderer* renderer) {
  if(targetShip != NULL && targetShip->isDestroyed())
    targetShip = NULL;

  if(targetShip != NULL)
    displayShip(renderer);
  else if(targetIsland != NULL)
    displayIsland(renderer);
  else
    displayStats(renderer);
}

void ShipGui::mouseButtonPress(int key) {
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    if(targetShip != NULL) {
      invButton[i][0]->mouseButtonPress(key);
      invButton[i][1]->mouseButtonPress(key);
    } else if(targetIsland != NULL && targetIsland->getType() == PORT)
      buyButton[i]->mouseButtonPress(key);
  }
  if(targetShip != NULL || targetIsland != NULL)
    exitGuiButton->mouseButtonPress(key);
}

void ShipGui::mouseButtonRelease(int key) {
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    if(targetShip != NULL) {
      invButton[i][0]->mouseButtonRelease(key);
      invButton[i][1]->mouseButtonRelease(key);
    } else if(targetIsland != NULL && targetIsland->getType() == PORT)
      buyButton[i]->mouseButtonRelease(key);
  }
  if(targetShip != NULL || targetIsland != NULL)
    exitGuiButton->mouseButtonRelease(key);
}

void ShipGui::mouseMotion(float _x, float _y) {
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    if(targetShip != NULL) {
      invButton[i][0]->mouseMotion(_x, _y);
      invButton[i][1]->mouseMotion(_x, _y);
    } else if(targetIsland != NULL && targetIsland->getType() == PORT)
      buyButton[i]->mouseMotion(_x, _y);
  }
  if(targetShip != NULL || targetIsland != NULL)
    exitGuiButton->mouseMotion(_x, _y);
}

void ShipGui::setShip(Ship* _ship) {
  if(_ship != NULL) {
    targetIsland = NULL;
    targetShip = _ship;
  }
}

void ShipGui::update() {
  for(int i = 0; i < MAX_RESOURCES; ++i) {
    if(invButton[i][1]->isPressed()) {
      if(targetShip != NULL)
        targetShip->addRequest((Resource)i, 1);
      invButton[i][1]->resetButton();
    }
    
    if(invButton[i][0]->isPressed()) {
      if(targetShip != NULL)
        targetShip->removeRequest((Resource)i, 1);
      invButton[i][0]->resetButton();
    }
  }
  
  if(exitGuiButton->isPressed()) {
    exitGuiButton->resetButton();
    targetShip = NULL;
    targetIsland = NULL;
  }
}

void ShipGui::setIsland(Island* _island) {
  if(_island != NULL) {
    targetShip = NULL;
    targetIsland = _island;
  }
}

std::vector<Button*> ShipGui::getButtons() {
  return buyButton;
}

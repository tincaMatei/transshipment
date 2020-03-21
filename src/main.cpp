#include <SDL2/SDL.h>
#include <cstdio>
#include "game/mapgen.h"
#include "game/controller.h"
#include "room.h"

SDL_Window* window;
SDL_Renderer* renderer;

void init() {
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
  }
  
  window = SDL_CreateWindow("Transshipment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  
  if(window == NULL)
    SDL_Log("Unable to create window: %s\n", SDL_GetError());
  
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void deinit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  renderer = NULL;
  window = NULL;
  
  SDL_Quit();
}

// Testroom
class TestRoom : public Room {
private:
  Controller* controller;
public:
  TestRoom() {
    controller = new Controller();
  }
  
  ~TestRoom() {
    delete controller;
    controller = NULL;
  }
  
  void initialize() {
  }
  
  bool runGameLoop() {
    SDL_Event event;
    
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT)
        return false;
      else if(event.type == SDL_MOUSEMOTION)
        controller->mouseMotion((float)event.motion.x, (float)event.motion.y);
      else if(event.type == SDL_MOUSEBUTTONDOWN)
        controller->mouseButtonPress(event.button.button);
      else if(event.type == SDL_MOUSEBUTTONUP)
        controller->mouseButtonRelease(event.button.button);
    }
    
    controller->update();
    
    return true;
  }
  
  void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    
    controller->display(renderer);
  }
};

int main(int argc, char** argv) {
  init();
  
  TestRoom* testRoom = new TestRoom();
  while(testRoom->runGameLoop()) {
    testRoom->render(renderer);
    SDL_RenderPresent(renderer);
  }
  
  delete testRoom;
  
  deinit();
  return 0;
}

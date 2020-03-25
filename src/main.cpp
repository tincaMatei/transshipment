#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "game/mapgen.h"
#include "game/controller.h"
#include "room.h"
#include "graphicshandler.h"
#include "game/mainmenu.h"
#include "game/gameroom.h"
#include "game/helproom.h"

SDL_Window* window;
SDL_Renderer* renderer;
RoomContext roomContext;
Mix_Music* bgsong;

void init() {
  
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
  }
  
  window = SDL_CreateWindow("Transshipment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  
  if(window == NULL)
    SDL_Log("Unable to create window: %s\n", SDL_GetError());
  
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if(TTF_Init() == -1)
    SDL_Log("Unable to start SDL_ttf: %s\n", TTF_GetError());
  
  if(!IMG_Init(IMG_INIT_PNG))
    SDL_Log("Unable to start SDL_image: %s\n", IMG_GetError());
  
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    SDL_Log("Unable to start SDL_mixed: %s\n", Mix_GetError());
  bgsong = Mix_LoadMUS("media/bgmusic.mp3");
  if(bgsong == NULL)
    SDL_Log("Unable to load media/bgmusic.mp3: %s\n", Mix_GetError);
}

void deinit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  renderer = NULL;
  window = NULL;
  
  Mix_FreeMusic(bgsong);
  bgsong = NULL;
  
  TTF_Quit();
  SDL_Quit();
  IMG_Quit();
}

int main(int argc, char** argv) {
  init();
  
  TextureContext* textureContext = new TextureContext(renderer);
  
  Mix_VolumeMusic(MIX_MAX_VOLUME);
  int volume = 10;
  Mix_PlayMusic(bgsong, -1);
  
  MainMenu* mainMenuRoom = new MainMenu(textureContext);
  GameRoom* gameRoom = new GameRoom(textureContext, &volume);
  HelpRoom* helpRoom = new HelpRoom(textureContext);
  
  Room* currentRoom = mainMenuRoom;
  
  roomContext.pushRoom(currentRoom);
  roomContext.pushRoom(gameRoom);
  roomContext.pushRoom(helpRoom);
  
  bool quit = false;
  
  
  while(!quit) {    
    int lag = 0, lastT = SDL_GetTicks();
    currentRoom->initialize();
    
    bool keepRoom = true;
    while(keepRoom) {
      int nowT = SDL_GetTicks();
      lag = lag + nowT - lastT;
      lastT = nowT;
      while(keepRoom && lag >= MS_TICK_SIZE) {
        keepRoom &= currentRoom->runGameLoop();
        lag -= MS_TICK_SIZE;
      }
      currentRoom->render(renderer);
      SDL_RenderPresent(renderer);
    }
    
    if(currentRoom->getTransition() == -1)
      quit = true;
    else
      currentRoom = roomContext.getRoom(currentRoom->getTransition());
  }
  
  delete mainMenuRoom;
  
  deinit();
  return 0;
}

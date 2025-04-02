#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include "main.h"

// NOTE: im fallowing a bit of elm arch with this one.
// if you dont know what its is you dont have to. :3c

#define FPS_CAP 30
#define DELTA_TIME 1000 / FPS_CAP

SDL_Renderer *ren = NULL;
int shouldQuit = 0;

int win_w = 800;
int win_h = 600;

int debugTog = 1;



void debug(){
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // NOTE: text color
  SDL_RenderDebugText(ren, 10, 5, "ShareWare 0.0.1JAM Reguler Fleshy Guy");
  SDL_RenderDebugText(ren, 10, 10, "FPS %i", fps);
}

void update() { // user inputs and things like that
  SDL_Event evt;

  while (SDL_PollEvent(&evt)) {
    switch (evt.type) {
    case SDL_EVENT_QUIT:
      shouldQuit = 1;
      break;
    case SDL_EVENT_KEY_DOWN:
      switch (evt.key.key) {
        case SDLK_ESCAPE: // NOTE: EXAMPLE KEY is a quit key
          shouldQuit = 1;
          break;
        case SDLK_F3:
          debugTog = !debugTog;
      }
    }
  }
}

typedef enum {TITLE = 0, GAME, END} GameState;

GameState gState = 0;

void loop() { // the game loop right at the top not lost in main just here for our enjoyment
  while (!shouldQuit) {
    update();

    SDL_RenderClear(ren);
    
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    SDL_RenderPresent(ren);

  }
}

int main() {
  SDL_Window *win = NULL;
  
  printf("===========================================\n  THIS is the shareware build of the game  \n===========================================\n\n");
  printf("WELCOME TO REGULER FLESHY GUY\nGame for the FrenJam\n");
  printf("Source Code can be found at *link* made in C :3\n");
  
  SDL_SetAppMetadata("REGULER FLESHY GUY", "0.0.1JAM", NULL);
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_URL_STRING, "https://");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "game");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "Trent And Ramona");

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERORR",
                             "FAILED To Init Video And Or Events", NULL); // the box will most likey fail
    printf("FOO ERROR: FAILED To Init Video And Or Events %d\n", 1);        // if init failes but ehh... better to try
    return 1;
  }

  win = SDL_CreateWindow("FOO", win_w, win_h, SDL_WINDOW_OPENGL);
  if (win == NULL) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERROR",
                             "FAILED To Make The Window", NULL);
    printf("FOO ERROR: FAILED To Create Window %d\n", 2);
    return 2;
  }

  ren = SDL_CreateRenderer(win, NULL); // SDL RENDER OVER OPENGL OR VULKEN
  if (ren == NULL) {                   // SO I CAN HAVE LESS TIME PUT IN TO THE RENDERER
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERROR",
                             "FAILED To Make Renderer", NULL);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("FOO ERROR: FAILED To Create Renderer %d\n", 3);
    return 3;
  }
  //  TODO: add init for CIMGUI, file system and libxml2 file loading

  loop();

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>
#include "main.h"

/* NOTE: im doing a bit of elm arch with this one. 
 *       if you dont know what its is you dont have to. :3c */

/* TODO: 
 * [ ] Frame Rate Cap
 * [ ] Map
 * [ ] ViewPort
 * [ ] HUD 
 */

#define FPS_CAP 30                // WARN: I DONT THINK IM DOING THIS RIGHT
#define DELTA_TIME 1000 / FPS_CAP //       LIKE AT ALL >:3c

SDL_Renderer *ren = NULL;
SDL_Window *win = NULL;

int shouldQuit = 0;  // should quit is true so I can have it !

int win_w, win_h; // holds the windows size

int debugTog = 1;

void update() { // user updates in a diffrent funcion to stay orginised
  SDL_Event evt;

  while (SDL_PollEvent(&evt)) {
    switch (evt.type) {
    case SDL_EVENT_QUIT:
      shouldQuit = 1;
      break;
    case SDL_EVENT_KEY_DOWN: // NOTE: KEYBOARD INPUT FOR THE GAME
      switch (evt.key.key) {
        case SDLK_ESCAPE: // NOTE: EXAMPLE KEY is a quit key
          shouldQuit = 1;
          break;
        case SDLK_F3:
          debugTog = !debugTog; // BUG: THIS IS BARELY A BUG BUT, F3 CAN BE HELD DOWN THIS
          break;                //      CAUSES THE DEBUG UI TO TOGGLE ON AND OFF REALY FAST
      }
    }
  }
}

typedef enum {TITLE = 0, GAME, END} GameState;
GameState gState = 0;

void debug(){
  #define MARGEN 10
  
  // NOTE: THE TEXT IS 10pix PER LINE

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // NOTE: text color
  SDL_RenderDebugText(ren, MARGEN, 10, "Reguler Fleshy Guy: ShareWare 0.0.1JAM");
  SDL_RenderDebugText(ren, MARGEN, 20, "FPS "); // NOTE: THIS should be CAPPED at 30
  SDL_RenderDebugText(ren, MARGEN, 30, "Map Run Time "); // NOTE: Timer of how long you have been on the map
}

void loop() { // the game loop right at the top not lost in main just here for our enjoyment
  while (!shouldQuit) {
    update();

    SDL_RenderClear(ren);
    
    if(debugTog == 0){ 
      debug();
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // NOTE: BACKGROUND COLOR change this to hot pink for errors later
    
    SDL_RenderPresent(ren);

  }
}

int main() {

  printf("===============================================\n    THIS is the shareware build of the game    \n===============================================\n\n");
  printf("WELCOME TO REGULER FLESHY GUY\nGame for the FrenJam\n");
  printf("Source Code can be found at *link* made in C :3\n");
  
  SDL_SetAppMetadata("REGULER FLESHY GUY", "0.0.1JAM", NULL);
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_URL_STRING, "https://");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "game");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "Trent And Ramona");
  
  const int compiled = SDL_VERSION;    // hardcoded number from SDL headers
  const int linked = SDL_GetVersion(); // reported by linked SDL library

  SDL_Log("\nWe compiled against SDL version %d.%d.%d. ...\n",
          SDL_VERSIONNUM_MAJOR(compiled),
          SDL_VERSIONNUM_MINOR(compiled),
          SDL_VERSIONNUM_MICRO(compiled));

  SDL_Log("But we are linking against SDL version %d.%d.%d.\n",
          SDL_VERSIONNUM_MAJOR(linked),
          SDL_VERSIONNUM_MINOR(linked),
          SDL_VERSIONNUM_MICRO(linked));
  
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERORR",
                             "FAILED To Init Video And Or Events", NULL); // the box will most likey fail
    printf("FOO ERROR: FAILED To Init Video And Or Events %d\n", 1);      // if init failes but ehh... better to try
    return 1;
  }

  win = SDL_CreateWindow("FOO", 800, 600, SDL_WINDOW_OPENGL);
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
  
  SDL_GetWindowSize(win, &win_w, &win_h); // this lets us center the viewport
                                          // and have borders yay

  //  TODO: add init for CIMGUI, file system and map file loading

  loop();

  printf("byebye\n");
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}

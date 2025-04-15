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

/* NOTE: im doing a bit of elm arch with this one. 
 *       if you dont know what its is you dont have to. :3c */

/* TODO: 
 * [ ] Frame Rate Cap
 * [ ] Map
 * [ ] ViewPort
 * [ ] HUD 
 */

#define FPS_CAP 30                 // WARN: I DONT THINK IM DOING THIS RIGHT
#define DELTA_TIME 1000 / FPS_CAP  //       LIKE AT ALL >:3c

static SDL_Renderer *ren = NULL;
static SDL_Window *win = NULL;

int shouldQuit = 0;  // should quit is true so I can have it !

int debugTog = 1;
const char build[] = "0.0.1";
const char name[] = "Gilly and Figgin's Adventure";

void update() { // user updates in a diffrent funcion to stay orginised
  SDL_Event evt;

  while (SDL_PollEvent(&evt)) {
    switch (evt.type) { // NOTE: EXIT/DEBUG UI KEYBOARD
      case SDL_EVENT_QUIT:
        shouldQuit = 1;
        break; 
      case SDL_EVENT_KEY_UP: 
        switch (evt.key.key) {
          case SDLK_F3:
            debugTog = !debugTog; 
            break;
      }
    }
    switch (evt.type) { // NOTE: YET ANOTHER KEYBOARD BASED UPDATTER
      case SDL_EVENT_KEY_DOWN:
        switch (evt.key.key) {
        // buttons
          case SDLK_ESCAPE:
            break;
          case SDLK_Z: // jump
            break;
          case SDLK_X: // run
            break;
          case SDLK_C: // throw
            break;
        // movenet
          case SDLK_UP:
            break;
          case SDLK_DOWN:
            break;
          case SDLK_LEFT:
            break;
          case SDLK_RIGHT:
            break;
      }
    }
  }
}

typedef enum {TITLE = 0, GAME, END} GameState;
GameState gState = 0;

void debug(){
  #define MARGEN 10

  // NOTE: THE TEXT IS 10pix PER NEW LINE

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // NOTE: text color
  SDL_RenderDebugTextFormat(ren, MARGEN, 10, "%s, %s",name, build);
  SDL_RenderDebugTextFormat(ren, MARGEN, 20, "FPS: /* fps */"); // NOTE: THIS should be CAPPED at 30
  SDL_RenderDebugTextFormat(ren, MARGEN, 30, "MAP: /* name */, TIME /* count */");
  SDL_RenderDebugTextFormat(ren, MARGEN, 40, "TILES: /* count */, ENITES /* count */");
  SDL_RenderDebugTextFormat(ren, MARGEN, 50, "POS X /* PLAYER X */, POS Y /* PLAYER Y */");
}

void loop() { // the game loop right at the top not lost in main just here for our enjoyment
  while (!shouldQuit) {
    update();

    SDL_RenderClear(ren);
    
      if(debugTog == 0){ 
        debug();
      }

      SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);
    SDL_RenderPresent(ren);
  }
}

int main() {
  SDL_SetAppMetadata(name, build, NULL);
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_URL_STRING, "https://");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "game");
  SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_TYPE_STRING, "Ramona");
  
  printf("YOU GET SHIT");

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
                             "FAILED To Init Video And Or Events", NULL); // the box will most likey fail if the init failes
    printf("FOO ERROR: FAILED To Init Video And Or Events ERROR CODE %d\n", 1);      // thats why we have a printf fallback >:3c
    return 1;
  }

  win = SDL_CreateWindow("FOO", 800, 600, SDL_WINDOW_OPENGL);
  if (win == NULL) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERROR",
                             "FAILED To Make The Window", NULL);
    printf("FOO ERROR: FAILED To Create Window ERROR CODE %d\n", 2);
    return 2;
  }

  ren = SDL_CreateRenderer(win, NULL); // SDL RENDER OVER OPENGL OR VULKEN
  if (ren == NULL) {                   // SO I CAN HAVE LESS TIME PUT IN TO THE RENDERER
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FOO ERROR",
                             "FAILED To Make Renderer", NULL);
    SDL_DestroyWindow(win);
    SDL_Quit();
    printf("FOO ERROR: FAILED To Create Renderer ERROR CODE %d\n", 3);
    return 3;
  }
  
  SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);

  SDL_SetRenderLogicalPresentation(ren, 800, 600, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  loop();

  printf("byebye\n");
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}

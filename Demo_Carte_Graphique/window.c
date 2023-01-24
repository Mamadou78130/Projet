#include <stdlib.h>
#include <GL4D/gl4du.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4duw_SDL2.h>
#include "animations.h"
#include "audioHelper.h"
#include "primitives.h"
#include <assert.h>
#include <GL4D/gl4dp.h>

static void init(void);
static void quit(void);
static void resize(int w, int h);
static void keydown(int keycode);

static GL4DHanime _animations[] = {
  
  { 3000, exemple_d_animation_00, NULL, NULL },
  { 2200, exemple_d_animation_01, NULL, NULL },

  { 2000, exemple_d_animation_04, NULL, NULL },

  { 3000, exemple_d_animation_00, NULL, NULL },
  { 2200, exemple_d_animation_02, NULL, NULL },

  { 2200, exemple_d_animation_03, NULL, NULL },
  { 1000, exemple_d_animation_06, NULL, NULL },

  { 2000, exemple_d_animation_05, NULL, NULL },
  { 2000, exemple_d_animation_07, NULL, NULL },


  {    0, NULL, NULL, NULL }
};


static GLfloat _dim[] = {1024, 768};

int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "GL4Dummies DemoHelper", 
			 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			 _dim[0], _dim[1],
			 SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN))
    return 1;
  init();
  atexit(quit);
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(keydown);
  gl4duwDisplayFunc(gl4dhDraw);

  ahInitAudio("paper_-_focus.it");
  gl4duwMainLoop();
  return 0;
}

static void init(void) {
  glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
  gl4dhInit(_animations, _dim[0], _dim[1], animationsInit);
  resize(_dim[0], _dim[1]);
}

static void resize(int w, int h) {
  _dim[0] = w; _dim[1] = h;
  glViewport(0, 0, _dim[0], _dim[1]);
}

static void keydown(int keycode) {
  switch(keycode) {
  case SDLK_ESCAPE:
  case 'q':
    exit(0);
  default: break;
  }
}

static void quit(void) {
  ahClean();
  gl4duClean(GL4DU_ALL);
}

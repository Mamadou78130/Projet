#include <GL4D/gl4dh.h>
#include "audioHelper.h"
#include <assert.h>
#include <stdlib.h>
#include <GL4D/gl4dg.h>
#include <SDL_image.h>
#include "primitives.h"
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>

static GLuint _quadId = 0;

void exemple_de_transition_00(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  switch(state) {
  case GL4DH_INIT:
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default:

    if(a0) a0(state);
    if(a1) a1(state);
    return;
  }
}

void exemple_de_transition_01(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state) {
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch(state) {
  case GL4DH_INIT:
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for(i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/mix.fs", NULL);
    return;
  case GL4DH_FREE:
    if(tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    if(a0) a0(state);
    if(a1) a1(state);
    return;
  default:
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &tId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[0],  0);
    if(a0) a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tex[1],  0);
    if(a1) a1(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,  tId,  0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if(et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void exemple_d_animation_00(int state) {
  int l, i;
  Uint16 * s;
  static GLfloat c[4] = {0, 0, 0, 0};
  switch(state) {
  case GL4DH_INIT:
    return;
  case GL4DH_FREE:
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if(l >= 8)
      for(i = 0; i < 4; i++)
	c[i] = s[i] / ((1 << 16) - 1.0);
    return;
  default:
    glClearColor(c[0], c[1], c[2], c[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    return;
  }
}

static void copyFromSurface(SDL_Surface * s, int x0, int y0) {
  Uint32 * p, coul, ocoul;
  Uint8 rmix, gmix, bmix;
  double f1, f2;
  int x, y, maxx, maxy;
  assert(s->format->BytesPerPixel == 4);
  p = s->pixels;
  maxx = MIN(x0 + s->w, gl4dpGetWidth());
  maxy = MIN(y0 + s->h, gl4dpGetHeight());
  for(y = y0; y < maxy; y++) {
    for(x = x0; x < maxx; x++) {
      ocoul = gl4dpGetPixel(x, y);
      coul = p[(s->h - 1 - (y - y0)) * s->w + x - x0];
      f1 = ALPHA(coul) / 255.0; f2 = 1.0 - f1;
      rmix = f1 *   RED(coul) + f2 *   RED(ocoul);
      gmix = f1 * GREEN(coul) + f2 * GREEN(ocoul);
      bmix = f1 *  BLUE(coul) + f2 *  BLUE(ocoul);
      gl4dpSetColor(RGB(rmix, gmix, bmix));
      gl4dpPutPixel(x, y);
    }
  }
}

void exemple_d_animation_01(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("images/batman.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, rand() % gl4dpGetWidth(),rand() % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void exemple_d_animation_02(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("images/superman.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, rand() % gl4dpGetWidth(),rand() % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void exemple_d_animation_03(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("images/fight.gif");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, rand() % gl4dpGetWidth(),rand() % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}


void exemple_d_animation_04(int state) {
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {0.0, 0.0, 0.5, 0.5}, r2[] = {0, 0, 1, 1}, r = 0.0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    sprite = IMG_Load("images/versus.jpg");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.01;
    r1[2] += 0.01;
    r -= 0.02;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}

void exemple_d_animation_05(int state) {
  const GLfloat s[2] = {1.0, -1.0}, t[2] = {0.0, 1.0};
  static GLfloat r1[] = {0.0, 0.0, 0.5, 0.5}, r2[] = {0, 0, 1, 1}, r = 0.0;
  static SDL_Surface * sprite = NULL;
  static GLuint s1 = 0, s2 = 0;
  switch(state) {
  case GL4DH_INIT:
    sprite = IMG_Load("images/winner.png");
    s1 = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    s2 = gl4dpInitScreen();
    gl4dpCopyFromSDLSurfaceWithTransforms(sprite, s, t);
    gl4dpMap(s1, s2, r1, r2, 0.0);
    return;
  case GL4DH_FREE:
    gl4dpSetScreen(s1);
    gl4dpDeleteScreen();
    gl4dpSetScreen(s2);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(s1);
    gl4dpUpdateScreen(NULL);
    r1[0] += 0.01;
    r1[2] += 0.01;
    r -= 0.02;
    gl4dpMap(s1, s2, r1, r2, r);
    return;
  }
}

void exemple_d_animation_06(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("images/poing.jpeg");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, 10 % gl4dpGetWidth(),10 % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}

void exemple_d_animation_07(int state) {
  static SDL_Surface * sprite = NULL;
  static GLuint screen_id = 0;
  switch(state) {
  case GL4DH_INIT: {
    SDL_Surface * s = IMG_Load("images/batman-winner.png");
    sprite = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    SDL_FreeSurface(s);
    screen_id = gl4dpInitScreen();
    gl4dpClearScreenWith(0xFFFFFFFF);
    return;
  }
  case GL4DH_FREE:
    gl4dpSetScreen(screen_id);
    gl4dpDeleteScreen();
    if(sprite) {
      SDL_FreeSurface(sprite);
      sprite = NULL;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
    gl4dpSetScreen(screen_id);
    copyFromSurface(sprite, 250 % gl4dpGetWidth(),10 % gl4dpGetHeight());
    gl4dpUpdateScreen(NULL);
    return;
  }
}


static void copyFromSDLSurface(SDL_Surface * s);

void exemple_d_animation_08(int state) {
  static float a = 0.0f;
  int i, j;
  static triangle_t _t[2] = {
			   { { {  0,   0, {1.0f, 0.0f, 0.0f, 1.0f}, { 0.0f,   0.0f}},
			       {  0, 479, {0.0f, 1.0f, 0.0f, 1.0f}, { 0.0f,  -1.0f}},
			       {639, 479, {0.0f, 0.0f, 1.0f, 1.0f}, { 1.0f,  -1.0f}} } },
			   { { {  0,   0, {1.0f, 0.0f, 0.0f, 1.0f}, { 0.0f,   0.0f}},
			       {639,   0, {1.0f, 1.0f, 0.0f, 1.0f}, { 1.0f,   0.0f}},
			       {639, 479, {0.0f, 0.0f, 1.0f, 1.0f}, { 1.0f,  -1.0f}} } }};
  static SDL_Surface *s;
  static GLuint _screenId = 0, _texId = 0;
  switch(state) {
  case GL4DH_INIT:
    _screenId = gl4dpInitScreen();
    s = SDL_LoadBMP("images/pandas.bmp");
    _texId = gl4dpInitScreenWithDimensions(s->w, s->h);
    return;
  case GL4DH_FREE:
    copyFromSDLSurface(s);
    SDL_FreeSurface(s);
    setTexture(_texId);
    gl4dpSetScreen(_screenId);
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    return;
  default:
  for(i = 0; i < 2; ++i)
    for(j = 0; j < 3; ++j) {
      if(fabs(_t[i].p[j].texCoord.x) > FLT_EPSILON)
	_t[i].p[j].texCoord.x = 1.0f + 65536.0f * fabs(sin(a));
      if(fabs(_t[i].p[j].texCoord.y) > FLT_EPSILON)
	_t[i].p[j].texCoord.y = -(1.0f + 65536.0f * fabs(sin(a)));
    }
  gl4dpClearScreen();
  fillTriangle(&_t[0]);
  fillTriangle(&_t[1]);
  gl4dpScreenHasChanged();
  gl4dpUpdateScreen(NULL);
  a += 0.000001f;
  }
}

void copyFromSDLSurface(SDL_Surface * s) {
  GLuint * p = gl4dpGetPixels();
  SDL_Surface * d = SDL_CreateRGBSurface(0, s->w, s->h, 32, R_MASK, G_MASK, B_MASK, A_MASK);
  SDL_BlitSurface(s, NULL, d, NULL);  
  memcpy(p, d->pixels, d->w * d->h * sizeof *p);
  SDL_FreeSurface(d);
}

void animationsInit(void) {
  if(!_quadId)
    _quadId = gl4dgGenQuadf();
}

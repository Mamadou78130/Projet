#include "primitives.h"
#include <assert.h>

static void abscisses(vertex_t * p0, vertex_t * p1, vertex_t * absc, int replace);
static void drawHLine(vertex_t * vG, vertex_t * vD, int y);

void fillTriangle(triangle_t * t) {
  int bas, median, haut, n, signe, i;
  vertex_t * aG = NULL, * aD = NULL;
  if(t->p[0].y < t->p[1].y) {
    if(t->p[0].y < t->p[2].y) {
      bas = 0;
      if(t->p[1].y < t->p[2].y) {
	median = 1;
	haut = 2;
      } else {
	median = 2;
	haut = 1;
      }
    } else {
      bas = 2;
	median = 0;
	haut = 1;
    }
  } else { 
    if(t->p[1].y < t->p[2].y) {
      bas = 1;
      if(t->p[0].y < t->p[2].y) {
	median = 0;
	haut = 2;
      } else {
	median = 2;
	haut = 0;
      }
    } else {
      bas = 2;
	median = 1;
	haut = 0;
    }
  }
  n = t->p[haut].y - t->p[bas].y + 1;
  aG = malloc(n * sizeof *aG);
  assert(aG);
  aD = malloc(n * sizeof *aD);
  assert(aD);

  if(t->p[haut].x == t->p[bas].x || t->p[haut].y == t->p[bas].y) {

    signe = (t->p[median].x > t->p[haut].x) ? -1 : 1;
  } else {
    float a, c, x;
    a = (t->p[haut].y - t->p[bas].y) / (float)(t->p[bas].x - t->p[haut].x);
    c = -a * t->p[haut].x - t->p[haut].y;
    x = -(c + t->p[median].y) / a;
    signe = (t->p[median].x >= x) ? -1 : 1;
  }
  if(signe < 0) { 
    abscisses(&(t->p[haut]), &(t->p[bas]), aG, 1);
    abscisses(&(t->p[haut]), &(t->p[median]), aD, 1);
    abscisses(&(t->p[median]), &(t->p[bas]), &aD[t->p[haut].y - t->p[median].y], 0);
  } else { 
    abscisses(&(t->p[haut]), &(t->p[bas]), aD, 1);
    abscisses(&(t->p[haut]), &(t->p[median]), aG, 1);
    abscisses(&(t->p[median]), &(t->p[bas]), &aG[t->p[haut].y - t->p[median].y], 0);
  }

  for(i = 0; i < n; ++i) {
    if(t->p[haut].y - i >= 0 && t->p[haut].y - i < gl4dpGetHeight())
      drawHLine(&aG[i], &aD[i], t->p[haut].y - i);

  }
  free(aG);
  free(aD);
}

void drawLine(int x0, int y0, int x1, int y1, GLuint color) {
  int u = x1 - x0, v = y1 - y0, pasX = u < 0 ? -1 : 1, pasY = v < 0 ? -1 : 1;
  int w = gl4dpGetWidth();
  GLuint * image = gl4dpGetPixels();
  u = abs(u); v = abs(v);
  if(u > v) { 
    int objX = (u + 1) * pasX;
    int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
    for (int x = 0, y = 0; x != objX; x += pasX) {
      if(IN_SCREEN(x + x0, y0 + y))
	image[(y0 + y) * w + x + x0] = color;
      if(delta < 0) {
	y += pasY;
	delta += incO;
      } else
	delta += incH;
    }
  } else {
    int objY = (v + 1) * pasY;
    int delta = v - 2 * u, incH = -2 * u, incO = 2 * v - 2 * u;
    for (int x = 0, y = 0; y != objY; y += pasY) {
      if(IN_SCREEN(x + x0, y0 + y))
	image[(y0 + y) * w + x + x0] = color;
      if(delta < 0) {
	x += pasX;
	delta += incO;
      } else
	delta += incH;
    }
  }
}

void abscisses(vertex_t * p0, vertex_t * p1, vertex_t * absc, int replace) {
  int u = p1->x - p0->x, v = p1->y - p0->y, pasX = u < 0 ? -1 : 1, pasY = v < 0 ? -1 : 1;
  float dmax = sqrt(u * u + v * v), d, p;
  u = abs(u); v = abs(v);
  if(u > v) { 
    if(replace) {
      int objX = (u + 1) * pasX;
      int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
      for (int x = 0, y = 0, k = 0; x != objX; x += pasX) {
	absc[k].x = x + p0->x;
	d = sqrt(x * x + y * y);
	p = d / dmax;
	absc[k].color.x    = (1.0f - p) *    p0->color.x + p *    p1->color.x;
	absc[k].color.y    = (1.0f - p) *    p0->color.y + p *    p1->color.y;
	absc[k].color.z    = (1.0f - p) *    p0->color.z + p *    p1->color.z;
	absc[k].color.w    = (1.0f - p) *    p0->color.w + p *    p1->color.w;
	absc[k].texCoord.x = (1.0f - p) * p0->texCoord.x + p * p1->texCoord.x;
	absc[k].texCoord.y = (1.0f - p) * p0->texCoord.y + p * p1->texCoord.y;
	if(delta < 0) {
	  ++k;
	  y += pasY;
	  delta += incO;
	} else
	  delta += incH;
      }
    } else {
      int objX = (u + 1) * pasX;
      int delta = u - 2 * v, incH = -2 * v, incO = 2 * u - 2 * v;
      for (int x = 0, y = 0, k = 0, done = 0; x != objX; x += pasX) {
	if(!done) {
	  absc[k].x = x + p0->x;
	  d = sqrt(x * x + y * y);
	  p = d / dmax;
	  absc[k].color.x    = (1.0f - p) *    p0->color.x + p *    p1->color.x;
	  absc[k].color.y    = (1.0f - p) *    p0->color.y + p *    p1->color.y;
	  absc[k].color.z    = (1.0f - p) *    p0->color.z + p *    p1->color.z;
	  absc[k].color.w    = (1.0f - p) *    p0->color.w + p *    p1->color.w;
	  absc[k].texCoord.x = (1.0f - p) * p0->texCoord.x + p * p1->texCoord.x;
	  absc[k].texCoord.y = (1.0f - p) * p0->texCoord.y + p * p1->texCoord.y;
	  done = 1;
	}
	if(delta < 0) {
	  ++k;
	  done = 0;
	  y += pasY;
	  delta += incO;
	} else
	  delta += incH;
      }
    }
  } else { 
    int objY = (v + 1) * pasY;
    int delta = v - 2 * u, incH = -2 * u, incO = 2 * v - 2 * u;
    for (int x = 0, y = 0, k = 0; y != objY; y += pasY) {
      absc[k].x = x + p0->x;
      d = sqrt(x * x + y * y);
      p = d / dmax;
      absc[k].color.x    = (1.0f - p) *    p0->color.x + p *    p1->color.x;
      absc[k].color.y    = (1.0f - p) *    p0->color.y + p *    p1->color.y;
      absc[k].color.z    = (1.0f - p) *    p0->color.z + p *    p1->color.z;
      absc[k].color.w    = (1.0f - p) *    p0->color.w + p *    p1->color.w;
      absc[k].texCoord.x = (1.0f - p) * p0->texCoord.x + p * p1->texCoord.x;
      absc[k].texCoord.y = (1.0f - p) * p0->texCoord.y + p * p1->texCoord.y;
      ++k;
      if(delta < 0) {
	x += pasX;
	delta += incO;
      } else
	delta += incH;
    }
  }
}

static GLuint * _tex = NULL, _texW = 0, _texH = 0;

void setTexture(GLuint screen) {
  GLuint oldId = gl4dpGetTextureId(); 
  gl4dpSetScreen(screen);
  _tex = gl4dpGetPixels();
  _texW = gl4dpGetWidth();
  _texH = gl4dpGetHeight();
  gl4dpSetScreen(oldId);
}

#define EPSILON FLT_EPSILON
void drawHLine(vertex_t * vG, vertex_t * vD, int y) {
  int w = gl4dpGetWidth(), x, yw = y * w, xt, yt;
  GLuint * image = gl4dpGetPixels();
  float dmax = vD->x - vG->x, p = 0.0f, deltap = 1.0f / dmax;
  vec4 c;
  vec2 tc;
  GLubyte r, g, b, a;
  for(x = vG->x, p = 0.0f; x <= vD->x; ++x, p += deltap)
    if(IN_SCREEN(x, y)) {
      c.x    = (1.0f - p) *    vG->color.x + p *    vD->color.x;
      c.y    = (1.0f - p) *    vG->color.y + p *    vD->color.y;
      c.z    = (1.0f - p) *    vG->color.z + p *    vD->color.z;
      c.w    = (1.0f - p) *    vG->color.w + p *    vD->color.w;
      tc.x   = (1.0f - p) * vG->texCoord.x + p * vD->texCoord.x;
      tc.y   = (1.0f - p) * vG->texCoord.y + p * vD->texCoord.y;
      xt = (int)(tc.x * (_texW - EPSILON));
      if(xt < 0) {
	xt = xt % (-_texW);
	while(xt < 0) xt += _texW;
      } else
	xt = xt % _texW;
      yt = (int)(tc.y * (_texH - EPSILON));
      if(yt < 0) {
	yt = yt % (-_texH);
	while(yt < 0) yt += _texH;
      } else 
	yt = yt % _texH;

      r = (GLubyte)((  RED(_tex[yt * _texW + xt]) + EPSILON) * c.x);
      g = (GLubyte)((GREEN(_tex[yt * _texW + xt]) + EPSILON) * c.y);
      b = (GLubyte)(( BLUE(_tex[yt * _texW + xt]) + EPSILON) * c.z);
      a = (GLubyte)((ALPHA(_tex[yt * _texW + xt]) + EPSILON) * c.w);
      image[yw + x] = _tex[yt * _texW + xt];
    }
}


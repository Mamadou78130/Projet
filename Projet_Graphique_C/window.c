#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>

static void initGL(void);
static void initTex(void);
static void resize(int w, int h);
static void clavier(int touch);
static void clavier_v(void);
static void clavier_e(int touch);
static void souris(int x, int y);
static void dessiner(void);
static void quitter(void);
static void mur(void);
static void collision(void);

/* pour labyrinthe.c */
extern unsigned int * labyrinth(int w, int h);

/* largeur et hauteur de la fenêtre */
static int haut = 800, larg = 600;
/* position de la souris */
static int souris_x = 400, souris_y = 300;
/* ici le labyrinthe à générer */
static GLuint * labyrinthe = NULL;
/* côté labyrinth */
static GLuint lab = 15;
static GLuint quad = 0;
static GLuint cube = 0;
static GLuint shaders = 0;
static GLuint planeTex = 0;
static GLfloat planeScale = 100.0f;

/* énumération pour les commandes du clavier */
enum clav {
  KLEFT = 0,
  KRIGHT,
  KUP,
  KDOWN
};

static GLuint clav_t[] = {0, 0, 0, 0};

/* stocker la position de la caméra et de son orientation */
typedef struct camera camera;
struct camera {
  GLfloat x, z;
  GLfloat orient;
};

/* la caméra */
static camera cam = {0, 0, 0};


/* création de la fenêtre et initialise les paramètres OpenGL */
int main(int argc, char ** argv) {
  if(!gl4duwCreateWindow(argc, argv, "Labyrinthe", 10, 10,
                         haut, larg, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;
  initGL();
  initTex();
  gl4duwResizeFunc(resize);
  gl4duwKeyDownFunc(clavier);
  gl4duwIdleFunc(clavier_v);
  gl4duwKeyUpFunc(clavier_e);
  gl4duwPassiveMotionFunc(souris);
  gl4duwDisplayFunc(dessiner);
  atexit(quitter);
  gl4duwMainLoop();
  return 0;
}

/* initialise les paramètres OpenGL */
static void initGL(void) {
  glClearColor(0.9f, 0.5f, 0.5f, 0.9f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  shaders = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/basic.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "matrice_m");
  gl4duGenMatrix(GL_FLOAT, "matrice_v");
  gl4duGenMatrix(GL_FLOAT, "matrice_p");
  resize(haut, larg);
}

/* création des objets 3D et des textures 2D. */
static void initTex(void) {
  quad = gl4dgGenQuadf();
  cube = gl4dgGenCubef();

  /* création et paramétrage de la texture plane */
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  labyrinthe = labyrinth(lab, lab);
}

/* param w largeur de la fenêtre */
/* param h hauteur de la fenêtre */
 
static void resize(int w, int h) {
  haut = w; 
  larg = h;
  gl4duBindMatrix("matrice_p");
  gl4duLoadIdentityf();
  gl4duFrustumf(-0.5, 0.5, -0.5 * larg / haut, 0.5 * larg / haut, 1.0, planeScale + 1.0);
}

/* Suivi de la position dans le monde avec la position sur la carte. */
static void changePosition(void) {
  GLfloat x1, z1;
  static int x2 = -1, z2 = -1;
  x1 = cam.x + planeScale;
  z1 = -cam.z + planeScale;
  x1 = x1 / (2.0f * planeScale);
  z1 = z1 / (2.0f * planeScale);
  x1 = x1 * lab;
  z1 = z1 * lab;
  /* réinitialise la position précédente en noir et la nouvelle en rouge */
  if((int)x1 != x2 || (int)z1 != z2) {
    if(x2 >= 0 && x2 < lab && z2 >= 0 && z2 < lab && labyrinthe[z2 * lab + x2] != -1) {
      labyrinthe[z2 * lab + x2] = 0;
      glBindTexture(GL_TEXTURE_2D, planeTex);

    }
    x2 = (int)x1;
    z2 = (int)z1;
    if(x2 >= 0 && x2 < lab && z2 >= 0 && z2 < lab && labyrinthe[z2 * lab + x2] != -1) {
      labyrinthe[z2 * lab + x2] = RGB(255, 255, 0);
      glBindTexture(GL_TEXTURE_2D, planeTex);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lab, lab, 0, GL_RGBA, GL_UNSIGNED_BYTE, labyrinthe);
    }
  }
}

static void clavier(int touch) {
  switch(touch) {
  case GL4DK_LEFT:
    clav_t[KLEFT] = 1;
    break;
  case GL4DK_RIGHT:
    clav_t[KRIGHT] = 1;
    break;
  case GL4DK_UP:
    clav_t[KUP] = 1;
    break;
  case GL4DK_DOWN:
    clav_t[KDOWN] = 1;
    break;
  case 'q':
    exit(0);
  default:
    break;
  }
}

/* stocke les états du clavier virtuel */
static void clavier_e(int touch) {
  switch(touch) {
  case GL4DK_LEFT:
    clav_t[KLEFT] = 0;
    break;
  case GL4DK_RIGHT:
    clav_t[KRIGHT] = 0;
    break;
  case GL4DK_UP:
    clav_t[KUP] = 0;
    break;
  case GL4DK_DOWN:
    clav_t[KDOWN] = 0;
    break;
  default:
    break;
  }
}

/* utilise le clavier virtuel pour déplacer la caméra selon direction orientation et temps */
static void clavier_v(void) {
  double m, orient_d = M_PI, multi = 5.0;
  static double p = 0, q;
  m = ((q = gl4dGetElapsedTime()) - p) / 1000.0;
  p = q;
  if(clav_t[KLEFT])
    cam.orient += m * orient_d;
  if(clav_t[KRIGHT])
    cam.orient -= m * orient_d;
  if(clav_t[KUP]) {
    cam.x += -m * multi * sin(cam.orient);
    cam.z += -m * multi * cos(cam.orient);
  }
  if(clav_t[KDOWN]) {
    cam.x += m * multi * sin(cam.orient);
    cam.z += m * multi * cos(cam.orient);
  }
  changePosition();
}

static void souris(int x, int y) {
  souris_x = x; 
  souris_y = y;
}



static void dessiner(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaders);

  /* pour dessiner la map */
  gl4duBindMatrix("matrice_v");
  gl4duLoadIdentityf();
  gl4duLookAtf(cam.x, 3.0, cam.z, 
	       cam.x - sin(cam.orient), 3.0 - (souris_y - (larg >> 1)) / (GLfloat)larg, cam.z - cos(cam.orient), 
	       0.0, 1.0,0.0);
  gl4duBindMatrix("matrice_m");
  gl4duLoadIdentityf();
  gl4duPushMatrix(); {
    gl4duRotatef(-90, 1, 0, 0);
    gl4duScalef(planeScale, planeScale, 1);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glUniform1f(glGetUniformLocation(shaders, "Texture"), 1.0);
  gl4dgDraw(quad);

    /* pour dessiner la carte */
  gl4duBindMatrix("matrice_p");
  gl4duPushMatrix(); {
    gl4duLoadIdentityf();
    gl4duOrthof(-1.0, 1.0, -larg / (GLfloat)haut, larg / (GLfloat)haut, 0.0, 2.0);
    gl4duBindMatrix("matrice_m");
    gl4duPushMatrix(); {
      gl4duLoadIdentityf();
      gl4duTranslatef(0.5, -0.5, 0.0);
      gl4duScalef(1.0 / 5.0, 1.0 / 5.0, 1.0);
      gl4duBindMatrix("matrice_v");
      gl4duPushMatrix(); {
	gl4duLoadIdentityf();
	gl4duSendMatrices();
      } gl4duPopMatrix();
      gl4duBindMatrix("matrice_m");
    } gl4duPopMatrix();
    gl4duBindMatrix("matrice_p");
  } gl4duPopMatrix();
  gl4duBindMatrix("matrice_m");
  glUniform1i(glGetUniformLocation(shaders, "bordure"), 1);
  gl4dgDraw(quad);
  glUniform1i(glGetUniformLocation(shaders, "bordure"), 0);
}

static void quitter(void) {
  if(labyrinthe) 
    free(labyrinthe);    
  if(planeTex)
    glDeleteTextures(1, &planeTex);
  gl4duClean(GL4DU_ALL);
}

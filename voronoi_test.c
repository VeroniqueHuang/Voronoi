#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <unistd.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>

#define SIZE 10

/*
#define Green = rgb <0, 1, 0>
#define Blue = rgb <0, 0, 1>
#define Yellow = rgb <1,1,0>
#define Cyan = rgb <0, 1, 1>
#define Magenta = rgb <1, 0, 1>
#define Clear = rgbf 1
#define White = rgb 1
#define Black = rgb 0*/

typedef struct couleur couleur;
struct couleur {
  float r;
  float g;
  float b;
};

typedef struct site_t site_t;
struct site_t {
  int x, y;
  couleur color;
  int alive;
};
static int nbCells, radius;
static site_t diag[SIZE];

int rand_a_b (int a, int b){
  return rand()%(b-a)+a;
}

int diagGrow(){
  int i;
  for(i=0; i<nbCells; i++){
    printf("%d heeeereee \n",nbCells);
  }
  return 1;
}

void diagInit(int nb){
  nbCells = nb;
  int i, x, y;
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  for( i=0; i<nb ; i++){
    x = rand_a_b(0,w);
    y = rand_a_b(0,h);
    diag[i].x = x;
    diag[i].y = y;
    diag[i].color.r = 1.0f;
    diag[i].color.g = 0.0f;
    diag[i].color.b = 0.0f;
    diag[i].alive = 1;
  }
}

void dessin(){
  if(!diagGrow()){
    printf("OOOKKK\n" );
    diagInit(1);
  }
}

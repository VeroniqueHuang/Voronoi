#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "ima.h"
#include <limits.h>

#define SIZE 10

typedef struct Point Point;
struct Point {
    GLint x;
    GLint y;
};

typedef struct Color Color;
struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

typedef struct site_t site_t;
struct site_t {
  int x, y;
  Color color;
  int alive;
};
static int nbCells, radius;
static site_t diag[SIZE];

int rand_a_b (int a, int b){
  return rand()%(b-a)+a;
}

Color getmyPixelColor (int x, int y){
  Color color;
  glReadPixels(x,y,1,1,GL_RGB, GL_FLOAT, &color);
  return color;
}

void setPixelColor(int x, int y, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int circleNOM(int x0, int y0, int r){
  int x, y,
  for(x = 0, y = r; x <= t; x++, incH += 4, incO += 4) {
  if(getmyPixelColor())
  return 1;
}

int diagGrow(int nb){
/*
int i, ii;
int j,k;
  printf("size %d \n", nb);
  for(i=0 ; i<nb; i++){
    j=diag[i].x-20;
    k=diag[i].y-20;
    printf("herreee : %d et %d \n", diag[i].x, diag[i].y);
    for(int a=j; a<diag[i].x; a++){
      for(int b=k; b<diag[i].y; b++){
        setPixelColor(a,b,diag[i].color);
      }
    }
  }*/

  int i, fini =1;
  for(i=0; i<nbCells; i++){
    if(!diag[i].alive) continue;

    if(circleNOM(diag[i].x, diag[i].y, radius))
      fini = 0;
    else{
      diag[i].alive = 0;
      printf("finish my voronoi number %d \n", i);
    }

  }

  return 0;
}

void diagInit (int nb){
  nbCells = nb;
  Color pixelColor;
  int i, x, y;
  int w =  glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  for(i=0 ; i<nb; i++){
    x = rand_a_b(1,w-1);
    y = rand_a_b(1,h-1);
    pixelColor = getmyPixelColor(x,y);
    diag[i].x = x;
    diag[i].y = y;
    diag[i].color = getmyPixelColor(diag[i].x,diag[i].y);
    diag[i].alive = 1;
  }
}

void grisgris (Image *im) {
  //OKK put pixel
/*  int j,i;
  Color colori = getmyPixelColor(1,1);
  for(i=0, j=0; i<600; i++, j++ ){
    for(j=0; j<600; j++){
      setPixelColor(i,j,colori);
    }
  }*/
  radius = 1;
  diagInit(5);
  if(!diagGrow(5)){
    printf("OOOKKK\n" );
  }
}

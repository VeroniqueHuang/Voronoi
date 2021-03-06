#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "ima.h"
#include <limits.h>


#define SIZE 15

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
static site_t diag[SIZE];
static int nbCells, radius;

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

int isBlack(int x,int y){
  Color color;
  color = getmyPixelColor(x,y);
  //printf("%d et %d et %d \n", color.r, color.g, color.b);
  if(color.g==0 && color.b==0){
    return 1;
  }
  return 0;
}

int notFull(Image *im){
  int i, j;
  //int w =  glutGet(GLUT_WINDOW_WIDTH);
  //int h = glutGet(GLUT_WINDOW_HEIGHT);
  for(i=1; i<2; i++){
    for(j=1; j<2; j++){
      if(isBlack(i,j)){
        return 1;
      }
    }
  }
  return 0;
}

int inScreen(int x, int y){
  int w =  glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  if(x>0 && x<=w){
    if(y>0 && y<=h){
      return 1;
    }
    return 0;
  }
  return 0;
}

int circleNOM(int x0, int y0, Color colori, int r){
//  printf("daccord \n");
  int ret=0;
  int x, y, del, incH, incO, t = M_SQRT1_2 * r + 1;
  //printf("%d ou float %f \n", ret,M_SQRT1_2);
  del = 3 - (r << 1);
  incH = 6;
  incO = 10 - (r << 2);
  for(x = 0, y = r; x <= t; x++, incH += 4, incO += 4) {
  if(inScreen
    (x0 + x, y0 + y)) if(isBlack(x0 + x, y0 + y)) {setPixelColor(x0 + x, y0 + y, colori); ret=1;}
  if(inScreen
    (x0 + x, y0 - y)) if(isBlack(x0 + x, y0 - y)) {setPixelColor(x0 + x, y0 - y, colori); ret=1;}
  if(inScreen
    (x0 - x, y0 + y)) if(isBlack(x0 - x, y0 + y)) {setPixelColor(x0 - x, y0 + y, colori); ret=1;}
  if(inScreen
    (x0 - x, y0 - y)) if(isBlack(x0 - x, y0 - y)) {setPixelColor(x0 - x, y0 - y, colori); ret=1;}
  if(inScreen
    (x0 + y, y0 + x)) if(isBlack(x0 + y, y0 + x)) {setPixelColor(x0 + y, y0 + x, colori); ret=1;}
  if(inScreen
    (x0 + y, y0 - x)) if(isBlack(x0 + y, y0 - x)) {setPixelColor(x0 + y, y0 - x, colori); ret=1;}
  if(inScreen
    (x0 - y, y0 + x)) if(isBlack(x0 - y, y0 + x)) {setPixelColor(x0 - y, y0 + x, colori); ret=1;}
  if(inScreen
    (x0 - y, y0 - x)) if(isBlack(x0 - y, y0 - x)) {setPixelColor(x0 - y, y0 - x, colori); ret=1;}
  if(del < 0) del += incH;
  else{
    y--;
    if(inScreen
      (x0 + x, y0 + y)) if(isBlack(x0 + x, y0 + y)) {setPixelColor(x0 + x, y0 + y, colori); ret=1;}
    if(inScreen
      (x0 + x, y0 - y)) if(isBlack(x0 + x, y0 - y)) {setPixelColor(x0 + x, y0 - y, colori); ret=1;}
    if(inScreen
      (x0 - x, y0 + y)) if(isBlack(x0 - x, y0 + y)) {setPixelColor(x0 - x, y0 + y, colori); ret=1;}
    if(inScreen
      (x0 - x, y0 - y)) if(isBlack(x0 - x, y0 - y)) {setPixelColor(x0 - x, y0 - y, colori); ret=1;}
    if(inScreen
      (x0 + y, y0 + x)) if(isBlack(x0 + y, y0 + x)) {setPixelColor(x0 + y, y0 + x, colori); ret=1;}
    if(inScreen
      (x0 + y, y0 - x)) if(isBlack(x0 + y, y0 - x)) {setPixelColor(x0 + y, y0 - x, colori); ret=1;}
    if(inScreen
      (x0 - y, y0 + x)) if(isBlack(x0 - y, y0 + x)) {setPixelColor(x0 - y, y0 + x, colori); ret=1;}
    if(inScreen
      (x0 - y, y0 - x)) if(isBlack(x0 - y, y0 - x)) {setPixelColor(x0 - y, y0 - x, colori); ret=1;}
    incO += 4;
    del += incO;
  }
}
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
    if(circleNOM(diag[i].x, diag[i].y, diag[i].color, radius)){
      fini = 0;
      //printf("continue grow %d\n",i);
    }
    else{
      diag[i].alive = 0;
      printf("finish my voronoi number %d \n", i);
    }

  }
  radius++;
  if(radius==50){return 1;}
  return !fini;
}

void diagInit (int nb){
  nbCells = nb;
  //Color pixelColor;
  int i, x, y;
  radius=1;
  int w =  glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  for(i=0 ; i<nb; i++){
    x = rand_a_b(1,w-1);
    y = rand_a_b(1,h-1);
    diag[i].x = x;
    diag[i].y = y;
    diag[i].color = getmyPixelColor(diag[i].x,diag[i].y);
    diag[i].alive = 1;
  }
}

void voronoi (Image *im ) {
  //OKK put pixel
/*  int j,i;
  Color colori = getmyPixelColor(1,1);
  for(i=0, j=0; i<600; i++, j++ ){
    for(j=0; j<600; j++){
      setPixelColor(i,j,colori);
    }
  }int k=0;
  */

    diagInit(SIZE);
    //set image in black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    diagGrow(SIZE);


    if(!diagGrow(SIZE)){
      printf("OOOKKK GOOO\n" );

      diagInit(SIZE);
      glClearColor(0.0, 0.0, 0.0, 0.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      diagGrow(SIZE);


    }
    /*if(diagGrow(5)){
        diagGrow(5);
      }*/

  /*  int k=0;
    diagInit(5);
    //while(k<25){
      k++;
      if(!diagGrow(5)){
        printf("yess in\n");
        diagInit(5);
        setImageBLack(im);
      }*/
    //}
}

/*

*/

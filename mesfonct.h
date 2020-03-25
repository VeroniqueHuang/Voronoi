#ifndef MAFONCT
#define MAFONCT

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>


#define SIZECOLOR 255
#define SIZE 10
#define WIDTH glutGet(GLUT_WINDOW_WIDTH)
#define HEIGHT glutGet(GLUT_WINDOW_HEIGHT)


typedef struct Color Color;
struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

typedef struct dataItem dataItem;
struct dataItem {
  int key; //numberColor
  Color color;
};
struct dataItem* hashmap[SIZECOLOR];
struct dataItem* item;
static int ** tab;

//prototype
int rand_a_b (int a, int b);
Color getmyPixelColor (int x, int y);
void setPixelColor(int x, int y, Color color);
int isBlack(int x,int y);
int inScreen(int x, int y);
int circleNOM(int x0, int y0, Color colori, int r);
int diagGrow(int nb);
void diagInit (int nb);


#endif

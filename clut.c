#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <string.h>

#include <unistd.h>
#include <math.h>
#include "ima.h"
#include "mesfonct.h"

//#include  "color_voronoi2.c"



/*
typedef struct Color Color;
struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};*/

/*
typedef struct dataItem dataItem;
struct dataItem {
  int key; //numberColor
  Color color;
};
struct dataItem* hashmap[SIZECOLOR];
struct dataItem* item;
*/

struct dataItem *search(int nb){//search color from number
  while(hashmap[nb] != NULL){
    if(hashmap[nb]->key == nb)
        return hashmap[nb];
    nb++;
  }
  return NULL;
}

struct dataItem *searchColor(Color color){//search number from color
  int i;
  for(i=0; i<SIZECOLOR; i++){
    if(hashmap[i] !=NULL && (hashmap[i]->color.r == color.r && hashmap[i]->color.g == color.g && hashmap[i]->color.b == color.b) ){
      //printf("color founnd %f %f %f number: %d\n",hashmap[i]->color.r,hashmap[i]->color.g,hashmap[i]->color.b,i);
      return hashmap[i];
    }
  }
  return NULL;
}

Color getmyPixelColor_ (int x, int y){
  Color color;
  glReadPixels(x,y,1,1,GL_RGB, GL_FLOAT, &color);
  return color;
}

void insert(int key, Color color){
  struct dataItem *item = (struct dataItem*) malloc(sizeof(struct dataItem));
  item->color = color;
  item->key = key;
  hashmap[key] = item;
}

int roundNumber(int nb){
  //int r = nb + ((5-(nb % 5)) % 5);
  //int num = nb % 10 < 6? nb - (nb % 10) : nb - (nb % 10) + 10;
  int num = nb % 42 < 21? nb - (nb % 42) : nb - (nb % 42) + 42;
  return num;
}

float roundNumberFloat(float nb){
  int numb = nb*100;
  numb = numb % 16 < 8? numb - (numb % 16) : numb - (numb % 16) + 16;
  if(numb!=0){
    float nn = (float)numb/100;
    return nn;
  }
  return numb;
}

Color roundCOlor (Color color){
  color.r = roundNumberFloat(color.r);
  color.g = roundNumberFloat(color.g);
  color.b = roundNumberFloat(color.b);
  //printf("coloredddd %f %f %f =\n",color.r,color.g,color.b);

  return color;
}

void clut (Image *im){
  Color colorFound;
  int nb=0;
//  int w =  glutGet(GLUT_WINDOW_WIDTH);
//  int h = glutGet(GLUT_WINDOW_HEIGHT);
   **tab = malloc( (WIDTH*HEIGHT) * sizeof( int ));

   printf("okkkkkkkkkkk \n");
  for (int i=0; i<WIDTH; i++){
    tab[i] = (int *)malloc(WIDTH * sizeof(int));
  }

  for (int i=0; i<WIDTH; i++){
    for (int j=0; j<HEIGHT; j++){
      //printf("ij : %d %d\n",i,j);
      colorFound = getmyPixelColor_(i,j);
      colorFound = roundCOlor(colorFound);
      if(searchColor(colorFound) == NULL){//if the color don't exist in the hashmap
        printf("in %d\n",i);
        insert(nb,colorFound);
        tab[i][j] = nb;
        nb++;
      }
      else{
        //printf("jai trouve %f %f %f \n", colorFound.r,colorFound.g,colorFound.b);
        tab[i][j] = searchColor(colorFound)->key;
      }
    }
  }

/*  for(int i=0; i<SIZECOLOR; i++){
    if(hashmap[i]!=NULL){
      printf("%d ",hashmap[i]->key);
    }
    else{
      printf("nop%d ",i);
    }
  }*/


  return;
}

/*
void ma(Image * img){
 Color c;
  c.r = 0.1;
  c.g = 0.1;
  c.b = 0.1;

  Color k;
  k.r = 0.2;
  k.g = 0.2;
  k.b = 0.2;

  Color d;
  d.r = 0.3;
  d.g = 0.3;
  d.b = 0.3;
//-------------
  insert(1,c);
  insert(2,k);
  insert(3,d);

  item = searchColor(d);


   if(item != NULL) {
      printf("Element found: %d color \n", item->key);
   } else {
      printf("Element not found pas de color\n");
   }


   item = search(2);
   if(item != NULL) {
      printf("Element found: %f\n", item->color.r);
   } else {
      printf("Element not found\n");
   }

   roundNumber(64);


  return;
}
*/

/* il s agit de prendre une image et de la modifier */

#include "ima.h"
#include <limits.h>

void gris_uniforme(Image * i) {
  int j, size;
  GLubyte * im, val;
  val = 128;
  size = 3 * i->sizeY * i->sizeX;
  im = i->data;
  for (j = 0; j < size; j ++) {
	*im++ = val;
  }
}


/*
void gris_uniforme(Image * img) {
  int b, c, rgb_comp_color, size, sizex, sizey;
  GLubyte tmp, * ptrdeb, *ptrfin, *lastline;
--*/

/*
  int j, size;
  GLubyte * im, val;
  val = 128;
  size = 3 * i->sizeY * i->sizeX;
  im = i->data;
  for (j = 0; j < size; j ++) {
	*im++ = val;
}*/
/*
size = img->sizeX * img->sizeY * 3;
sizex = img->sizeX;
sizey = img->sizeY;
lastline = img->data + size - sizex * 3;

  for (b = 0; b < img->sizeY / 2; b++) {
    ptrdeb = img->data + b * sizex * 3;
	  ptrfin = lastline - (b * sizex * 3);
    for (c = 0; c < 3 * sizex; c++) {
     tmp = *ptrdeb;
     *ptrdeb = *ptrfin;
     *ptrfin = tmp;
     ptrfin++;
     ptrdeb++;
   }
 }

}
--*/

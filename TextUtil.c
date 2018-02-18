
#include <stdio.h>

#include "TextUtil.h"

void RenderText( char text[], int x, int y ){

  glRasterPos2i( x, y );

  for( int i = 0; text[i] != '\0'; i++ ){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
  }

}

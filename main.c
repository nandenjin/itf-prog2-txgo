
#include <stdio.h>
#include "GL/glut.h"

#define g_WindowWidth 900
#define g_WindowHeight 300

void init( void ){


}


void display( void ){


}

void onKeyboard( unsigned char key, int x, int y ){

	printf( "%c\n", key );	
	
}

void onSpecialKey( int key, int x, int y ){

	printf( "%d\n", key );	
	
}

int main( int argc, char *argv[] ){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize( g_WindowWidth, g_WindowHeight );
  glutCreateWindow( "TXGO" );
 
  glutDisplayFunc( display );
  //glutIdleFunc(idle);
  
  glutKeyboardFunc( onKeyboard );
  glutSpecialFunc( onSpecialKey );
  //glutMouseFunc(mouse);
  //glutReshapeFunc(reshape);
 
  init();
 
  glutMainLoop();
 
  return 0;
  
}




#include <stdio.h>
#include "GL/glut.h"

#include "ImageUtil.h"

#include "main.h"

// テクスチャ画像
Texture train, rail, tunnel;

void init( void ){
	
	// CLI起動ロゴ
	printf( "  _______  ____________ \n /_  __/ |/ / ____/ __ \\\n  / /  |   / / __/ / / /\n / /  /   / /_/ / /_/ / \n/_/  /_/|_\\____/\\____/  \n                        \n" );
	
	// クリアカラーの設定
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	
	// 座標系の設定 
	glOrtho( 0, WIN_WIDTH, WIN_HEIGHT, 0, -1, 1 );
	
	// テクスチャ画像のロード
	GetTextureByPNGImage( &tunnel, "./assets/tunnel.png" );
	GetTextureByPNGImage( &train, "./assets/train.png" );
	GetTextureByPNGImage( &rail, "./assets/rail.png" );

}


void display( void ){
	
	glClear(GL_COLOR_BUFFER_BIT);
	DrawTexture( &tunnel, 0, 0, BG_WIDTH, BG_HEIGHT );
	DrawTexture( &rail, 0, 0, BG_WIDTH, BG_HEIGHT );
	DrawTexture( &train, 0, RAIL_Y - TRAIN_HEIGHT, TRAIN_WIDTH, TRAIN_HEIGHT );
	glutSwapBuffers();
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
  glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
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



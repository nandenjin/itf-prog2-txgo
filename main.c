
#include <stdio.h>
#include "GL/glut.h"

#include "ImageUtil.h"
#include "Track.h"

#include "main.h"

// テクスチャ画像
Texture train, rail, scenes[2];

// 走行位置
int trainPosition = 0;

void init( void ){
	
	// CLI起動ロゴ
	printf( "  _______  ____________ \n /_  __/ |/ / ____/ __ \\\n  / /  |   / / __/ / / /\n / /  /   / /_/ / /_/ / \n/_/  /_/|_\\____/\\____/  \n                        \n" );
	
	// クリアカラーの設定
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	
	// 座標系の設定 
	glOrtho( 0, WIN_WIDTH, WIN_HEIGHT, 0, -1, 1 );
	
	// テクスチャ画像のロード
	GetTextureByPNGImage( &scenes[0], "./assets/tunnel.png" );
	GetTextureByPNGImage( &scenes[1], "./assets/station.png" );
	GetTextureByPNGImage( &train, "./assets/train.png" );
	GetTextureByPNGImage( &rail, "./assets/rail.png" );
	
	// 路線の初期化
	initTrack();

}


void display( void ){
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	int posOnPx = trainPosition * MP_UNIT;
	int posOfRE = trainPosition - ( WIN_WIDTH - TRAIN_HEAD_X ) / MP_UNIT;
  int ib = getSceneIndexByPosition( posOfRE );
  int pb = WIN_WIDTH + ( posOfRE - track.scenes[ib].beginAt ) * MP_UNIT % BG_WIDTH;
  
  while( 0 < pb ){
    int i = getSceneIndexByPosition( ( WIN_WIDTH - pb ) / MP_UNIT + posOfRE );
    if( i != ib ){
      pb = WIN_WIDTH - ( track.scenes[i].beginAt - posOfRE ) * MP_UNIT;
      ib = i;
    }
    int type = track.scenes[i].type;
    if( pb - BG_WIDTH < WIN_WIDTH ) DrawTexture( &scenes[type], pb - BG_WIDTH, 0, BG_WIDTH, BG_HEIGHT );
    pb -= BG_WIDTH;
  }
	
	// 軌道の描画
	int pr = TRAIN_HEAD_X + ( WIN_WIDTH - TRAIN_HEAD_X ) % BG_WIDTH + posOnPx % BG_WIDTH;
	
	while( -BG_WIDTH < pr ){
		if( pr < BG_WIDTH ) DrawTexture( &rail, pr, 0, BG_WIDTH, BG_HEIGHT );
		pr -= BG_WIDTH;
	}
	
	// 車両の描画
	DrawTexture( &train, TRAIN_HEAD_X, RAIL_Y - TRAIN_HEIGHT, TRAIN_WIDTH, TRAIN_HEIGHT );
	
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



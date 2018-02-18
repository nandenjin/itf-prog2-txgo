
#include <stdio.h>
#include <stdlib.h>
#include "GL/glut.h"

// タイマーライブラリ
#include "GenericTimer.h"

#include "main.h"
#include "drive.h"
#include "Track.h"
#include "ImageUtil.h"
#include "TextUtil.h"

// 走行位置
double trainPosition = 0;

// 走行速度（km/h）
double trainSpeed = 0;

// 描画インターバル時刻の記録
int lastIdleTime = 0;

// 運行ステータス
int state = 0;

// 発車時刻
double departureTime = 0;

// セクション
int sectionIndex = 0;

Texture msg[2];

void init( void ){
	
	// CLI起動ロゴ
	printf( "  _______  ____________ \n /_  __/ |/ / ____/ __ \\\n  / /  |   / / __/ / / /\n / /  /   / /_/ / /_/ / \n/_/  /_/|_\\____/\\____/  \n                        \n" );
	
	// クリアカラーの設定
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	
	// 座標系の設定 
	glOrtho( 0, WIN_WIDTH, WIN_HEIGHT, 0, -1, 1 );

	// 路線の初期化
	initTrack();
	loadTrackAssets();

  // 運転操作系の初期化
  loadControlsAssets();
	
	// タイマー開始
	StartTimer();
	
	// 描画インターバル時刻の初期値
	lastIdleTime = GetTime();

  // 初期発車時刻
  departureTime = GetTime() + 10000;

  GetTextureByPNGImage( &msg[0], "./assets/msg/msg_time-left.png" );
  GetTextureByPNGImage( &msg[1], "./assets/msg/msg_cannot-stop-here.png" );

}


void display( void ){
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 軌道と車両の描画
	renderTrack( trainPosition, WIN_WIDTH, TRAIN_HEAD_X, MP_UNIT );

  // 操作系の描画
  renderControls();
  if( state == 0 ){

    DrawTexture( &msg[0], MSG_X + 150, 150, MSG_WIDTH, MSG_HEIGHT );
    char leftTimeStr[10];
    sprintf( leftTimeStr, "%2.0lf", ( departureTime - GetTime() ) / 1000 );
    RenderText( leftTimeStr, MSG_X + 160, 200 );

  }else if( state == 1 ){

    renderMeters( trainSpeed, getSectionByIndex( sectionIndex ) - trainPosition );
    DrawTexture( &msg[1], MSG_X, MSG_Y, MSG_WIDTH, MSG_HEIGHT );

  }
	
	glutSwapBuffers();
}


void idle( void ){

  double now = GetTime();

  if( state == 0 ){

    if( departureTime < now ) state = 1;

  }else if( state == 1 ){

  }
	
	double t = GetRapTime( lastIdleTime );
	
	if( t > 100 ){

		tickDrive( t, &trainSpeed, &trainPosition );
		lastIdleTime = now;
		
	}

	display();

}


void onKeyboard( unsigned char key, int x, int y ){

	printf( "%c\n", key );

  if( key == 'q' ) exit( 0 );
	
}


void onSpecialKey( int key, int x, int y ){

	if( key == GLUT_KEY_DOWN ){

    stepDrive( 1 );

  }else if( key == GLUT_KEY_UP ){

    stepDrive( -1 );

  }
	
}


int main( int argc, char *argv[] ){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize( WIN_WIDTH, WIN_HEIGHT );
  glutCreateWindow( "TXGO" );
 
  glutDisplayFunc( display );
  glutIdleFunc( idle );
  
  glutKeyboardFunc( onKeyboard );
  glutSpecialFunc( onSpecialKey );
  //glutMouseFunc(mouse);
  //glutReshapeFunc(reshape);
 
  init();
 
  glutMainLoop();
 
  return 0;
  
}



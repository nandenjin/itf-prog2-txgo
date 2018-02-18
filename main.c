
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GL/glut.h"

// タイマーライブラリ
#include "GenericTimer.h"

#include "main.h"
#include "drive.h"
#include "Track.h"
#include "map.h"
#include "Ranking.h"
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

// 起点出発時刻
double startTime = 0;

// 発車時刻
double departureTime = 0;

// スコアタイム
int scoreTime = 0;

// セクション
int sectionIndex = 0;

// 名前入力
char rankingName[20];

Texture msg[2], cover[5];

// キー入力ハンドラ
void ( *onKeyHandler )( void ) = NULL;

void startGame( void );
void toGameOP( void );
void joinRanking( void );
void writeRanking( void );

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

  // マップ表示初期化
  InitMap();
	
	// タイマー開始
	StartTimer();
	
	// 描画インターバル時刻の初期値
	lastIdleTime = GetTime();

  GetTextureByPNGImage( &msg[0], MSG_TIME_LEFT );
  GetTextureByPNGImage( &msg[1], MSG_CANNOT_STOP_HERE );

  GetTextureByPNGImage( &cover[0], COVER_OP );
  GetTextureByPNGImage( &cover[1], COVER_OVER );
  GetTextureByPNGImage( &cover[2], COVER_END );
  GetTextureByPNGImage( &cover[3], COVER_NAME_INPUT );
  GetTextureByPNGImage( &cover[4], COVER_RANKING );

  toGameOP();

}


void display( void ){

  double now = GetTime();
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 軌道と車両の描画
	renderTrack( trainPosition, WIN_WIDTH, TRAIN_HEAD_X, MP_UNIT );

  // 操作系の描画
  renderControls();
  if( state == 0 ){

    DrawTexture( &msg[0], MSG_X + 150, 150, MSG_WIDTH, MSG_HEIGHT );
    char leftTimeStr[10];
    sprintf( leftTimeStr, "%2.0lf", ( departureTime - now ) / 1000 );
    RenderText( leftTimeStr, MSG_X + 160, 200 );

    renderTime( (int)( now - startTime ) / 1000 );

  }else if( state == 1 ){

    double distanceLeft = getSectionByIndex( sectionIndex ) - trainPosition;
    renderMeters( trainSpeed, distanceLeft );
    renderTime( (int)( now - startTime ) / 1000 );

    if( distanceLeft < 30 && distanceLeft >= 2 && trainSpeed == 0 ){

      DrawTexture( &msg[1], MSG_X, MSG_Y, MSG_WIDTH, MSG_HEIGHT );

    }

  // オープニング画面
  }else if( state == 2 ){

    DrawTexture( &cover[0], 0, 0, WIN_WIDTH, WIN_HEIGHT );

  // ゲームオーバー
  }else if( state == 3 ){

    DrawTexture( &cover[1], 0, 0, WIN_WIDTH, WIN_HEIGHT );

  // 終了画面
  }else if( state == 4 ){

    char timeChar[20];
    sprintf( timeChar, "%2d:%02d", scoreTime / 60, scoreTime % 60 );

    DrawTexture( &cover[2], 0, 0, WIN_WIDTH, WIN_HEIGHT );
    RenderText( timeChar, 440, 200 );

    if( isRankedIn( scoreTime ) == 1 ){

      onKeyHandler = joinRanking;

    }else{

      onKeyHandler = toGameOP;

    }

  // 名前入力
  }else if( state == 5 ){

    DrawTexture( &cover[3], 0, 0, WIN_WIDTH, WIN_HEIGHT );
    RenderText( rankingName, 430, 200 );

  // ランキング表示
  }else if( state == 6 ){

    DrawTexture( &cover[4], 0, 0, WIN_WIDTH, WIN_HEIGHT );
    renderRanking();
    onKeyHandler = toGameOP;

  }

  RenderMap( state, sectionIndex, trainPosition );
	
	glutSwapBuffers();
}


void idle( void ){

  double now = GetTime();
  double distanceLeft = getSectionByIndex( sectionIndex ) - trainPosition;
  Track track = getTrack();

  if( state == 0 ){

    if( departureTime < now ) state = 1;

  }else if( state == 1 ){

    if( distanceLeft < -2 ){

      printf( "== GAME OVER ==\n" );
      state = 3;
      onKeyHandler = toGameOP;

    }

    if( trainSpeed == 0 ){

      if( distanceLeft < 2 ){

        state = 0;
        departureTime = now + 20000;
        sectionIndex++;

        if( sectionIndex >= track.sectionNum ){

          state = 4;
          scoreTime = (int)( GetTime() - startTime ) / 1000;

        }

      }

    }

  }
	
	double t = GetRapTime( lastIdleTime );
	
	if( t > 100 ){

		tickDrive( t, &trainSpeed, &trainPosition );
		lastIdleTime = now;
		
	}

	display();

}

void startGame( void ){

  state = 0;

  // 初期発車時刻
  departureTime = GetTime() + 10000;
  startTime = GetTime();

  trainPosition = 0;
  trainSpeed = 0;

  sectionIndex = 0;

  resetDrive();

}

void toGameOP( void ){

  state = 2;
  onKeyHandler = startGame;

}

void joinRanking( void ){

  state = 5;
  rankingName[0] = '\0';

}

void writeRanking( void ){

  joinToRanking( rankingName, scoreTime );
  state = 6;

}

void onKeyboard( unsigned char key, int x, int y ){

	if( onKeyHandler != NULL ){

    void (*k)(void) = onKeyHandler;
    onKeyHandler = NULL;
    k();

  }else if( state == 5 ){


    // Enter
    if( (int)key == 13 ){

      writeRanking();

    // Backspace
    }else if( (int)key == 127 ){

      if( strlen( rankingName ) > 0 ){

        rankingName[ strlen( rankingName ) - 1 ] = '\0';

      }

    }else if( strlen( rankingName ) < 19 ){

      int len = strlen( rankingName );
      rankingName[ len ] = key;
      rankingName[ len + 1 ] = '\0';

    }

  }else{

    if( key == 'q' ) exit( 0 );

  }
	
}


void onSpecialKey( int key, int x, int y ){

  if( onKeyHandler != NULL ){

    void (*k)(void) = onKeyHandler;
    onKeyHandler = NULL;
    k();

  }else if( state == 5 ){



  }else{

    int locked;
    if( state == 1 ) locked = 0;
    else locked = 1;

  	if( key == GLUT_KEY_DOWN ){

      stepDrive( 1, locked );

    }else if( key == GLUT_KEY_UP ){

      stepDrive( -1, locked );

    }
  
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



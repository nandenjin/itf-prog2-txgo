
#include <stdlib.h>
#include "GL/glut.h"

#include "Track.h"
#include "ImageUtil.h"

Track track;

// テクスチャ画像
Texture trainTex, railTex, bgTexs[2];

void initTrack( void ){

	track.sceneNum = 4;
	track.scenes = ( Scene * )malloc( sizeof( Scene ) * track.sceneNum );
	
	if( track.scenes == NULL ) exit( EXIT_FAILURE );

	track.scenes[0].beginAt = -120;
	track.scenes[0].type = 1;

	track.scenes[1].beginAt = 5;
	track.scenes[1].type = 0;

	track.scenes[2].beginAt = 500;
	track.scenes[2].type = 1;

	track.scenes[3].beginAt = 800;
	track.scenes[3].type = 0;

	track.sectionNum = 1;
	track.sections = ( int * )malloc( sizeof( int ) * track.sectionNum );
	
	if( track.sections == NULL ) exit( EXIT_FAILURE );

	track.sections[0] = 0;

}

void loadTrackAssets( void ){
	
	// テクスチャ画像のロード
	GetTextureByPNGImage( &bgTexs[0], BG_TUNNEL_TEXTURE );
	GetTextureByPNGImage( &bgTexs[1], BG_STATION_TEXTURE );
	GetTextureByPNGImage( &trainTex, TRAIN_TEXTURE );
	GetTextureByPNGImage( &railTex, RAIL_TEXTURE );

}

int getSceneIndexByPosition( int pos ){
	
	for( int i = 0; i < track.sceneNum; i++ ){
	
		if( track.scenes[i].beginAt >= pos ) return i - 1;
	
	}
	
	return -1;

}

int isSceneExists( int pos ){
	
	if( pos < 0 || track.sceneNum <= pos ) return 0;
	else return 1;

}

void renderTrack( double trainPosition, int width, int train_x, int mp_unit ){
	
	// シーン背景の描画
	int posOfRE = trainPosition * mp_unit - ( width - train_x );
  int ib = -1;
  int pb = width;
  printf("%d / ", posOfRE );
  
  while( -BG_WIDTH < pb ){
    int i = getSceneIndexByPosition( ( ( width - pb ) + posOfRE ) / mp_unit );
    if( i < 0 ) break;
    if( i != ib ){
    	int d = track.scenes[i].beginAt * mp_unit - posOfRE;
      if( d > -BG_WIDTH ) pb = width - d;
      else pb = width + ( -d ) % BG_WIDTH;
      ib = i;
    }
    int type = track.scenes[i].type;
  	
    if( pb - BG_WIDTH >= -BG_WIDTH ){
    	DrawTexture( &bgTexs[type], pb - BG_WIDTH, 0, BG_WIDTH, BG_HEIGHT );
    	printf( "%d + %d ", pb - BG_WIDTH, i );
    }
    pb -= BG_WIDTH;
  }
  printf( "\n" );
	
	// 軌道の描画
	int pr = width + posOfRE % RAIL_WIDTH + RAIL_WIDTH;
	
	while( 0 < pr ){
		DrawTexture( &railTex, pr - RAIL_WIDTH, 0, RAIL_WIDTH, RAIL_HEIGHT );
		pr -= RAIL_WIDTH;
	}
	
	// 車両の描画
	DrawTexture( &trainTex, train_x, RAIL_Y - TRAIN_HEIGHT, TRAIN_WIDTH, TRAIN_HEIGHT );
	
}








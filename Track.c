
#include <stdlib.h>
#include "GL/glut.h"

#include "Track.h"
#include "ImageUtil.h"

Track track;

// テクスチャ画像
Texture trainTex, railTex, bgTexs[2];

void initTrack( void ){

	track.sceneNum = 3;
	track.scenes = ( Scene * )malloc( sizeof( Scene ) * track.sceneNum );
	
	if( track.scenes == NULL ) exit( EXIT_FAILURE );

	track.scenes[0].beginAt = -120;
	track.scenes[0].type = 1;

	track.scenes[1].beginAt = 5;
	track.scenes[1].type = 0;

	track.scenes[2].beginAt = 1000;
	track.scenes[2].type = 1;

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
	
		if( ( track.scenes[i].beginAt ) > pos ) return i - 1;
	
	}
	
	return -1;

}

int isSceneExists( int pos ){
	
	if( pos < 0 || track.sceneNum <= pos ) return 0;
	else return 1;

}

void renderTrack( int trainPosition, int width, int train_x, int mp_unit ){
	
	// シーン背景の描画
	int posOfRE = trainPosition - ( width - train_x ) / mp_unit;
  int ib = getSceneIndexByPosition( posOfRE );
  int pb = width + ( posOfRE - track.scenes[ib].beginAt ) * mp_unit % BG_WIDTH;
  
  while( 0 < pb ){
    int i = getSceneIndexByPosition( ( width - pb ) / mp_unit + posOfRE );
    if( i != ib ){
      pb = width - ( track.scenes[i].beginAt - posOfRE ) * mp_unit;
      ib = i;
    }
    int type = track.scenes[i].type;
    if( pb - BG_WIDTH < width ) DrawTexture( &bgTexs[type], pb - BG_WIDTH, 0, BG_WIDTH, BG_HEIGHT );
    pb -= BG_WIDTH;
  }
	
	// 軌道の描画
	int posOnPx = trainPosition * mp_unit;
	int pr = train_x + ( width - train_x ) % RAIL_WIDTH + posOnPx % RAIL_WIDTH;
	
	while( -RAIL_WIDTH < pr ){
		if( pr < RAIL_WIDTH ) DrawTexture( &railTex, pr, 0, RAIL_WIDTH, RAIL_HEIGHT );
		pr -= RAIL_WIDTH;
	}
	
	// 車両の描画
	DrawTexture( &trainTex, train_x, RAIL_Y - TRAIN_HEIGHT, TRAIN_WIDTH, TRAIN_HEIGHT );
	
}








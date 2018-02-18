
#include "map.h"

Texture line[2][2];
Texture station[3];

void InitMap( void ){

  GetTextureByPNGImage( &line[0][0], MAP_LINE0 );
  GetTextureByPNGImage( &line[0][1], MAP_LINE1 );
  GetTextureByPNGImage( &line[1][0], MAP_LINE2 );
  GetTextureByPNGImage( &line[1][1], MAP_LINE3 );
  GetTextureByPNGImage( &station[0], MAP_STA0 );
  GetTextureByPNGImage( &station[1], MAP_STA1 );
  GetTextureByPNGImage( &station[2], MAP_STA2 );

}

void RenderMap( int state, int sectionIndex, double position ){

  Track track = getTrack();
  int section = track.sections[ sectionIndex ];

  if( state == 0 ){

    DrawTexture( &station[ sectionIndex ], MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT );

  }else if( state == 1 ){

    if( section - position > 150 ){

      int x = (int) GetTime() / 1000 % 2;
      DrawTexture( &line[ sectionIndex ][ x ], MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT );

    }else{

      DrawTexture( &station[ sectionIndex + 1 ], MAP_X, MAP_Y, MAP_WIDTH, MAP_HEIGHT );

    }

  }

}

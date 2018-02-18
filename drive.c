
#include <stdio.h>
#include "GL/glut.h"

#include "drive.h"
#include "ImageUtil.h"
#include "TextUtil.h"

int notch = 0;
double accel[] = {
  -0.03,  // EB
  -0.025, // B7
  -0.02,
  -0.015,
  -0.01,
  -0.005,
  -0.003,
  -0.002,
  -0.001, // N
  0.005,  // M1
  0.01,
  0.015,
  0.02    // M4
};

Texture lvTex[13];

void tickDrive( double time, double *speed, double *position ){
	
	double a;

  if( notch <= 9 ){
    a = *speed * accel[ notch ] * 10;
    if( a > -0.4 ) a = -0.4;
  }else{
    a = ( MAX_SPEED - *speed ) * accel[ notch ];
	  if( a < 0.2 ) a = 0.2;
  }

	*speed += a * ( time / 1000 );
  if( *speed < 0.5 && notch <= 9 ) *speed = 0;

	*position += *speed * 1000 * ( time / 60 / 60 / 1000 );

}

void stepDrive( int w ){

  notch += w;

  if( notch >= 13 ) notch = 12;
  else if( notch < 0 ) notch = 0;

}

void loadControlsAssets( void ){

  GetTextureByPNGImage( &lvTex[0], CTRL_LV_TEXTURE_EB );

  for( int i = 0; i < 7; i++ ){

    char x[30];
    sprintf( x, CTRL_LV_TEXTURE_B_FORMAT, 7 - i );
    GetTextureByPNGImage( &lvTex[ i + 1 ], x );

  }

  GetTextureByPNGImage( &lvTex[ 1 + 7 ], CTRL_LV_TEXTURE_N );

  for( int i = 0; i < 4; i++ ){

    char x[30];
    sprintf( x, CTRL_LV_TEXTURE_M_FORMAT, i + 1 );
    GetTextureByPNGImage( &lvTex[ i + 1 + 7 + 1 ], x );

  }

}

void renderControls( void ){

	DrawTexture( &lvTex[ notch ],
    CTRL_LV_TEXTURE_LEFT,
    CTRL_LV_TEXTURE_TOP,
    CTRL_LV_TEXTURE_WIDTH,
    CTRL_LV_TEXTURE_HEIGHT
  );

}

void renderMeters( double speed, double position ){

  char speedChar[20];
  sprintf( speedChar, "%3.0lf km/h", speed );

  RenderText(
    speedChar,
    CTRL_LV_TEXTURE_LEFT - CTRL_LV_TEXTURE_WIDTH - 70,
    CTRL_LV_TEXTURE_TOP  + 50
  );

  char positionChar[20];
  sprintf( positionChar, "%4.0lf m", position );

  RenderText(
    positionChar,
    CTRL_LV_TEXTURE_LEFT - CTRL_LV_TEXTURE_WIDTH - 70 ,
    CTRL_LV_TEXTURE_TOP  + 75
  );

}

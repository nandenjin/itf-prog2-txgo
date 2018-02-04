
#include "GL/glut.h"

#include "drive.h"
#include "ImageUtil.h"

int notch = -5;

void tickDrive( double time, double *speed, double *position ){
	
	double accel = ( MAX_SPEED - *speed ) * 0.02;
	
	// ToDo: 加速度下限リミッター設置
	
	*speed += accel * ( time / 1000 );
	*position += *speed * 1000 * ( time / 60 / 60 / 1000 );

}

void renderControls( void ){

	

}


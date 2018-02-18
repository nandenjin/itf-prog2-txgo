
#ifndef __MAP__
#define __MAP__

#include <stdio.h>
#include "ImageUtil.h"
#include "Track.h"
#include "GenericTimer.h"

#define MAP_X 15
#define MAP_Y 155
#define MAP_WIDTH 400
#define MAP_HEIGHT 120

#define MAP_LINE0 "./assets/map/map_line-0.png"
#define MAP_LINE1 "./assets/map/map_line-1.png"
#define MAP_LINE2 "./assets/map/map_line-2.png"
#define MAP_LINE3 "./assets/map/map_line-3.png"
#define MAP_LINE4 "./assets/map/map_line-4.png"

#define MAP_STA0 "./assets/map/map_station-0.png"
#define MAP_STA1 "./assets/map/map_station-1.png"
#define MAP_STA2 "./assets/map/map_station-2.png"

void InitMap( void );
void RenderMap( int state, int sectionIndex, double position );

#endif

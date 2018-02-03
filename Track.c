
#include <stdlib.h>

#include "Track.h"

Track track;

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








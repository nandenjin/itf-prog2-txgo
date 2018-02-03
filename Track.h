
typedef struct {
	
	int beginAt;
	int length;
	int type;

} Scene;

typedef struct {
	
	int beginAt;
	int sectionNum;
	int *sections;
	int sceneNum;
	Scene *scenes;
	
} Track;

extern Track track;

void initTrack( void );
int getSceneIndexByPosition( int pos );
int isSceneExists( int pos );

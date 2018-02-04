
// 車両画像
#define TRAIN_TEXTURE "./assets/train.png"

// 車両画像サイズ
#define TRAIN_WIDTH 618
#define TRAIN_HEIGHT 73

// シーン背景画像
#define BG_TUNNEL_TEXTURE "./assets/tunnel.png"
#define BG_STATION_TEXTURE "./assets/station.png"

// シーン背景画像サイズ
#define BG_WIDTH 626
#define BG_HEIGHT 143

// レール画像
#define RAIL_TEXTURE "./assets/rail.png"

// レール画像サイズ
#define RAIL_WIDTH 626
#define RAIL_HEIGHT 143

// レール面のY座標
#define RAIL_Y 109

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
void loadTrackAssets( void );
int getSceneIndexByPosition( int pos );
int isSceneExists( int pos );
void renderTrack( double trainPosition, int width, int train_x, int mp_unit );



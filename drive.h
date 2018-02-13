
#define MAX_SPEED 130

#define CTRL_LV_TEXTURE_B_FORMAT "./assets/lv/ui_ctrl-lv_B%d.png"
#define CTRL_LV_TEXTURE_M_FORMAT "./assets/lv/ui_ctrl-lv_M%d.png"
#define CTRL_LV_TEXTURE_EB "./assets/lv/ui_ctrl-lv_EB.png"
#define CTRL_LV_TEXTURE_N "./assets/lv/ui_ctrl-lv_N.png"

#define CTRL_LV_TEXTURE_TOP 150
#define CTRL_LV_TEXTURE_LEFT 830
#define CTRL_LV_TEXTURE_WIDTH 60
#define CTRL_LV_TEXTURE_HEIGHT 150

void tickDrive( double time, double *speed, double *position );
void stepDrive( int w );
void loadControlsAssets( void );
void renderControls( void );

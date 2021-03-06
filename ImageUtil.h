
#ifndef __IMGUT__
#define __IMGUT__

#include "GL/glut.h"
#include "glpng/glpng.h"

typedef struct {
	
	pngInfo info;
	GLuint obj;

} Texture;

void GetTextureByPNGImage( Texture *tex, char *filename );
void DrawTexture( Texture *tex, int x, int y, int w, int h );


#endif

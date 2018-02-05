
#include "GL/glut.h"
#include <glpng/glpng.h>

#include "ImageUtil.h"

#define glError() { \
	GLenum err = glGetError(); \
	while (err != GL_NO_ERROR) { \
		fprintf(stderr, "glError: %s caught at %s:%u\n", (char *)gluErrorString(err), __FILE__, __LINE__); \
		err = glGetError(); \
	} \
}


void GetTextureByPNGImage( Texture *tex, char *filename ){
	
	
	tex->obj = pngBind( filename, PNG_NOMIPMAP, PNG_ALPHA, &(tex->info), GL_CLAMP, GL_NEAREST, GL_NEAREST );

}



void DrawTexture( Texture *tex, int x, int y, int w, int h ){

	glError();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	
	glBindTexture( GL_TEXTURE_2D, tex->obj );
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2i(x,   y);
	glTexCoord2f(1, 0); glVertex2i(x+w, y);
	glTexCoord2f(1, 1); glVertex2i(x+w, y+h);
	glTexCoord2f(0, 1); glVertex2i(x,   y+h);
	glEnd();
		
	glBindTexture( GL_TEXTURE_2D, 0 );
		
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glError();
	
}



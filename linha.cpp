#include "linha.h"
#include <GL/gl.h>

void Linha::render()
{
	glBegin( GL_LINES );
    glColor3f( r, g, b );
    glVertex2i( p1.getX(), p1.getY() );
    glVertex2i( p2.getX(), p2.getY() );
    glEnd();
}

Linha::Linha(int x1, int y1, int x2, int y2, float r, float g, float b): 
	p1(x1, y1), p2(x2, y2)
{
	setColor(r, g, b);
}

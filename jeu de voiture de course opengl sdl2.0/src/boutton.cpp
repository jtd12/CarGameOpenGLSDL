#include"boutton.hpp"

boutton::boutton(int minX,int maxX,int minY,int maxY)
{
this->minX=minX;
this->minY=minY;
this->maxX=maxX;
this->maxY=maxY;
	
}

boutton::~boutton()
{
		
}


void boutton::set2D(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0); // origine en haut à gauche
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void boutton::unset2D() {
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
		
void boutton::drawButton(int x, int y, int w, int h, bool hovered) {
    if (hovered) glColor3f(0.0f, 1.0f, 0.0f); // vert si survolé
    else glColor3f(0.0f, 0.0f, 1.0f);         // bleu sinon

    glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + w, y);
        glVertex2i(x + w, y + h);
        glVertex2i(x, y + h);
    glEnd();
}

int boutton::getMinX(){
	return minX;
}
int boutton::getMinY()
		{
			return minY;
		}
int boutton::getMaxX()
		{
			return maxX;
		}
int boutton::getMaxY()
		{
			return maxY;
		}

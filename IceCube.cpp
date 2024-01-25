#include "IceCube.h"
#include "Glut.h"

double IceCube::height = 1.0;
double IceCube::width = 1.0;
double IceCube::startingX = 0.5;
double IceCube::startingY = 1.25;
double IceCube::speed = 0.5;
unsigned int IceCube::textureDiamond = 0;
unsigned int IceCube::texture = 0;
int IceCube::ID = 0;

IceCube::IceCube(int row, int col, bool diamond) {
	this->row = row;
	this->col = col;
	this->diamond = diamond;
	this->id = ++IceCube::ID;
}

unsigned int IceCube::pickTexture()
{
	if (diamond) return textureDiamond;
	return texture;
}

double IceCube::getX() {
	double posX = startingX + col;
	switch (orientation) {
	case 1:
		posX -= shift;
		break;
	case 3:
		posX += shift;
		break;
	}
	return posX;
}

double IceCube::getY() {
	double posY = startingY + row;
	switch (orientation) {
	case 2:
		posY -= shift;
		break;
	case 4:
		posY += shift;
		break;
	}
	return posY;
}

void IceCube::draw() {

	//position of the block
	double posX = getX();
	double posY = getY();

	//draw block
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pickTexture());

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(posX, posY);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(posX + width, posY);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(posX + width, posY + height);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(posX, posY + height);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
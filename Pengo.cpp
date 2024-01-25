#include "Pengo.h"
#include "Glut.h"

double Pengo::height = 1.0;
double Pengo::width = 1.0;
double Pengo::startingX = 0.5;
double Pengo::startingY = 1.25;
double Pengo::speed = 0.2;


unsigned int Pengo::pengoLeft1 = 0, Pengo::pengoLeft2 = 0, Pengo::pengoRight1 = 0, Pengo::pengoRight2 = 0;
unsigned int Pengo::pengoUp1 = 0, Pengo::pengoUp2 = 0, Pengo::pengoDown1 = 0, Pengo::pengoDown2 = 0;
unsigned int Pengo::pengoDead = 0;


unsigned int Pengo::texture() {
	if (dead) 
		return pengoDead;
	
	switch (orientation) {
	case 1:
		if (changeStep)
			return pengoLeft1;
		return pengoLeft2;
	case 2:
		if (changeStep)
			return pengoDown1;
		return pengoDown2;
	case 3:
		if (changeStep)
			return pengoRight1;
		return pengoRight2;
	case 4:
		if (changeStep)
			return pengoUp1;
		return pengoUp2;
	default:
		return pengoDown1;
	}
}


Pengo::Pengo() {
	this->row = 8;
	this->col = 6;
}
Pengo::Pengo(int row, int col) {
	this->row = row;
	this->col = col;
}

double Pengo::getX() {
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

double Pengo::getY() {
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

void Pengo::draw() {
	double posX = getX();
	double posY = getY();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture());
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
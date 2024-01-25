#include "SnooBee.h"
#include "Glut.h"



int SnooBee::ID = 0;
double SnooBee::height = 1.0;
double SnooBee::width = 1.0;
double SnooBee::startingX = 0.5;
double SnooBee::startingY = 1.25;
unsigned int SnooBee::yellowDown1 = 0, SnooBee::yellowDown2 = 0, SnooBee::yellowUp1 = 0, SnooBee::yellowUp2 = 0;
unsigned int SnooBee::yellowLeft1 = 0, SnooBee::yellowLeft2 = 0, SnooBee::yellowRight1 = 0, SnooBee::yellowRight2 = 0;
unsigned int SnooBee::greenDown1 = 0, SnooBee::greenDown2 = 0, SnooBee::greenUp1 = 0, SnooBee::greenUp2 = 0;
unsigned int SnooBee::greenLeft1 = 0, SnooBee::greenLeft2 = 0, SnooBee::greenRight1 = 0, SnooBee::greenRight2 = 0;


SnooBee::SnooBee(int row, int col, bool canKill) {
	this->killed = false;
	this->row = row;
	this->col = col;
	this->speed = 0.1;
	this->scale = 0.1;
	this->canKill = canKill;
	this->id = ++SnooBee::ID;
}

unsigned int SnooBee::pickTexture()
{
	if (canKill)
		switch (orientation) {
		case 1:
			if (changeStep)
				return greenLeft1;
			else
				return greenLeft2;
		case 2:
			if (changeStep)
				return greenDown1;
			else
				return greenDown2;
		case 3:
			if (changeStep)
				return greenRight1;
			else
				return greenRight2;
		case 4:
			if (changeStep)
				return greenUp1;
			else
				return greenUp2;
		default:
			return greenDown1;
		}
	else
		switch (orientation)
		{
		case 1:
			if (changeStep)
				return yellowLeft1;
			else
				return yellowLeft2;
		case 2:
			if (changeStep)
				return yellowDown1;
			else
				return yellowDown2;
		case 3:
			if (changeStep)
				return yellowRight1;
			else
				return yellowRight2;
		case 4:
			if (changeStep)
				return yellowUp1;
			else
				return yellowUp2;
		default:
			return yellowDown1;
		}
}
double SnooBee::getX() {
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

double SnooBee::getY() {
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

void SnooBee::draw() {
	double posX = getX();
	double posY = getY();

	glColor3f(1, 1, 1);
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
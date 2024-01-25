#pragma once

class Pengo
{
public:
	static double width, height;
	static double startingX, startingY;
	static double speed;
	int orientation = 2;
	int row, col;
	double shift = 0;
	bool changeStep = true;
	bool dead = false;
	bool moving = false;
	bool unavailable = false;
	static unsigned int pengoLeft1, pengoLeft2, pengoRight1, pengoRight2;
	static unsigned int pengoUp1, pengoUp2, pengoDown1, pengoDown2;
	static unsigned int pengoDead;
	Pengo();
	Pengo(int row, int col);
	unsigned int texture();
	double getX();
	double getY();
	void draw();
};


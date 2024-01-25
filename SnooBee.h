#pragma once
class SnooBee
{
public:
	static unsigned int yellowDown1, yellowDown2, yellowUp1, yellowUp2;
	static unsigned int yellowLeft1, yellowLeft2, yellowRight1, yellowRight2;
	static unsigned int greenDown1, greenDown2, greenUp1, greenUp2;
	static unsigned int greenLeft1, greenLeft2, greenRight1, greenRight2;
	int id;
	static int ID;
	static double width, height;
	static double startingX, startingY;
	double speed;
	bool killed = false;
	int row, col;
	bool canKill = false;
	bool moving = false;
	bool changeStep = true;
	double scale;
	int orientation = 2;
	double shift = 0;
	SnooBee(int row, int col, bool canKill);
	double getX();
	double getY();
	void draw();
	unsigned int pickTexture();
};


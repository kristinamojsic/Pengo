#pragma once
class IceCube
{
public:
	static int ID;
	int id;
	bool diamond;
	static double width, height;
	static double startingX, startingY;
	static double speed;
	bool moving = false;
	bool destroyed = false;
	int row, col;
	int orientation = 0;
	double shift = 0.0;
	static unsigned int texture, textureDiamond;
	IceCube(int row, int col, bool diamond);
	unsigned int pickTexture(); 
	double getX();
	double getY();
	void draw();
	


};


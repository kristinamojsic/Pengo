#pragma once
#include <vector>
#include "IceCube.h"
#include "Pengo.h"
#include "SnooBee.h"

class PositionMatrix
{
public:
	Pengo pengo;
	std::vector<IceCube> icecubes;
	std::vector<SnooBee> snoobees;
	PositionMatrix();
	PositionMatrix(short coordinates[15][13], Pengo pengo);
	void draw();
};


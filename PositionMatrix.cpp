#include "PositionMatrix.h"

PositionMatrix::PositionMatrix()
{
	this->icecubes = std::vector<IceCube>();
	this->snoobees = std::vector<SnooBee>();
	this->pengo = Pengo();
}

PositionMatrix::PositionMatrix(short coordinates[15][13], Pengo pengo)
{
	this->icecubes = std::vector<IceCube>();
	this->snoobees = std::vector<SnooBee>();
	this->pengo = pengo;
	for (int row = 0; row < 15; row++)
		for (int col = 0; col < 13; col++)
	// obican blok
			if (coordinates[row][col] == 1)
				icecubes.push_back(IceCube(14 - row, col, 0));
	//  diamond 
			else if (coordinates[row][col] == 2)
				icecubes.push_back(IceCube(14 - row, col, 1));
	//obican neprijatelj, ne moze da unistava blokove
			else if (coordinates[row][col] == 3)
				snoobees.push_back(SnooBee(14 - row, col, 0));
	//moze da unistava blokove
			else if (coordinates[row][col] == 4)
				snoobees.push_back(SnooBee(14 - row, col, 1));
}


void PositionMatrix::draw() {
	pengo.draw();
	for (SnooBee& snooBee : snoobees)
		snooBee.draw();
	for (IceCube& icecube : icecubes)
		icecube.draw();
}



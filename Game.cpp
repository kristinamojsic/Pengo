#include "Game.h"
#include "RgbImage.h"
#include "Glut.h"
#include <cmath>

int level = 1;
int score = 0;
int lives = 3;
int anim = 0;
const unsigned int blockDestroyedScore = 20;
const unsigned int killedEnemyScore = 1000;
const unsigned int clearedLevelScore = 500;
const unsigned int diamondLineScore = 5000;
bool levelStarted = false;
bool gameOver = false;
bool gameWon = false;
bool levelCleared = false;
int pushedBlockDirection = 0;
unsigned int heartTexture = 0;

PositionMatrix matrix = PositionMatrix();
Pengo& pengo = matrix.pengo;


unsigned int loadTextureFromFile(const char* filename) {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	RgbImage theTexMap(filename);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
	return texture;
}

void loadTextures()
{
	heartTexture = loadTextureFromFile("images/heart2.bmp");
	Pengo::pengoDown1 = loadTextureFromFile("images/pengo1.bmp");
	Pengo::pengoDown2 = loadTextureFromFile("images/pengo2.bmp");
	Pengo::pengoUp1 = loadTextureFromFile("images/pengo3.bmp");
	Pengo::pengoUp2 = loadTextureFromFile("images/pengo4.bmp");
	Pengo::pengoLeft2 = loadTextureFromFile("images/pengo5.bmp");
	Pengo::pengoRight2 = loadTextureFromFile("images/pengo6.bmp");
	Pengo::pengoLeft1 = loadTextureFromFile("images/pengo7.bmp");
	Pengo::pengoRight1 = loadTextureFromFile("images/pengo8.bmp");
	Pengo::pengoDead = loadTextureFromFile("images/dead.bmp");
	IceCube::texture = loadTextureFromFile("images/icecube1.bmp");
	IceCube::textureDiamond = loadTextureFromFile("images/icecube2.bmp");
	SnooBee::greenDown1 = loadTextureFromFile("images/green1.bmp");
	SnooBee::greenDown2 = loadTextureFromFile("images/green2.bmp");
	SnooBee::greenLeft1 = loadTextureFromFile("images/green3.bmp");
	SnooBee::greenLeft2 = loadTextureFromFile("images/green4.bmp");
	SnooBee::greenRight1 = loadTextureFromFile("images/green5.bmp");
	SnooBee::greenRight2 = loadTextureFromFile("images/green6.bmp");
	SnooBee::greenUp1 = loadTextureFromFile("images/green7.bmp");
	SnooBee::greenUp2 = loadTextureFromFile("images/green8.bmp");
	SnooBee::yellowDown1 = loadTextureFromFile("images/yellow1.bmp");
	SnooBee::yellowDown2 = loadTextureFromFile("images/yellow2.bmp");
	SnooBee::yellowLeft1 = loadTextureFromFile("images/yellow3.bmp");
	SnooBee::yellowLeft2 = loadTextureFromFile("images/yellow4.bmp");
	SnooBee::yellowRight1 = loadTextureFromFile("images/yellow5.bmp");
	SnooBee::yellowRight2 = loadTextureFromFile("images/yellow6.bmp");
	SnooBee::yellowUp1 = loadTextureFromFile("images/yellow7.bmp");
	SnooBee::yellowUp2 = loadTextureFromFile("images/yellow8.bmp");


}
void drawHearts()
{
	double posX = 1.0;
	double posY = 18.0;
	for (int i = 0; i < lives; i++)
	{
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, heartTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(posX, posY);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(posX + 0.6, posY);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(posX + 0.6, posY + 0.5);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(posX, posY + 0.5);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		posX += 0.8;
	}
}

void displayScore()
{
	double posX = 5.0;
	double posY = 18.0;

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1.0, 0.0, 1.0);
	char textToDisplay[40];

	if (!gameOver && !gameWon)
		sprintf_s(textToDisplay, "Score: %d  Level: %d", score, level);
	else{
		posX = 0.8;
		glColor3f(1.0, 0.0, 1.0);

		if (gameOver)
			sprintf_s(textToDisplay, "GAME OVER, PRESS SPACE TO RESTART");
		if (gameWon)
			sprintf_s(textToDisplay, "YOU WON, PRESS SPACE TO RESTART");
	}
	glRasterPos2f(posX, posY);

	for (int i = 0; textToDisplay[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, textToDisplay[i]);

	glPopAttrib();
	if (!gameWon) drawHearts();
}

void startGame(int level) {

	if (level == 1) {
		short coordinates[15][13] = { {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
									  {0, 1, 0, 1, 1, 1, 0, 1, 1, 2, 0, 1, 0},
									  {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
									  {0, 1, 1, 3, 1, 1, 1, 1, 0, 1, 1, 1, 0},
									  {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
									  {0, 1, 0, 1, 1, 2, 1, 1, 1, 0, 0, 1, 0},
									  {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
									  {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},
									  {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
									  {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 3, 1, 0},
									  {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
									  {0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
									  {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
									  {0, 1, 0, 2, 0, 1, 1, 1, 1, 1, 0, 1, 0},
									  {0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0} };
		matrix = PositionMatrix(coordinates, Pengo(8, 6));
		pengo = matrix.pengo;
	}
	else if (level == 2) {
		short coordinates[15][13] = { {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
									  {0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 2, 0},
									  {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0},
									  {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0},
									  {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0},
									  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 3, 0},
									  {0, 1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 1},
									  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},
									  {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
									  {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0},
									  {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1},
									  {0, 1, 3, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
									  {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
									  {1, 1, 0, 1, 0, 2, 0, 1, 1, 1, 1, 4, 0},
									  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0} };
		matrix = PositionMatrix(coordinates, Pengo(8, 6));
		pengo = matrix.pengo;
	}
	else if (level == 3) {
		short coordinates[15][13] = { {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 4},
									  {0, 1, 0, 1, 3, 1, 1, 2, 0, 1, 0, 1, 1},
									  {0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0},
									  {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
									  {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
									  {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
									  {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
									  {0, 2, 0, 3, 0, 1, 1, 1, 1, 1, 0, 1 ,0},
									  {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
									  {0, 1, 1, 1, 0, 1, 0, 1, 0, 3, 0, 1, 0},
									  {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
									  {1, 1, 1, 2, 1, 3, 0, 1, 0, 1, 0, 1, 0},
									  {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
									  {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0},
									  {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0} };
		matrix = PositionMatrix(coordinates, Pengo(8, 6));
		pengo = matrix.pengo;
	}
}


void drawEverything() {
	if (!levelStarted) {
		levelStarted = true;
		anim++;
		levelCleared = false;
		startGame(level);
		glutTimerFunc(500, turnSnooBee, anim);
		glutTimerFunc(500, snooBeeChangeStep, anim);
		glutTimerFunc(1000, diamondBlocksInOneLine, anim);
	}
	displayScore();
	matrix.draw();
}

void restartGame() {
	level = 1;
	score = 0;
	lives = 3;
	levelStarted = false;
	levelCleared = false;
	gameOver = false;
	gameWon = false;

}



void turnPengo(int direction) {
	if (gameWon || gameOver || levelCleared || pengo.moving || pengo.dead)
		return;

	pengo.orientation = direction;
	//ako su ispunjeni uslovi pod kojim se ne krece
	switch (direction) {
	case 1:
		//ulevo
		if (pengo.col == 0)
			return;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == pengo.row && icecube.col == pengo.col - 1)
				return;
		break;
	case 2:
		//nadole
		if (pengo.row == 0)
			return;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == pengo.col && icecube.row == pengo.row - 1)
				return;
		break;
	case 3:
		//udesno
		if (pengo.col == 12)
			return;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == pengo.row && icecube.col == pengo.col + 1)
				return;
		break;
	case 4:
		//nagore
		if (pengo.row == 14)
			return;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == pengo.col && icecube.row == pengo.row + 1)
				return;
		break;
	default:
		return;
	}

	pengo.moving = true;
	pengo.changeStep = !pengo.changeStep;
	pengoChangePosition(direction);
}

void pengoChangePosition(int direction)
{
	if (pengo.dead)
		return;

	pengo.shift += pengo.speed;

	if (pengo.shift >= 1) {
		switch (direction) {
		case 1:
			pengo.col--;
			break;
		case 2:
			pengo.row--;
			break;
		case 3:
			pengo.col++;
			break;
		case 4:
			pengo.row++;
			break;
		}
		pengo.moving = false;
		pengo.shift = 0;
		return;
	}

	glutTimerFunc(30, pengoChangePosition, direction);
}

void pushIceCube() {
	if (pengo.moving || pengo.dead)
		return;

	switch (pengo.orientation) {
	case 1:
		//krece se ulevo
		if (pengo.col == 0) {
			return;
		}
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == pengo.row && icecube.col == pengo.col - 1 && !icecube.destroyed) {
				pushedBlockDirection = pengo.orientation;
				pushIceCubeCheck(icecube.id);
			}
		return;
	case 2:
		//nadole
		if (pengo.row == 0) {
			return;
		}
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == pengo.col && icecube.row == pengo.row - 1 && !icecube.destroyed) {
				pushedBlockDirection = pengo.orientation;
				pushIceCubeCheck(icecube.id);
			}
		return;
	case 3:
		//udesno
		if (pengo.col == 12) {
			return;
		}
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == pengo.row && icecube.col == pengo.col + 1 && !icecube.destroyed) {
				pushedBlockDirection = pengo.orientation;
				pushIceCubeCheck(icecube.id);
			}
		return;
	case 4:
		//nagore
		if (pengo.row == 14) {
			return;
		}
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == pengo.col && icecube.row == pengo.row + 1 && !icecube.destroyed) {
				pushedBlockDirection = pengo.orientation;
				pushIceCubeCheck(icecube.id);
			}
		return;
	default:
		return;
	}
}


void pushIceCubeCheck(int id) {
	IceCube* pushedIceCube = nullptr;
	for (IceCube& icecube : matrix.icecubes) {
		if (icecube.id == id) {
			pushedIceCube = &icecube;
			break;
		}
	}

	if (pushedIceCube == nullptr) {
		return;
	}

	pushedIceCube->orientation = pushedBlockDirection;
	switch (pushedIceCube->orientation) {
	case 1:
		if (pushedIceCube->col == 0) {
			checkDestroying(pushedIceCube);
			return;
		}
		for (IceCube& icecube : matrix.icecubes) {
			if (icecube.row == pushedIceCube->row && icecube.col == pushedIceCube->col - 1) {
				checkDestroying(pushedIceCube);
				return;
			}
		}
		break;
	case 2:
		if (pushedIceCube->row == 0) {
			checkDestroying(pushedIceCube);
			return;
		}
		for (auto& icecube : matrix.icecubes) {
			if (icecube.col == pushedIceCube->col && icecube.row == pushedIceCube->row - 1) {
				checkDestroying(pushedIceCube);
				return;
			}
		}
		break;
	case 3:
		if (pushedIceCube->col == 12) {
			checkDestroying(pushedIceCube);
			return;
		}
		for (IceCube& icecube : matrix.icecubes) {
			if (icecube.row == pushedIceCube->row && icecube.col == pushedIceCube->col + 1) {
				checkDestroying(pushedIceCube);
				return;
			}
		}
		break;
	case 4:
		if (pushedIceCube->row == 14) {
			checkDestroying(pushedIceCube);
			return;
		}
		for (IceCube& icecube : matrix.icecubes) {
			if (icecube.col == pushedIceCube->col && icecube.row == pushedIceCube->row + 1) {
				checkDestroying(pushedIceCube);
				return;
			}
		}
		break;
	default:
		break;
	}

	pushedIceCube->moving = true;
	pushedIceCube->shift += pushedIceCube->speed;

	iceCubeKill(pushedIceCube);
	if (pushedIceCube->shift >= 1) {
		switch (pushedIceCube->orientation) {
		case 1:
			pushedIceCube->col--;
			break;
		case 2:
			pushedIceCube->row--;
			break;
		case 3:
			pushedIceCube->col++;
			break;
		case 4:
			pushedIceCube->row++;
			break;
		}
		pushedIceCube->shift = 0;
	}

	glutTimerFunc(15, pushIceCubeCheck, id);
}


void iceCubeKill(IceCube* pushedIceCube) {
	for (auto i = matrix.snoobees.begin(); i < matrix.snoobees.end(); i++)
		if (abs((*i).getX() - pushedIceCube->getX()) < 0.75 && abs((*i).getY() - pushedIceCube->getY()) < 0.75) {
			matrix.snoobees.erase(i);
			score += killedEnemyScore;
			levelWon();
			return;
		}
}
void levelWon() {
	if (matrix.snoobees.empty()) {
		score += clearedLevelScore * level;
		if (level < 3) {
			levelCleared = true;
			glutTimerFunc(3000, startNewLevel, anim);
		}
		else
			gameWon = true;
	}
}
void startNewLevel(int animId) {
	if (animId != anim)
		return;

	levelStarted = false;
	level++;
}

void checkDestroying(IceCube* pushedIceCube) {
	if (!pushedIceCube->moving && !pushedIceCube->diamond) {
		pushedIceCube->destroyed = true;
		score += blockDestroyedScore;
		destroyIceCube(pushedIceCube->id);
	}
	else
		pushedIceCube->moving = false;
}
void destroyIceCube(int id) {
	for (std::vector<IceCube>::iterator i = matrix.icecubes.begin(); i != matrix.icecubes.end(); i++)
		if ((*i).id == id) {
			matrix.icecubes.erase(i);
			return;
		}
}

void turnSnooBee(int animId) {
	if (animId != anim)
		return;

	for (SnooBee& snooBee : matrix.snoobees) {
		pengoSnooBeeCollision();
		if (snooBee.moving || snooBee.killed)
			continue;
		if (!snooBee.canKill)
			snooBee.orientation = snooBeeNewOrientation(&snooBee);
		else
			snooBee.orientation = snooBeeKillerNewOrientation(&snooBee);
		snooBee.moving = true;
		switch (snooBee.orientation) {
		case 1:
			if (snooBee.col == 0) {
				snooBee.moving = false;
				continue;
			}
			for (IceCube& icecube : matrix.icecubes)
				if (icecube.row == snooBee.row && icecube.col == snooBee.col - 1) {
					snooBeeBlockCollision(&snooBee, icecube);
					break;}
			break;
		case 2:
			if (snooBee.row == 0) {
				snooBee.moving = false;
				continue;}
			for (IceCube& icecube : matrix.icecubes)
				if (icecube.col == snooBee.col && icecube.row == snooBee.row - 1) {
					snooBeeBlockCollision(&snooBee, icecube);
					break;}
			break;
		case 3:
			if (snooBee.col == 12) {
				snooBee.moving = false;
				continue;}
			for (IceCube& icecube : matrix.icecubes)
				if (icecube.row == snooBee.row && icecube.col == snooBee.col + 1) {
					snooBeeBlockCollision(&snooBee, icecube);
					break;}
			break;
		case 4:
			if (snooBee.row == 14) {
				snooBee.moving = false;
				continue;}
			for (IceCube& icecube : matrix.icecubes)
				if (icecube.col == snooBee.col && icecube.row == snooBee.row + 1) {
					snooBeeBlockCollision(&snooBee, icecube);
					break;}
			break;}
	}
	snooBeeChangePosition();
	glutTimerFunc(50, turnSnooBee, animId);
}

void snooBeeBlockCollision(SnooBee* snooBee, IceCube& icecube) {
	if (snooBee->canKill && !icecube.diamond) {
		icecube.destroyed = true;
		destroyIceCube(icecube.id);}
	else
		snooBee->moving = false;
}

int snooBeeNewOrientation(SnooBee* snooBee) {
	//int possibleOrientations[4] = { 0 };
	std::vector<int> possibleOrientations;
	int currentOrientation = snooBee->orientation;
	if (snooBee->col > 0) {
		bool hasIceCube = false;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == snooBee->row && icecube.col == snooBee->col - 1) {
				hasIceCube = true;
				break;
			}
		if (!hasIceCube) possibleOrientations.push_back(1);
	}
	if (snooBee->row > 0) {
		short hasIceCube = 0;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == snooBee->col && icecube.row == snooBee->row - 1) {
				hasIceCube = 1;
				break;
			}
		if (!hasIceCube) possibleOrientations.push_back(2);
	}
	if (snooBee->col < 12) {
		short hasIceCube = 0;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.row == snooBee->row && icecube.col == snooBee->col + 1) {
				hasIceCube = 1;
				break;
			}
		if (!hasIceCube) possibleOrientations.push_back(3);
	}
	if (snooBee->row < 14) {
		short hasIceCube = 0;
		for (IceCube& icecube : matrix.icecubes)
			if (icecube.col == snooBee->col && icecube.row == snooBee->row + 1) {
				hasIceCube = 1;
				break;
			}
		if (!hasIceCube) possibleOrientations.push_back(4);
	}

	if (possibleOrientations.size() == 0)
		return 2;

	int randInd = rand() % possibleOrientations.size();
	return possibleOrientations[randInd];
}

//snobee juri penga
int snooBeeKillerNewOrientation(SnooBee* snooBee) {

	if (abs(snooBee->row - pengo.row) < abs(snooBee->col - pengo.col)) {
		if (pengo.col < snooBee->col)
			return 1;
		return 3;
	}
	if (pengo.row < snooBee->row)
		return 2;
	return 4;
}

void snooBeeChangePosition() {
	for (SnooBee& snooBee : matrix.snoobees)
		if (snooBee.moving && !snooBee.killed) {
			snooBee.shift += snooBee.speed;
			if (snooBee.shift >= 1) {
				switch (snooBee.orientation) {
				case 1:
					snooBee.col--;
					break;
				case 2:
					snooBee.row--;
					break;
				case 3:
					snooBee.col++;
					break;
				case 4:
					snooBee.row++;
					break;
				}
				snooBee.moving = false;
				snooBee.shift = 0;
			}
		}
}

void snooBeeChangeStep(int animId) {
	if (animId != anim)
		return;

	for (SnooBee& snooBee : matrix.snoobees)
		snooBee.changeStep = !snooBee.changeStep;

	glutTimerFunc(300, snooBeeChangeStep, animId);
}


void pengoSnooBeeCollision() {
	if (pengo.dead)
		return;

	for (auto i = matrix.snoobees.begin(); i < matrix.snoobees.end(); i++)
		if (abs((*i).getX() - pengo.getX()) < 0.75 && abs((*i).getY() - pengo.getY()) < 0.75) {
			if ((*i).killed) {
				matrix.snoobees.erase(i);
				score += 500;
				levelWon();
			}
			else if (!pengo.unavailable) {
				pengo.dead = true;
				lives--;
				if (lives > 0)
					glutTimerFunc(1000, restartPengo, 0);
				else {
					gameOver = true;
				}}
			return;
		}
}

void restartPengo(int i) {
	matrix.pengo = Pengo(8, 6);
	pengo = matrix.pengo;
	pengo.unavailable = true;
	glutTimerFunc(1000, pengoAvailable, 0);
}

void pengoAvailable(int i) {
	pengo.unavailable = false;
}

void diamondBlocksInOneLine(int animId) {
	if (animId != anim)
		return;

	bool allBlocksInLine = true;
	for (const IceCube& currentBlock : matrix.icecubes) {
		if (!currentBlock.diamond)
			continue;
		if (currentBlock.moving) {
			allBlocksInLine = false;
			break;
		}

		bool hasAdjacentDiamond = false;
		for (const IceCube& adjacentBlock : matrix.icecubes) {
			if (&currentBlock == &adjacentBlock || !adjacentBlock.diamond)
				continue;
			if (currentBlock.row == adjacentBlock.row && abs(currentBlock.col - adjacentBlock.col) == 1) {
				hasAdjacentDiamond = true;
				break;
			}
			if (currentBlock.col == adjacentBlock.col && abs(currentBlock.row - adjacentBlock.row) == 1) {
				hasAdjacentDiamond = true;
				break;
			}
		}
		if (!hasAdjacentDiamond) {
			allBlocksInLine = false;
			break;
		}
	}
	if (!allBlocksInLine)
		glutTimerFunc(1000, diamondBlocksInOneLine, animId);
	else {
		matrix.snoobees.clear();
		score += diamondLineScore;
		levelWon();
	}
}


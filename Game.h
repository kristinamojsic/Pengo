#pragma once
#include "PositionMatrix.h"
#include <string>

void drawEverything();
void loadTextures();
void displayScore();
void drawHearts();
void startGame(int level);
void restartGame();
void levelWon();
void turnPengo(int direction);
void pengoChangePosition(int direction);
void pushIceCube();
void pushIceCubeCheck(int id);
void iceCubeKill(IceCube* icecube);
void checkDestroying(IceCube* pushedCube);
void destroyIceCube(int id);
void turnSnooBee(int animId);
int snooBeeNewOrientation(SnooBee* snooBee);
int snooBeeKillerNewOrientation(SnooBee* snooBee);
void snooBeeChangePosition();
void snooBeeBlockCollision(SnooBee* snooBee, IceCube& icecube);
void snooBeeChangeStep(int i);
void pengoSnooBeeCollision();
void restartPengo(int i);
void pengoAvailable(int i);
void diamondBlocksInOneLine(int animId);
void startNewLevel(int animId);
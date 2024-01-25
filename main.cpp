#include "Game.h"
#include "Glut.h"

const double Xmin = 0.0, Xmax = 14.0;
const double Ymin = 0.0, Ymax = 20.0;

void myKeyboardFunc(unsigned char key, int x, int y) {
	if (key == 'R' || key == 'r' || key == 32)
		restartGame();
	if (key == 'Z' || key == 'z')
		pushIceCube();
	if (key == 27)
		exit(0);
}

void mySpecialKeyFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		turnPengo(1);
		break;
	case GLUT_KEY_DOWN:
		turnPengo(2);
		break;
	case GLUT_KEY_RIGHT:
		turnPengo(3);
		break;
	case GLUT_KEY_UP:
		turnPengo(4);
		break;
	}
}


void updateScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawEverything();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void initRendering() {
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH);
	loadTextures();
}

void resizeWindow(int w, int h) {
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	glViewport(0, 0, w, h);

	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin) * scale;
		windowXmax = center + (Xmax - center) * scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin) * scale;
		windowYmax = center + (Ymax - center) * scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(10, 60);
	glutInitWindowSize(560, 720);
	glutCreateWindow("Pengo");
	initRendering();
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialKeyFunc);
	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(updateScene);

	glutMainLoop();

	return(0);
}
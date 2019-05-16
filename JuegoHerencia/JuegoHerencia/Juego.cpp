#include <iostream>
#include "Fabrica.h"
#include "Tablero.h"
#include "glut.h"

//call back declarations: will be called by glut when registered
void OnDraw(void); //dibujar
void OnKeyboardDown(unsigned char key, int x, int y); //tecla
void OnMouseClick(int button, int state, int x, int y); //ratón
void OnTimer(int value); //llamada cada cierto tiempo

//global objects which make the world
Tablero T;
Fabrica F;
Fabrica * pF = &F;

int main(int argc, char* argv[]) {
	//GL Initialization stuff
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("ClipFactory");


	//Register callbacks
	glutDisplayFunc(OnDraw);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);
	glutTimerFunc(25, OnTimer, 0);			 //set timer if required, currently not used



	//sets light and perspective
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//glut takes control
	glutMainLoop();

	return 0;
}

void OnDraw(void) {
	T.Dibuja(F.getnFilas(), F.getnColumnas(), *pF);
	glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x_t, int y_t) {
	T.KeyDown(key);
	glutPostRedisplay();
}

void OnMouseClick(int b, int state, int x, int y) {
	bool down = (state == GLUT_DOWN);
	int button;
	if (b == GLUT_LEFT_BUTTON) {
		button = MOUSE_LEFT_BUTTON;
	}
	if (b == GLUT_RIGHT_BUTTON) {
		button = MOUSE_RIGHT_BUTTON;
		//std::cout << "MOUSE_RIGHT_BUTTON" << std::endl;
	}

	int specialKey = glutGetModifiers();
	bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
	bool sKey = specialKey & GLUT_ACTIVE_SHIFT;


	T.MouseButton(x, y, b, down, sKey, ctrlKey);
	glutPostRedisplay();
}


void OnTimer(int value) {
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}
#include "Tablero.h"
#include "gltools.h"
#include "glut.h"

Tablero::Tablero() {
	FilaSeleccionada = ColumnaSeleccionada = 0;
	ancho = 3.0; //ancho de cada celda del tablero
	nFilas, nColumnas;
	x_centro, y_centro, dist_x, dist_y, z_ojo;
}

Tablero::~Tablero() {

}

void Tablero::CentroCelda(int coordx, int coordy, float& glx, float& gly) {
	//coordx y coordy son las coordenadas de la celda, siendo la superior izquierda la (0,0)
	//glx, gly son las coordenadas del centro de la celda en coordenadas del mundo
	glx = coordx * ancho + ancho / 2.0f;
	gly = -coordy * ancho - ancho / 2.0f;
}

void Tablero::CoordCelda(double x, double y, int& xc, int& yc) {
	xc = (int)(abs(y / ancho));
	yc = (int)(x / ancho);
}

void Tablero::DibujaMalla() {
	//Dibuja la "malla" del tablero con el numero de filas y columnas de la fabrica
	//de forma que la esquina superior izquierda esta en (0,0)
	//Ademas centra la vista en el tablero, y aleja o acerca la vista
	//para que se vea completo
	dist_x = nColumnas * ancho; dist_y = nFilas * ancho;
	x_centro = dist_x / 2; y_centro = -dist_y / 2;

	if (dist_x > (dist_y * 0.75)) {
		z_ojo = 1.5 * dist_x * atan(23);
	}
	else { z_ojo = 1.5 * dist_y * atan(29); }

	//glClearColor(50, 244, 244, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x_centro, y_centro, z_ojo,  // posicion del ojo
		x_centro, y_centro, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)  

	GLTools::Color(gltools::WHITE);
	for (int i = 0; i <= nFilas; i++) {
		if (i% nFilas == 0) glLineWidth(4);
		else glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(0, -i * ancho, 0);
		glVertex3f(dist_x, -i * ancho, 0);
		glEnd();
	}
	for (int j = 0; j <= nColumnas; j++) {
		if (j% nColumnas == 0) glLineWidth(4);
		else glLineWidth(1);
		glBegin(GL_LINES);
		glVertex3f(j*ancho, 0, 0);
		glVertex3f(j*ancho, -dist_y, 0);
		glEnd();
	}
}

void Tablero::DibujaCelda(int i, int j, Fabrica &f) {
	float glx, gly;
	Pieza *pPieza = f.getValue(i, j);
	glDisable(GL_LIGHTING);
	if (pPieza == NULL) {
		CentroCelda(j, i, glx, gly);
		//glDisable(GL_LIGHTING);
		GLTools::Color(gltools::WHITE);
		glTranslatef(glx, gly, 0);
		glutSolidSphere((ancho / 2.0f)*0.8f, 50, 50);
		glTranslatef(-glx, -gly, 0);
		//glEnable(GL_LIGHTING);
	}
	else {
		switch (pPieza->get_type()) {
		case Autoclipper_M:
			CentroCelda(j, i, glx, gly);
			//glDisable(GL_LIGHTING);
			GLTools::Color(gltools::RED);
			glTranslatef(glx, gly, 0);
			glutSolidSphere((ancho / 2.0f)*0.8f, 50, 50);
			glTranslatef(-glx, -gly, 0);
			//glEnable(GL_LIGHTING);

			break;
		case Marketing_M:
			CentroCelda(j, i, glx, gly);
			//glDisable(GL_LIGHTING);
			GLTools::Color(gltools::RED);
			glTranslatef(glx, gly, 0);
			glutSolidSphere((ancho / 2.0f)*0.8f, 50, 50);
			glTranslatef(-glx, -gly, 0);
			//glEnable(GL_LIGHTING);

			break;
		case Trefiladora_M:
			CentroCelda(j, i, glx, gly);
			//glDisable(GL_LIGHTING);
			GLTools::Color(gltools::RED);
			glTranslatef(glx, gly, 0);
			glutSolidSphere((ancho / 2.0f)*0.8f, 50, 50);
			glTranslatef(-glx, -gly, 0);
			//glEnable(GL_LIGHTING);

			break;
		}
	}
}

void Tablero::Dibuja(int nF, int nC, Fabrica &f) {
	nFilas = nF; nColumnas = nC;
	DibujaMalla();
	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			DibujaCelda(i, j, f);
		}
	}
	//Dibuja un rectángulo transparente en el tablero para capturar el ratón
	//glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLTools::Color(gltools::WHITE, 0.1f);
	//glTranslatef(x_centro, y_centro, 0);
	glRectf(0, 0, nColumnas * ancho, -nFilas * ancho);
	//glTranslatef(-x_centro, -y_centro, 0);
	//glEnable(GL_LIGHTING);
}

void Tablero::KeyDown(unsigned char key) {

}

void Tablero::MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey) {
	//computes cell coordinates from mouse coordinates

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//coordenadas de celda:
	CoordCelda(posX, posY, ColumnaSeleccionada, FilaSeleccionada);

	//otros

	if (down) {
		controlKey = ctrlKey;
		shiftKey = sKey;
	}
	else {
		controlKey = shiftKey = false;
	}

	if (button == MOUSE_LEFT_BUTTON)
		leftButton = down;
	else if (button == MOUSE_RIGHT_BUTTON)
		rightButton = down;
	else if (button == MOUSE_MIDDLE_BUTTON)
		midButton = down;

	//***WRITE ACTIONS CONNECTED TO MOUSE STATE HERE
	//if (MOUSE_LEFT_BUTTON == down) { if (N <= 8) N++; }
	//print cell coordinates after click
	if (MOUSE_LEFT_BUTTON == down)
		cout << "(" << ColumnaSeleccionada << "," << FilaSeleccionada << ")" << endl;
	else if (MOUSE_RIGHT_BUTTON == down)
		cout << "(" << nFilas << ")" << endl;
}

#include "Tablero.h"
#include "gltools.h"
#include "ETSIDI.h"
#include "glut.h"

Tablero::Tablero() {
	FilaSeleccionada = ColumnaSeleccionada = -1;
	ancho = 3.0; //ancho de cada celda del tablero
	contador = 0; contadordeRatonI = 0; contadordeRatonD = 0;
	F = C = FA = CA = -1;
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
	xc = (int)(-(y / ancho));
	yc = (int)(x / ancho);
	if ((xc < 0) || (xc > nFilas) || (yc < 0) || (yc > nColumnas)) { xc = yc = -1; }//valor por defecto
	//que traducimos como "Ninguna celda seleccionada"
	float glx, gly, xmax, xmin, ymax, ymin;
	CentroCelda(-2, 1, glx, gly); glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.005*dist_y*dist_y;
	xmax = glx + ancho * dist_x / 30; xmin = glx - ancho * dist_x / 30;
	ymax = gly + ancho * dist_y / 30; ymin = gly - ancho * dist_y / 30;
	if ((x < xmax) && (x > xmin) && (y < ymax) && (y > ymin)) {
		xc = 50;//TREFILADORA
	}
	CentroCelda(-2, 2, glx, gly); glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.009*dist_y*dist_y;
	xmax = glx + ancho * dist_x / 30; xmin = glx - ancho * dist_x / 30;
	ymax = gly + ancho * dist_y / 30; ymin = gly - ancho * dist_y / 30;
	if ((x < xmax) && (x > xmin) && (y < ymax) && (y > ymin)) {
		xc = 60;//AUTOCLIPPER
	}
	CentroCelda(-2, 3, glx, gly); glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.013*dist_y*dist_y;
	xmax = glx + ancho * dist_x / 30; xmin = glx - ancho * dist_x / 30;
	ymax = gly + ancho * dist_y / 30; ymin = gly - ancho * dist_y / 30;
	if ((x < xmax) && (x > xmin) && (y < ymax) && (y > ymin)) {
		xc = 70;//MARKETING
	}
	CentroCelda(0, nFilas, glx, gly); glx = glx + 0.004*dist_x*dist_x; gly = gly - 0.003*dist_y*dist_y;
	xmax = glx + ancho * dist_x / 30; xmin = glx - ancho * dist_x / 30;
	ymax = gly + ancho * dist_y / 30; ymin = gly - ancho * dist_y / 30;
	if ((x < xmax) && (x > xmin) && (y < ymax) && (y > ymin)) {
		xc = 80;//BOTON PASAR AL DIA SIGUIENTE
	}
	CentroCelda(1, nFilas, glx, gly); glx = glx + 0.008*dist_x*dist_x; gly = gly - 0.003*dist_y*dist_y;
	xmax = glx + ancho * dist_x / 30; xmin = glx - ancho * dist_x / 30;
	ymax = gly + ancho * dist_y / 30; ymin = gly - ancho * dist_y / 30;
	if ((x < xmax) && (x > xmin) && (y < ymax) && (y > ymin)) {
		xc = 90;//BOTON SUBIR DE NIVEL
	}
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

void Tablero::DibujaTitulo() {
	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 20);
	ETSIDI::printxy("CLIP FACTORY", dist_x * 0.25, dist_y * 0.1, 0.00);
}

void Tablero::DibujaInfo(Fabrica &f) {
	char Cadena[20];
	float Tab[9] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
	if (nFilas >= 16) { Tab[0] = 4.0; Tab[1] = 8.0; Tab[2] = 12.0; Tab[3] = 16.0; Tab[4] = 20.0; Tab[5] = 24.0; Tab[6] = 28.0; Tab[7] = 32.0; Tab[8] = 36.0; }
	else if (nFilas >= 12) { Tab[0] = 3.0; Tab[1] = 6.0; Tab[2] = 9.0; Tab[3] = 12.0; Tab[4] = 15.0; Tab[5] = 18.0; Tab[6] = 21.0; Tab[7] = 24.0; Tab[8] = 27.0; }
	else if (nFilas >= 8) { Tab[0] = 2.0; Tab[1] = 4.0; Tab[2] = 6.0; Tab[3] = 8.0; Tab[4] = 10.0; Tab[5] = 12.0; Tab[6] = 14.0; Tab[7] = 16.0; Tab[8] = 18.0; }

	ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 10);
	ETSIDI::printxy("Fondos:", dist_x*1.1, -Tab[0], 0.00);
	snprintf(Cadena, 20, "%f", f.getFondos());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[0], 0.00);
	ETSIDI::printxy("Produccion:", dist_x*1.1, -Tab[1], 0.00);
	snprintf(Cadena, 20, "%d", f.getProduccion());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[1], 0.00);
	ETSIDI::printxy("Precio:", dist_x*1.1, -Tab[2], 0.00);
	snprintf(Cadena, 20, "%f", f.getPrecio());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[2], 0.00);
	ETSIDI::printxy("Prod. Alambre:", dist_x*1.1, -Tab[3], 0.00);
	snprintf(Cadena, 20, "%f", f.getProduccionAlambre());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[3], 0.00);
	ETSIDI::printxy("Cons. Alambre:", dist_x*1.1, -Tab[4], 0.00);
	snprintf(Cadena, 20, "%f", f.getConsumoAlambre());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[4], 0.00);
	ETSIDI::printxy("Cons. Dinero:", dist_x*1.1, -Tab[5], 0.00);
	snprintf(Cadena, 20, "%f", f.getConsumoDinero());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[5], 0.00);
	ETSIDI::printxy("Gastos:", dist_x*1.1, -Tab[6], 0.00);
	snprintf(Cadena, 20, "%f", f.getGastos());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[6], 0.00);
	ETSIDI::printxy("Beneficio:", dist_x*1.1, -Tab[7], 0.00);
	snprintf(Cadena, 20, "%f", f.getBeneficio());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[7], 0.00);
	ETSIDI::printxy("Dias:", dist_x*1.1, -Tab[8], 0.00);
	snprintf(Cadena, 20, "%d", f.getDias());
	ETSIDI::printxy(Cadena, dist_x*1.40, -Tab[8], 0.00);
}

void Tablero::DibujaMasInfo(Fabrica &f) {
	ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 10);
	if (CeldadelTablero(ColumnaSeleccionada, FilaSeleccionada) == FALSE) {
		ETSIDI::printxy("INFORMACION: Ninguna celda seleccionada", dist_x*0.70, -dist_y * 1.09, 0.00);
	}
	else {
		Pieza *pPieza = f.getValue(FilaSeleccionada, ColumnaSeleccionada);
		if (pPieza == NULL) {
			ETSIDI::printxy("INFORMACION: Celda vacia", dist_x*0.70, -dist_y * 1.09, 0.00);
		}
		else {
			switch (pPieza->get_type()) {
			case Trefiladora_M:
				switch (pPieza->getLevel()) {
				case 0:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 1", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 1:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 2", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 2:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 3", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 3:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 4", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 4:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 5", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 5:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 6", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 6:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 7", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 7:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 8", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 8:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 9", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				case 9:
					ETSIDI::printxy("INFORMACION: Trefiladora de nivel 10", dist_x*0.70, -dist_y * 1.09, 0.00);
					break;
				}
				break;
			case Autoclipper_M:
				ETSIDI::printxy("INFORMACION: AutoClipper de nivel", dist_x*0.70, -dist_y * 1.09, 0.00);
				break;
			case Marketing_M:
				ETSIDI::printxy("INFORMACION: Marketing de nivel", dist_x*0.70, -dist_y * 1.09, 0.00);
				break;
			}
		}
	}
}

void Tablero::DibujaCeldaSeleccionada() {
	if ((FilaSeleccionada >= 0 && FilaSeleccionada < nFilas) && (ColumnaSeleccionada >= 0 && ColumnaSeleccionada < nColumnas)) {
		float glx, gly;
		CentroCelda(FilaSeleccionada, ColumnaSeleccionada, glx, gly);
		GLTools::Color(gltools::RED);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex3f(glx - ancho / 2, gly - ancho / 2, 0.15); glVertex3f(glx - ancho / 2, gly + ancho / 2, 0.15);
		glVertex3f(glx - ancho / 2, gly + ancho / 2, 0.15); glVertex3f(glx + ancho / 2, gly + ancho / 2, 0.15);
		glVertex3f(glx + ancho / 2, gly + ancho / 2, 0.15); glVertex3f(glx + ancho / 2, gly - ancho / 2, 0.15);
		glVertex3f(glx + ancho / 2, gly - ancho / 2, 0.15); glVertex3f(glx - ancho / 2, gly - ancho / 2, 0.15);
		glEnd();
	}
}


void Tablero::DibujaCelda(int i, int j, Fabrica &f) {
	float glx, gly;
	Pieza *pPieza = f.getValue(i, j);
	glDisable(GL_LIGHTING);
	if (pPieza == NULL) {
		CentroCelda(i, j, glx, gly);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/noocupadoo.png").id);
		glBegin(GL_POLYGON);

		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);		glVertex3f(glx - ancho / 2, gly - ancho / 2, 0);
		glTexCoord2d(1, 1);		glVertex3f(glx + ancho / 2, gly - ancho / 2, 0);
		glTexCoord2d(1, 0);		glVertex3f(glx + ancho / 2, gly + ancho / 2, 0);
		glTexCoord2d(0, 0);		glVertex3f(glx - ancho / 2, gly + ancho / 2, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		switch (pPieza->get_type()) {
		case Autoclipper_M:
			CentroCelda(i, j, glx, gly);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina1.png").id);
			glBegin(GL_POLYGON);

			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(glx - ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 1);		glVertex3f(glx + ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 0);		glVertex3f(glx + ancho / 2, gly + ancho / 2, 0);
			glTexCoord2d(0, 0);		glVertex3f(glx - ancho / 2, gly + ancho / 2, 0);
			glEnd();

			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			break;
		case Marketing_M:
			CentroCelda(i, j, glx, gly);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina3.png").id);
			glBegin(GL_POLYGON);

			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(glx - ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 1);		glVertex3f(glx + ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 0);		glVertex3f(glx + ancho / 2, gly + ancho / 2, 0);
			glTexCoord2d(0, 0);		glVertex3f(glx - ancho / 2, gly + ancho / 2, 0);
			glEnd();

			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			break;
		case Trefiladora_M:
			CentroCelda(i, j, glx, gly);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina2.png").id);
			glBegin(GL_POLYGON);

			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(glx - ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 1);		glVertex3f(glx + ancho / 2, gly - ancho / 2, 0);
			glTexCoord2d(1, 0);		glVertex3f(glx + ancho / 2, gly + ancho / 2, 0);
			glTexCoord2d(0, 0);		glVertex3f(glx - ancho / 2, gly + ancho / 2, 0);
			glEnd();

			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			break;
		}
	}
}

void Tablero::DibujaNuevasMaquinas() {
	ETSIDI::setTextColor(1, 1, 1);
	ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 10);
	ETSIDI::printxy("NUEVA MAQUINA", -dist_x * 0.47, -dist_y * 0.16, 0.00);
	float glx, gly;
	glDisable(GL_LIGHTING);
	CentroCelda(-2, 1, glx, gly);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina2.png").id);
	glBegin(GL_POLYGON);
	glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.005*dist_y*dist_y;
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(glx - ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(glx + ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(glx + ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glTexCoord2d(0, 0);		glVertex3f(glx - ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	CentroCelda(-2, 2, glx, gly);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina1.png").id);
	glBegin(GL_POLYGON);
	glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.009*dist_y*dist_y;
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(glx - ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(glx + ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(glx + ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glTexCoord2d(0, 0);		glVertex3f(glx - ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	CentroCelda(-2, 3, glx, gly);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/maquina3.png").id);
	glBegin(GL_POLYGON);
	glx = glx - 0.005*dist_x*dist_x; gly = gly - 0.013*dist_y*dist_y;
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(glx - ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(glx + ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(glx + ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glTexCoord2d(0, 0);		glVertex3f(glx - ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Tablero::DibujaBotonPasarDia() {
	float glx, gly;
	glDisable(GL_LIGHTING);
	CentroCelda(0, nFilas, glx, gly);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/diasiguiente.png").id);
	glBegin(GL_POLYGON);
	glx = glx + 0.004*dist_x*dist_x; gly = gly - 0.003*dist_y*dist_y;
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(glx - ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(glx + ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(glx + ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glTexCoord2d(0, 0);		glVertex3f(glx - ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Tablero::DibujaBotonSubirNivel() {
	float glx, gly;
	glDisable(GL_LIGHTING);
	CentroCelda(1, nFilas, glx, gly);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("img/subirnivel.png").id);
	glBegin(GL_POLYGON);
	glx = glx + 0.008*dist_x*dist_x; gly = gly - 0.003*dist_y*dist_y;
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(glx - ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 1);		glVertex3f(glx + ancho * dist_x / 30, gly - ancho * dist_y / 30, 0);
	glTexCoord2d(1, 0);		glVertex3f(glx + ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glTexCoord2d(0, 0);		glVertex3f(glx - ancho * dist_x / 30, gly + ancho * dist_y / 30, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Tablero::Dibuja(int nF, int nC, Fabrica &f) {
	nFilas = nF; nColumnas = nC;

	DibujaMalla();
	DibujaTitulo();
	DibujaInfo(f);
	DibujaMasInfo(f);
	DibujaCeldaSeleccionada();
	DibujaNuevasMaquinas();
	DibujaBotonPasarDia();
	DibujaBotonSubirNivel();

	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			DibujaCelda(i, j, f);
		}
	}
}

bool Tablero::CeldadelTablero(int x, int y) {
	if (x >= 0 && x < nColumnas && y >= 0 && y < nFilas) {
		return TRUE;
	}
	else { return FALSE; }
}

void Tablero::KeyDown(unsigned char key, Fabrica &f) {
	switch (key) {
	case 's':
		f.CambiaTamaño(1, 1); break;
	}
}

void Tablero::MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey, Fabrica &f) {
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

	int GO = 1;
	if (MOUSE_LEFT_BUTTON == button) {
		contadordeRatonI = contadordeRatonI + 1;
		if (contadordeRatonI == 1) { FA = F; CA = C; F = FilaSeleccionada; C = ColumnaSeleccionada; }
		//CODIGO DEL JUEGO:
		if (contadordeRatonI == 2) {
			if (C == 50 && CeldadelTablero(CA, FA) == TRUE && f.getValue(FA, CA) == NULL) { //TREFILADORA
				f.new_maquina(Trefiladora_M, FA, CA);
			}
			else if (C == 60 && CeldadelTablero(CA, FA) == TRUE && f.getValue(FA, CA) == NULL) { //AUTOCLIPPER
				f.new_maquina(Autoclipper_M, FA, CA);
			}
			else if (C == 70 && CeldadelTablero(CA, FA) == TRUE && f.getValue(FA, CA) == NULL) { //MARKETING
				f.new_maquina(Marketing_M, FA, CA);
			}
			else if (C == 80) { // PASAR DE DIA
				f.update_dias(); GO = f.UpdateFabric(); if (GO == 0) { cout << "GAME OVER" << endl; }
			}
			else if (C == 90 && CeldadelTablero(CA, FA) == TRUE && f.getValue(FA, CA) != NULL) { //SUBIR DE NIVEL
				f.UpdateMachine(FA, CA);
			}
			cout << "(" << ColumnaSeleccionada << "," << FilaSeleccionada << ")" << endl;
			contadordeRatonI = 0;
		}
	}
	else if (MOUSE_RIGHT_BUTTON == button) {
		cout << "(" << nFilas << ")" << endl;
	}
}

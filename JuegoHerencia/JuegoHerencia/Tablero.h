#pragma once
#include "Fabrica.h"


enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

class Tablero {
private:
	int FilaSeleccionada, ColumnaSeleccionada;
	float ancho; //ancho de cada celda del tablero
	int nFilas, nColumnas;
	float x_centro, y_centro, dist_x, dist_y, z_ojo;
	bool controlKey;
	bool sKey;
	bool leftButton;
	bool rightButton;
	bool midButton;
public:
	Tablero();
	~Tablero();
	void CentroCelda(int coordx, int coordy, float& glx, float& gly);
	void CoordCelda(double x, double y, int& xc, int& yc);
	void DibujaMalla();
	void DibujaCelda(int i, int j, Fabrica &f);
	void Dibuja(int nF, int nC, Fabrica &f);
	void KeyDown(unsigned char key);
	void MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey);
};


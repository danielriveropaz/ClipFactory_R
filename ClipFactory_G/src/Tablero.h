#pragma once
#include "Fabrica.h"


enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

class Tablero {
private:
	int FilaSeleccionada, ColumnaSeleccionada;
	int F, C, FA, CA;
	float ancho; //ancho de cada celda del tablero
	int nFilas, nColumnas;
	float x_centro, y_centro, dist_x, dist_y, z_ojo;
	bool controlKey;
	bool sKey;
	bool leftButton;
	bool rightButton;
	bool midButton;
	int contador, contadordeRatonI, contadordeRatonD;
	bool fondos;
	float Tab[9];
	bool EstaSeguroAmpliar;
public:
	Tablero();
	~Tablero();
	void CentroCelda(int coordx, int coordy, float& glx, float& gly);
	void CoordCelda(double x, double y, int& xc, int& yc);
	void DibujaMalla();
	void DibujaCelda(int i, int j, Fabrica &f);
	void DibujaTitulo();
	void DibujaCeldaSeleccionada();
	void DibujaNuevasMaquinas();
	void DibujaBotonPasarDia();
	void DibujaBotonSubirNivel();
	void DibujaInfo(Fabrica &f);
	void DibujaMasInfo(Fabrica &f);
	void DibujaMasInfoPieza(Pieza &p);
	void Tablero::DibujaInfoNuevaMaquina(int tipo);
	void Dibuja(int nF, int nC, Fabrica &f);
	void KeyDown(unsigned char key, Fabrica &f);
	void MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey, Fabrica &f);
	bool CeldadelTablero(int x, int y); //nos dice si pertenece o no al tablero
	void ActualizaSeleccion();
	bool getFondos();
	void ActualizaTab();
};


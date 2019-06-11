#pragma once
#include "Tablero.h"

class Coordinador
{
private:
	enum Estado { INICIO, JUEGO, GAMEOVER, FIN };
	Estado estado;
	Tablero tablero;
	Fabrica fabrica;
	Fabrica * pF = &fabrica;
	std::string cargar;
public:
	Coordinador();
	~Coordinador();
	void Dibuja();
	void KeyDown(unsigned char key);
	void MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey);
};


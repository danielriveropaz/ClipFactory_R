#include "Coordinador.h"


Coordinador::Coordinador()
{
	estado = INICIO;
	ETSIDI::playMusica("music/digimonadv.mp3", true);
}

Coordinador::~Coordinador() {

}

void Coordinador::Dibuja() {

	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (estado == INICIO)
	{
		//CODIGO PARA PINTAR UNA PANTALLA NEGRA CON LETRAS

		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 32);
		ETSIDI::printxy("CLIP FACTORY", -6, 8, 0.01);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 11);
		ETSIDI::printxy("(N): NUEVA PARTIDA", -3, 1, 0.01);
		ETSIDI::printxy("(L): CARGAR PARTIDA", -3, 0, 0.01);
		//ETSIDI::printxy("PULSE LA TECLA 'P' PARA SALIR", -5, 6);
		//ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::printxy("Daniel Rivero, Antonio Arco, John Jairo Marín", -6, 7, 0.01);
	}
	else if (estado == JUEGO)
	{
		tablero.Dibuja(fabrica.getnFilas(), fabrica.getnColumnas(), *pF);
	}
	else if (estado == GAMEOVER)
	{
		//CODIGO PARA PINTAR UNA PANTALLA NEGRA CON LETRAS

		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/ATFAntique Bold.ttf", 25);
		ETSIDI::printxy("GAME OVER ", -4, 8, 0.01);
	}
	/*else if (estado == FIN)
	{
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		mundo.dibuja();
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("ENHORABUENA, ¡Has triunfado!", -5, 10, 0.01);
		ETSIDI::printxy("Pulsa -C- para continuar", -5, 9);
	}*/
}

void Coordinador::KeyDown(unsigned char key) {
	if (estado == INICIO)
	{
		switch (key) {
		case 'n' :
		case 'N' :
			estado = JUEGO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("music/digimonadvbajo.mp3", true);
			break;
		case 'l':
		case 'L':
			estado = JUEGO;
			ETSIDI::stopMusica();
			ETSIDI::playMusica("music/digimonadvbajo.mp3", true);
			//PONER AQUI PARA CARGAR LA PARTIDA
		}
	}
	else if (estado == JUEGO)
	{
		tablero.KeyDown(key, *pF);
	}
	else if (estado == GAMEOVER)
	{

	}
}


void Coordinador::MouseButton(int x, int y, int button, bool down, bool shiftKey, bool ctrlKey) {
	if (estado == INICIO)
	{

	}
	else if (estado == JUEGO)
	{
		tablero.MouseButton(x, y, button, down, shiftKey, ctrlKey, *pF);
		if (tablero.getFondos() == false) { estado = GAMEOVER; }
	}
	else if (estado == GAMEOVER)
	{

	}
}

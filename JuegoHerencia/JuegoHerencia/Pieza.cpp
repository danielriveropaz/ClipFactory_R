#include "Pieza.h"


/*
Pieza::Pieza(float V_aporte[TOP_LEVEL], float V_consumo[TOP_LEVEL]) {

	level = 0;
}
*/

Pieza::~Pieza()
{
}

Pieza::Pieza()
{
	level = 0;
}

Pieza::Pieza(int a) //Esto crea una pieza que ni aporta ni consume.
{
	level = 0;

	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = 0;
		consumo[i] = 0;
	}

	coste = 0;

}


//METODOS

int Pieza::get_type()
{
	return tipo;
}

float Pieza::get_consumo()
{
	return consumo[level];
}

float Pieza::get_aporte() {

	return aporte[level];
}



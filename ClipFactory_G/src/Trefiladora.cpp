#include "Trefiladora.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


Trefiladora::~Trefiladora()
{
}



Trefiladora::Trefiladora() :Pieza()
{
	float SetUPaporte[] = { 1,2,3,4,5,6,7,8,9,10 };
	float SetUpconsumo[] = { 10,9,8,7,6,5,4,3,2,1 };
	float SetUpcoste[] = { 10, 30,40,55,69,79,59,49,86,10 };


	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = SetUPaporte[i];
		consumo[i] = SetUpconsumo[i];
		coste[i] = SetUpcoste[i];
	}

	level = 0;

	tipo = 3;

}

ostream & Trefiladora::print(ostream & o)
{
	o << "T";
	return o;// TODO: insertar una instrucción return aquí
}


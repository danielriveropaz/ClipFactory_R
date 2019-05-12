#include "AutoClipper.h"
#include <fstream>
#include <sstream>
//#include <iostream>

using namespace std;


AutoClipper::AutoClipper() :Pieza()
{
	float SetUPaporte[] = { 1,2,3,4,5,6,7,8,9,10 };
	float SetUpconsumo[] = { 10,9,8,7,6,5,4,3,2,1 };

	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = SetUPaporte[i];
		consumo[i] = SetUpconsumo[i];
	}
	
	coste = 10;
	tipo = 1;
}

ostream & AutoClipper::print(ostream & o)
{
	o << "A";
	return o;// TODO: insertar una instrucción return aquí
}

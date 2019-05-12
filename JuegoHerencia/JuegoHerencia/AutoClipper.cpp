#include "AutoClipper.h"
#include <fstream>
#include <sstream>
//#include <iostream>

using namespace std;


AutoClipper::AutoClipper() :Pieza()
{
	float SetUPaporte[] = { 10,20,30,40,50,60,70,80,90,100 };
	float SetUpconsumo[] = { 10,9,8,7,6,5,4,3,2,1 };
	float SetUpcoste[]= { 10,20,40,80,90,100,110,30,100 };

	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = SetUPaporte[i];
		consumo[i] = SetUpconsumo[i];
		coste[i] = SetUpcoste[i];
	}

	level = 0;
	
	tipo = 1;
}

ostream & AutoClipper::print(ostream & o)
{
	o << "A";
	return o;// TODO: insertar una instrucción return aquí
}

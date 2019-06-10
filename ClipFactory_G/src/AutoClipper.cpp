#include "AutoClipper.h"
#include <fstream>
#include <sstream>
//#include <iostream>

using namespace std;


AutoClipper::AutoClipper() :Pieza()
{
	float SetUPaporte[] = { 500,1000,1500,2000,2500,3000,3700,4300,4900,5500 };
	float SetUpconsumo[] = { 10, 11, 13, 15, 20, 26, 30, 36, 41, 47 };
	float SetUpcoste[] = { 10, 20, 40, 80, 90, 100, 110, 300, 100 };
	float SetUpConsumoAlambre[] = { 10, 11, 13, 15, 20, 26, 30, 36, 41, 47 };

	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = SetUPaporte[i];
		consumo[i] = SetUpconsumo[i];
		coste[i] = SetUpcoste[i];
		ConsumoAlambre[i] = SetUpConsumoAlambre[i];
	}

	level = 0;

	tipo = 1;
}

ostream & AutoClipper::print(ostream & o)
{
	o << "A";
	return o;// TODO: insertar una instrucci�n return aqu�
}

float AutoClipper::get_consumo_alambre()
{
	return ConsumoAlambre[level];
}
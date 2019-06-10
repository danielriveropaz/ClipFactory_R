#include "Marketing.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


Marketing::Marketing() :Pieza()
{
	float SetUPaporte[] = { 0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10 };
	float SetUpconsumo[] = { 10,9,8,7,6,5,4,3,2,1 };
	float SetUpcoste[] = { 10, 30,40,55,69,79,59,49,86,10 };

	for (int i = 0; i < TOP_LEVEL; i++)
	{
		aporte[i] = SetUPaporte[i];
		consumo[i] = SetUpconsumo[i];
		coste[i] = SetUpcoste[i];
	}

	tipo = 2;

}


Marketing::~Marketing()
{
}

ostream & Marketing::print(ostream & o)
{
	o << "M";
	return o;// TODO: insertar una instrucción return aquí
}

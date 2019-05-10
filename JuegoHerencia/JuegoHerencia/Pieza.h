#pragma once
#define TOP_LEVEL 10 //VER POSIBILIDAD DE CONST....
#include <iostream>


class Pieza
{
protected:

	int level; //alamacena el nivel en el que se encuentra la maquina
	float aporte[TOP_LEVEL]; //hay que cambiarlo para cada objeto, aqui se consulta por ejemplo cuanto dinero aporta en el nivel X
	float consumo[TOP_LEVEL]; //hay que cambiarlo para cada objeto, aqui se consulta por ejemplo cuanto dinero consume en el nivel X
	int coste;
	int tipo; //1-->AutoClipper, 2-->Marketing, 3-->trefiladora

public:
	//Pieza(float V_aporte[TOP_LEVEL], float V_consumo[TOP_LEVEL]);
	Pieza();
	Pieza(int a); //Esto cuando este por punteros no seria necesario, se pondria nullptr
	~Pieza();

//metodos
	float get_aporte(); //devuelve cuanto aporta la maquina durante su funcionamiento. 
	float get_consumo(); //devuelve lo que necesita para funcionar.
	int get_type(); //devuelve el tipo de maquina, lo rellena el constructor de los hijos
	virtual std::ostream& print(std::ostream& o = std::cout);
};




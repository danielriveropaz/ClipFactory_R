#pragma once
#include "Pieza.h"

class Trefiladora :public Pieza
{
	//Trefiladora aporta-- > Aalambre;
	//Trefiladora consume-- > Dinero;

public:
	Trefiladora();
	~Trefiladora();

	std::ostream& print(std::ostream& o = std::cout);

};


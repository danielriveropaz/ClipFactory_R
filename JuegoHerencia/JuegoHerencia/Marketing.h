#pragma once
#include "Pieza.h"

class Marketing: public Pieza
{
	//Marketing aporta--> sube el valor de venta de los clips
	//Marketing consume--> Dinero

public:
	Marketing();
	~Marketing();

	std::ostream& print(std::ostream& o = std::cout);

};


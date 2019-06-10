#pragma once
#include "Pieza.h"
#include <iostream>



class AutoClipper : public Pieza {

	//El autoclipper aporta --> clips 
	//El autoclipper consume --> alambre
	float ConsumoAlambre[TOP_LEVEL];

public:
	AutoClipper();
	float get_consumo_alambre();
	std::ostream& print(std::ostream& o = std::cout);

};

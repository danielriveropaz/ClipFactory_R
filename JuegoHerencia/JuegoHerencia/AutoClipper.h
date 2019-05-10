#include "Pieza.h"
#include <iostream>



class AutoClipper : public Pieza  {

	//El autoclipper aporta --> clips 
	//El autoclipper consume --> alambre

public:
	AutoClipper();


	std::ostream& print(std::ostream& o = std::cout);
	
};


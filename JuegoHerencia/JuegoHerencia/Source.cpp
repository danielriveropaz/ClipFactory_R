#include "Fabrica.h"
#include "Pieza.h"

#include "AutoClipper.h"
#include "Marketing.h"
#include "Trefiladora.h"

#include <iostream>
#include <stdlib.h>


using namespace std;



int main()
{
	
	
	/*F.new_maquina(1, 0, 0);
	F.new_maquina(1, 0, 1);
	F.new_maquina(3, 0, 2);
	F.new_maquina(1, 0, 3);
	F.print();
	
	cout << endl;
	cout << F.getLevel(0, 0);

	cout << endl;
	cout << F.getCoste(0, 0);*/

	Fabrica F;
	F.new_maquina(Fabrica::Autoclipper_M, 0, 0);
	F.new_maquina(Fabrica::Marketing_M, 1, 0);
	F.new_maquina(Fabrica::Trefiladora_M, 2, 0);

	for (int i = 1; i > 0; i++) {
		system("cls");
		F.UpdateFabric();
		F.print();
		F.imprimirEstado();
		cout << i<<endl;
		F.control();
		//F.new_maquina(Fabrica::Autoclipper_M, 0, i);
	}
	system ("pause");
	return 0;


}


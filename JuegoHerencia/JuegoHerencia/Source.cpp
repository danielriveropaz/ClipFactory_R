#include "Fabrica.h"
#include "Pieza.h"

#include "AutoClipper.h"
#include "Marketing.h"
#include "Trefiladora.h"

#include <iostream>

using namespace std;



int main()
{
	Fabrica F;
	//F.UpdateFabric();+
	//AutoClipper A, B, C, D;
	//Marketing E, M, G, H;
	//Trefiladora I, J, K, L;
	//Marketing M;
	//Trefiladora T;
	//T.print();
	//F.new_maquina(1, &A, 2, 3); F.new_maquina(1, &B, 0, 0); F.new_maquina(1, &C, 4, 3); F.new_maquina(1, &D, 1, 1);
	//F.new_maquina(2, &E, 2, 2); F.new_maquina(2, &M, 2, 0); F.new_maquina(2, &G, 1, 3); F.new_maquina(2, &H, 2, 4);
	//F.new_maquina(3, &I, 3, 3); F.new_maquina(3, &J, 4, 4); F.new_maquina(3, &K, 1, 2); F.new_maquina(3, &L, 0, 1);
	
	F.new_maquina(2, 0, 0);
	F.new_maquina(1, 0, 1);
	F.new_maquina(3, 0, 2);
	F.new_maquina(1, 0, 3);
	F.print();


	system ("pause");
	return 0;


}


//Ejemplo Maurisio
/*
int main() {
	DynamicMatrix<int> matriz(10, 15);
	for (int i = 0; i < matriz.getRows(); i++) {
		for (int j = 0; j < matriz.getColumns(); j++) {
			matriz.setValue(i, j, i + j);
		}
	}
	for (int i = 0; i < matriz.getRows(); i++) {
		for (int j = 0; j < matriz.getColumns(); j++) {
			cout << matriz.getValue(i, j) << "\t";
		}
		cout << endl;
	}
	return 0;
}*/
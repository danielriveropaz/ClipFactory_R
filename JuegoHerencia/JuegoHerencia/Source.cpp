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
	AutoClipper A;
	Marketing M;
	Trefiladora T;
	//T.print();

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
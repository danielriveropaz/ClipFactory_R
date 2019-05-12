#include "Fabrica.h"
#include "Pieza.h"
#include "AutoClipper.h"
#include "Marketing.h"
#include "Trefiladora.h"
#include <fstream>
#include <sstream>
#include <iostream>



using namespace std;

Fabrica::Fabrica()
{
	fondos = 1000; //Se podria poner modos de juego, facil, dificil, etc etc donde cambiemos el capital inicial.
	produccion = 0;
	precio = 0;
	gasto = 0;
	beneficios = 0;

	ConsumoAlambre = 0;
	ConsumoDinero = 0;
	ProdAlambre = 0;

	nFilas = 5;
	nColumnas = 5;

	M = lightsOn(nFilas, nColumnas);

	for (int i = 0; i < nFilas; i++)
	{
		for (int j = 0; j < nColumnas; j++)
		{
			M[i][j] = NULL; 
		}

	}

}

bool Fabrica::UpdateFabric()
{
	//Esta funcion escanea la matriz de la fabrica, viendo que maquinas hay y suma los aportes y consumos de cada una.
	ConsumoAlambre = 0;
	ConsumoDinero = 0;
	ProdAlambre = 0;
	precio = 0;
	produccion = 0;

	//Esto se podria meter en otro metodo para facilitar lectura.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			switch (M[i][j]->get_type()) {

			case Autoclipper_M: //Aporta dinero, consume alambre
				ConsumoAlambre += M[i][j]->get_consumo(); //Esto nos da cuanto alambre/segundo necesitamos, si lo tenemos produciremos, sino iremos perdiendo capacidad de produccion
				//tambien podriamos ir apagando las maquinas de menor nivel y marcarlas en rojo o algo, se puede cambiar la funcion si lo vemos guay
				produccion += int(M[i][j]->get_aporte());
				break;
			case Marketing_M:
				ConsumoDinero += M[i][j]->get_consumo();
				precio += M[i][j]->get_aporte();

				break;
			case Trefiladora_M:
				ConsumoDinero += M[i][j]->get_consumo();
				ProdAlambre += M[i][j]->get_aporte();
				break;

			}

		}

	}

	//Comprobamos si podemos produccir al 100%
	//Ahora que tenemos todos los consumos podemos saber a que capacidad podemos producir
	//Empezamos por las cosas que consumen dinero, si no las puedes pagar estas OUT.

	fondos = fondos - ConsumoDinero; // consumo de dinero por ciclo, si lo restamos en cada ciclo a fondos pues es dinero-dinero
	if (fondos < 0)
	{
		//Pierdes, estas en la bancarrota. 
		return 0;
	}

	//Si no estas en la bancarrota, actualizamos los autoclippers.

	float ocupacion = ProdAlambre / ConsumoAlambre;
	produccion = int(produccion * ocupacion); //actualizamos la produccion de las maquinas en funcion de si pueden trabajar al 100 o no.

	//Una vez tenemos la produccion de clips de este ciclo, los vendemos.
	fondos += precio * produccion;



}


Pieza *** Fabrica::lightsOn(int nFilas, int nColumnas) { //Crea la matriz base para guardar cada objeto de la fabrica

	Pieza ***puntero_matriz;
	puntero_matriz = new Pieza**[nFilas]; //reserva de memoria para las filas
	for (int i = 0; i < nFilas; i++) {
		puntero_matriz[i] = new Pieza*[nColumnas]; //reserva de memoria para columnas por cada fila

	}

	/*cout << "\nDigitando elementos de la matriz:\n";
	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			cout << "Introduzca un numero [" << i + 1 << "][" << j + 1 << "]: ";
			cin >> *(*(puntero_matriz + i) + j);
		}

	}*/

	return puntero_matriz;

}

Pieza* Fabrica::getValue(int pRow, int pColumn) {
	if (pRow < 0 || pRow >= nFilas) {
		//throw runtime_error("Invalid row.");
	}
	if (pColumn < 0 || pColumn >= nColumnas) {
		//throw runtime_error("Invalid column.");
	}
	return M[pRow][pColumn];
}

ostream& Fabrica::print(ostream& o) {
	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			//o << static_cast<int>(M[i][j]) << " ";
			//cout << ".";
			cout << "| ";
			if (M[i][j] != NULL) {
				
				M[i][j]->print();

			}
			else {
				cout << " ";
			}
			cout << " |\t";
			
		}
		o << endl;
		o << endl;
	}

	return o;
}

int Fabrica::new_maquina(int tipo, int F, int C)
{
	
	AutoClipper J_aux;
	Marketing M_aux;
	Trefiladora T_aux;

	switch (tipo) {

	case Autoclipper_M:
		M[F][C] = new AutoClipper;
		*M[F][C] = J_aux;
		break;

	case Marketing_M:
		M[F][C] = new Marketing;
		*M[F][C] = M_aux;
		//*M[F][C] = H;
		break;
	case Trefiladora_M:
		M[F][C] = new Trefiladora;
		*M[F][C] = T_aux;
		break;
		return 0;//Si devuelve 0 todo ha ido mal, a los McCoy le pasan estas cosas de cuando en cuando.
	}
	//M[F][C] = pp;
	//return 0;
}







Fabrica::~Fabrica()
{
}



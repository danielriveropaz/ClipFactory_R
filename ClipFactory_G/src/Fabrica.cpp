#include "Fabrica.h"
#include "Pieza.h"
#include "AutoClipper.h"
#include "Marketing.h"
#include "Trefiladora.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <regex>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <vector>



using namespace std;

Fabrica::Fabrica()
{
	fondos = 1000; //Se podria poner modos de juego, facil, dificil, etc etc donde cambiemos el capital inicial.
	produccion = 0;//numero de clips por ciclo
	precio = 0;
	gasto = 0;
	beneficios = 0;

	dias = 0;

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

	//pruebas, para ver cómo se dibujan...
	//new_maquina(1, 0, 1); new_maquina(2, 1, 1); new_maquina(3, 1, 0); new_maquina(1, 2, 2); 

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
	for (int i = 0; i < nFilas; i++)
	{
		for (int j = 0; j < nColumnas; j++)
		{
			if (M[i][j] != NULL) {

				switch (M[i][j]->get_type()) {

				case Autoclipper_M: //Aporta dinero, consume alambre
					ConsumoAlambre += M[i][j]->get_consumo_alambre(); //Esto nos da cuanto alambre/segundo necesitamos, si lo tenemos produciremos, sino iremos perdiendo capacidad de produccion
					//tambien podriamos ir apagando las maquinas de menor nivel y marcarlas en rojo o algo, se puede cambiar la funcion si lo vemos guay
					produccion += M[i][j]->get_aporte();
					ConsumoDinero += M[i][j]->get_consumo();
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

	if (ocupacion >= 1) //las maquinas no pueden trabajar a mas del 100%
		ocupacion = 1;


	produccion = int(produccion * ocupacion); //actualizamos la produccion de las maquinas en funcion de si pueden trabajar al 100 o no.

	//Una vez tenemos la produccion de clips de este ciclo, los vendemos.
	fondos += precio * produccion;


	return 1;//todo correcto
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

ostream& Fabrica::print(ostream& o, bool fichero) {
	for (int i = 0; i < nFilas; i++) {
		for (int j = 0; j < nColumnas; j++) {
			if (!fichero)
				cout << "| ";


			if (M[i][j] != NULL) {

				M[i][j]->print(o);
				o << M[i][j]->getLevel();


			}
			else {
				o << "-";
			}
			if (!fichero)
				cout << " |\t";
			else
				o << ';';
		}
		o << endl;

		if (!fichero)
			cout << endl;
	}

	return o;
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

int Fabrica::getnFilas() { return nFilas; }

int Fabrica::getnColumnas() { return nColumnas; }

float Fabrica::getFondos() { return fondos; }

int Fabrica::getProduccion() { return produccion; }

float Fabrica::getPrecio() { return precio; }

float Fabrica::getProduccionAlambre() { return ProdAlambre; }

float Fabrica::getConsumoAlambre() { return ConsumoAlambre; }

float Fabrica::getConsumoDinero() { return ConsumoDinero; }

float Fabrica::getGastos() { return gasto; }

float Fabrica::getBeneficio() { return beneficios; }

int Fabrica::getDias() { return dias; }


void Fabrica::CambiaTamaño(int F, int C) {  //F y C son las filas y columnas QUE SE AÑADEN.
	//NOTA: SOLO SE CONSIDERAN POSIBLES LAS AMPLIACIONES
	//Maximo 20 filas y 20 columnas, de momento, si metemos más, hay que programar que se pueda mover la cámara, 
	//y dejarla más cerca, si no no se ve nada...
	int numeroespacios = 2 * nFilas + 1;
	float coste = 100.0 * numeroespacios;
		if ((F < 0 || C < 0) || (nFilas >= 20 || nColumnas >= 20)) {}
		else
		{
			//nuevo puntero a una matriz N auxiliar, para guardar los datos mientras se crea una nueva matriz.
			Pieza *** N = lightsOn(nFilas, nColumnas);
			for (int i = 0; i < nFilas; i++)
			{
				for (int j = 0; j < nColumnas; j++)
				{
					N[i][j] = M[i][j];
				}
			}
			//puntero a nueva matriz M, inicialmente, ponemos todo a NULL, y despues pasamos los datos de N a M.

			M = lightsOn(nFilas + F, nColumnas + C);

			for (int i = 0; i < nFilas + F; i++)
			{
				for (int j = 0; j < nColumnas + C; j++)
				{
					M[i][j] = NULL;
				}
			}

			for (int i = 0; i < nFilas; i++)
			{
				for (int j = 0; j < nColumnas; j++)
				{
					M[i][j] = N[i][j];
				}
			}


			//nuevas filas y columnas.
			nFilas = nFilas + F;
			nColumnas = nColumnas + C;
			fondos = fondos - coste;
	}
}

int Fabrica::new_maquina(int tipo, int F, int C)
{

	if (F > nFilas || C > nColumnas)
		return 1;

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
	}

	fondos = fondos - M[F][C]->getCoste(); //gasto incial de la maquina
	return 0;//Si devuelve 0 todo ha ido mal, a los McCoy le pasan estas cosas de cuando en cuando.


}

int Fabrica::getLevel(int F, int C) {
	return M[F][C]->getLevel();
}

float Fabrica::getCoste(int F, int C) {
	return M[F][C]->getCoste();
}


int Fabrica::UpdateMachine(int F, int C) {

	M[F][C]->UpdateLevel();
	fondos = fondos - M[F][C]->getCoste();
	return 1; //todo ok

}

void Fabrica::imprimirEstado()
{
	cout << "Fondos: " << fondos << endl;
	cout << "Produccion: " << produccion << endl;
	cout << "Precio: " << precio << endl;
	cout << "Produccion alambre: " << ProdAlambre << endl;
	cout << "Consumo alambre: " << ConsumoAlambre << endl;
	cout << "Consumo dinero: " << ConsumoDinero << endl;
	cout << "Gastos: " << gasto << endl;
	cout << "Beneficios: " << beneficios << endl;
	cout << "Dias transcurridos: " << dias << endl;


}

void Fabrica::control()
{
	char opcion;
	int fila, columna;
	//cin >> opcion;
	opcion = std::cin.get();
	if (opcion == 'n')
	{
		cin >> opcion;
		switch (opcion) {
		case 'a':
			cout << "Escriba la fila de la nueva maquina:";
			cin >> fila;
			cout << "Escriba la columna de la nueva maquina:";
			cin >> columna;

			new_maquina(Autoclipper_M, fila, columna);
			break;


		case 'm':
			cout << "Escriba la fila de la nueva maquina:";
			cin >> fila;
			cout << "Escriba la columna de la nueva maquina:";
			cin >> columna;

			new_maquina(Marketing_M, fila, columna);
			break;


		case 't':
			cout << "Escriba la fila de la nueva maquina:";
			cin >> fila;
			cout << "Escriba la columna de la nueva maquina:";
			cin >> columna;

			new_maquina(Trefiladora_M, fila, columna);
			break;


		}


	}
	else if (opcion == '\n') {
		system("pause");
	}
	else if (opcion == 'l') {

		cout << "Escriba la fila de la maquina a la que quiere subir el nivel: ";
		cin >> fila;
		cout << "Escriba la columnade la maquina a la que quiere subir el nivel: ";
		cin >> columna;
		if (UpdateMachine(fila, columna)) cout << "El nivel se ha subido correctamente";
		else {
			cout << "El nivel no se ha subido correctamente";
		}

	}

	else {
		system("pause");
	}

}



int Fabrica::update_dias()
{
	dias++;
	SaveGame();
	return 1; //todo ha ido bien. 
}





Fabrica::~Fabrica()
{
}


/*

int Fabrica::LoadGame(string name, Fabrica FA)
{
	ifstream myFile;
	myFile.open(name);

	int i = 0;
	int j = 0;

	while (myFile.good())
	{
		char tipo;
		int level;
		string line;

		getline(myFile, line, ';');
		const char* contenido = line.c_str();
		sprintf((char*)contenido, "%c%d ", tipo, level);

		j++;
		if (j > 3) {
			i++;
			j = 0;
		}
	}

}

*/

int Fabrica::SaveGame() {

	ofstream fs("SavedGame.csv");

	print(fs, true);

	fs << 'f' << ';' << fondos << endl;
	fs << 'd' << ';' << dias << endl;

	cout << "JuegoGuardado" << endl;
	fs.close();
	return 1;
}

int Fabrica::LoadGame(std::string name)
{

	ifstream myFile;
	myFile.open(name);

	int level = 0;
	char machine = NULL;

	while (myFile.good())
	{

		string line;
		string s;
		std::vector<std::vector<std::string> > values;
		bool dentromatriz = true;
		int filas = 0;
		int columnas = 0;
		int level = 0;

		while (getline(myFile, line))
		{
			std::string line_value;
			std::vector<std::string> line_values;
			std::stringstream ss(line);

			while (std::getline(ss, line_value, ';'))
			{

				switch (line_value[0])
				{
				case 'A':
					cout << "A en: " << filas << columnas << " nivel :" << line_value[1] << endl;
					new_maquina(Autoclipper_M, filas, columnas);
					//level = (int)stod(line_value);
					for (int i = 0; i <= level; i++) {
						M[filas][columnas]->UpdateLevel();
					}
					break;
				case 'M':
					cout << "M en: " << filas << columnas << " nivel :" << line_value[1] << endl;
					new_maquina(Marketing_M, filas, columnas);
					break;
				case 'T':
					cout << "T en: " << filas << columnas << " nivel :" << line_value[1] << endl;
					new_maquina(Trefiladora_M, filas, columnas);
					break;
				case 'f':
					std::getline(ss, line_value, ';');
					cout << "Fondos: " << line_value << endl;
					fondos = stod(line_value);
					dentromatriz = 0;

					break;
				case 'd':
					std::getline(ss, line_value, ';');
					cout << "Dias Transcurridos: " << line_value << endl;
					dias = (int)stod(line_value);
					dentromatriz = 0;
					break;
				}
				if (dentromatriz)
					columnas++;
			}
			if (dentromatriz)
			{
				columnas = 0;
				filas++;
			}

		}

	}

	return 0;
}
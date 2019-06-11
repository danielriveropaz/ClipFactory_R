#pragma once
#include "Pieza.h"

//Tipos de datos
enum Maquinas { Autoclipper_M = 1, Marketing_M, Trefiladora_M };

class Fabrica
{
private:
	//datos mostrados al usuario
	float fondos; //fondos totales.
	float produccion; //produccion de clip por segundo.
	float precio; //precio de venta de los clips
	int dias;

	//datos para nuestros calculos internos
	float ProdAlambre; //Alambre producido por segundo
	float ConsumoAlambre;

	float ConsumoDinero; //Cuanto dinero necesitamos por ciclo.

	float gasto; //gasto por segundo total de la fabrica.
	float Ingresos; //beneficio por segundo que produce la fabrica. //Como lo voy añadiendo todo a los fondos pues no lo calculo, habria que añadir una auxiliar que sea fondos/ciclo para poder calcularla, o sino borrarla jajaja

	int nFilas, nColumnas;

	//matriz de piezas. Esta matriz es el estado de nuestra partida, que maquinas tenemos donde y en que nivel.

	Pieza *** M; //Estaria bien cambiarlo a memoria dinamica sobretodo si luego queremos ampliar la fabrica



public:
	Fabrica(); //deberia reservar memoria para el vector e igualarlo a NULL
	~Fabrica();


	//metodos
	bool UpdateFabric(); //actualiza los fondos, el precio y la produccion en funcion de las piezas y su nivel. Devuelve 1 si todo va bien o un 0 si estamos en numeros rojos.
	Pieza ***lightsOn(int nFilas, int nColumnas);

	//Pieza* getValue(int pRow, int pColumn); por qué no?

	Pieza* getValue(int pRow, int pColumn);
	std::ostream& print(std::ostream& o = std::cout, bool fichero = false);
	int new_maquina(int tipo, int F, int C);
	int getLevel(int F, int C); //devuelve el nivel de la maquina que esta en la casilla [F] [C]
	float getCoste(int F, int C);//devuelve el coste de la maquina, ya sea precio inicial si esta el nivel a 0 o de actualizacion si es superior. 
	int getnFilas();
	int getnColumnas();
	float getFondos();
	int getProduccion();
	float getPrecio();
	float getProduccionAlambre();
	float getConsumoAlambre();
	float getConsumoDinero();
	float getIngresos();
	int getDias();
	int UpdateMachine(int F, int C); //aumenta el nivel y cobra el precio 
	void imprimirEstado();
	void control();
	int update_dias();
	void CambiaTamaño(int F, int C);

	//guardar y cargar juego
	int SaveGame();
	//int LoadGame(string name, Fabrica FA);
	int LoadGame(std::string name);



};

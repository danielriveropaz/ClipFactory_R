#pragma once
#include "Pieza.h"
class Fabrica
{
	//datos mostrados al usuario
	float fondos; //fondos totales.
	int produccion; //produccion de clip por segundo.
	float precio; //precio de venta de los clips

	//datos para nuestros calculos internos
	float ProdAlambre; //Alambre producido por segundo
	float ConsumoAlambre;

	float ConsumoDinero; //Cuanto dinero necesitamos por ciclo.

	float gasto; //gasto por segundo total de la fabrica.
	float beneficios; //beneficio por segundo que produce la fabrica. //Como lo voy añadiendo todo a los fondos pues no lo calculo, habria que añadir una auxiliar que sea fondos/ciclo para poder calcularla, o sino borrarla jajaja


	//matriz de piezas. Esta matriz es el estado de nuestra partida, que maquinas tenemos donde y en que nivel.

	Pieza M[5][5]; //Estaria bien cambiarlo a memoria dinamica sobretodo si luego queremos ampliar la fabrica

	//Tipos de datos
	enum Maquinas {Autoclipper_M =1, Marketing_M, Trefiladora_M};


public:
	Fabrica(); //deberia reservar memoria para el vector e igualarlo a NULL
	~Fabrica();

//metodos
	bool UpdateFabric(); //actualiza los fondos, el precio y la produccion en funcion de las piezas y su nivel. Devuelve 1 si todo va bien o un 0 si estamos en numeros rojos.


	
};


#include "Fabrica.h"

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



	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			M[i][j] = Pieza(0);
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
			switch (M[i][j].get_type()) {

			case Autoclipper_M: //Aporta dinero, consume alambre
				ConsumoAlambre += M[i][j].get_consumo(); //Esto nos da cuanto alambre/segundo necesitamos, si lo tenemos produciremos, sino iremos perdiendo capacidad de produccion
				//tambien podriamos ir apagando las maquinas de menor nivel y marcarlas en rojo o algo, se puede cambiar la funcion si lo vemos guay
				produccion += int(M[i][j].get_aporte());
				break;
			case Marketing_M:
				ConsumoDinero += M[i][j].get_consumo();
				precio += M[i][j].get_aporte();

				break;
			case Trefiladora_M:
				ConsumoDinero += M[i][j].get_consumo();
				ProdAlambre += M[i][j].get_aporte();
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




Fabrica::~Fabrica()
{
}

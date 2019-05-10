/*

//Por lo tanto, el nombre de la matriz no va a ser simplemente un puntero hacia elementos, si no que es un puntero hacia un arreglo de punteros,
//lo que significa que hay que declararlo como un puntero hacia un puntero.Esta l�gica puede extenderse a cualquier cantidad de dimensiones.

//La matriz del diagrama anterior la podemos ver como una matriz de 5 filas por 7 columnas.El asunto es que tanto los arreglos con los elementos
//como el arreglo de punteros van a existir en memoria din�mica, por lo que hay que solicitar la memoria respectiva.

int **arreglo = new int*[5];
for (int i = 0; i < 7; i++) {
	arreglo[i] = new int[7];
}

//Primero se solicita memoria para el arreglo de punteros y luego se solicita la memoria para cada una de las filas de la matriz.
//En el ejemplo anterior, las dimensiones est�n fijas en el c�digo, pero estos valores pueden ser variables dado que se est� declarando todo en memoria din�mica.
//Entonces, volviendo a nuestra intenci�n original, puede hacerse algo como lo siguiente.

int m, n;
cin >> m >> n;
int **arreglo = new int*[m];
for (int i = 0; i < m; i++) {
	arreglo[i] = new int[n];
}

//Es importante recalcar que, cuando se solicita memoria din�mica, �sta no se encuentra inicializada,
//por lo que los valores almacenados son indeterminados y podr�amos obtener cualquier valor.

//Despu�s de esa declaraci�n es posible acceder a los elementos de la matriz mediante dos �ndices, uno para seleccionar la "fila" y otro para la "columna".
//Si quisi�ramos asignar un valor inicial de cero a todos los elementos de la matriz anterior, debe hacerse algo as�:

for (int i = 0; i < m; i++) {
	for (int j = 0; j < n; j++) {
		arreglo[i][j] = 0;
	}
}*/

//A continuaci�n se encuentra el c�digo de una clase gen�rica que encapsula el funcionamiento de una matriz bidimensional.
//El constructor recibe como par�metro las dimensiones y solicita la memoria necesaria.El destructor se encarga de liberar la memoria din�mica solicitada.
//Se incluyen m�todos para asignar un valor a una celda, obtener el valor de una celda, y para obtener la cantidad de filas y columnas.Posteriormente se muestra un ejemplo de utilizaci�n de la clase.

/*
template <typename E>
class DynamicMatrix
{
private:
	int rows;
	int columns;
	E** matrix;

public:
	DynamicMatrix(int pRows, int pColumns) throw(runtime_error) {
		if (pRows <= 0 || pColumns <= 0) {
			throw runtime_error("Number of rows and columns must be greater than zero.");
		}
		rows = pRows;
		columns = pColumns;
		matrix = new E*[rows];
		for (int i = 0; i < rows; i++) {
			matrix[i] = new E[columns];
		}
	}

	~DynamicMatrix() {
		for (int i = 0; i < rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	E getValue(int pRow, int pColumn) throw(runtime_error) {
		if (pRow < 0 || pRow >= rows) {
			throw runtime_error("Invalid row.");
		}
		if (pColumn < 0 || pColumn >= columns) {
			throw runtime_error("Invalid column.");
		}
		return matrix[pRow][pColumn];
	}

	void setValue(int pRow, int pColumn, E value) throw(runtime_error) {
		if (pRow < 0 || pRow >= rows) {
			throw runtime_error("Invalid row.");
		}
		if (pColumn < 0 || pColumn >= columns) {
			throw runtime_error("Invalid column.");
		}
		matrix[pRow][pColumn] = value;
	}
	int getRows() {
		return rows;
	}
	int getColumns() {
		return columns;
	}
};


//Ejemplo de uso de la clase.El primer ciclo llena la matriz con valores crecientes y el segundo lo imprime en consola.

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
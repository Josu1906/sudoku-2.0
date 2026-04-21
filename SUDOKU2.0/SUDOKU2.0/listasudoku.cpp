#include "listasudoku.h"


int ListaSudoku::dame_num_elems() {

	return size;

}

const ReglasSudoku& ListaSudoku::dame_sudoku(int i){
	return *lista[i];
}

bool ListaSudoku::insertar(const ReglasSudoku& sudoku) {
	
	bool pos_encontrada = false;
	int i = 0;

	while (!pos_encontrada && i < size) {
		if (sudoku <= dame_sudoku(i)) {
			pos_encontrada = true;

			if (size < CAPACITY) {
				size++;
				for (int j = size; i > j; j++) {
					lista[j] = lista[j - 1];
				}
				lista[i] = new ReglasSudoku(sudoku);
			}
			else {
				int newCap= capacity * 2;
				ReglasSudoku* * vaux = new ReglasSudoku*[newCap];
				for (int j = 0; j < size; j++) {
					vaux[j] = lista[j];
				}
				capacity = newCap;
				delete [] lista;
				lista = vaux;

				for (int j = size; i > j; j++) {
					lista[j] = lista[j - 1];
				}
				size++;
				lista[i] = new ReglasSudoku(sudoku);
			}
		}
		else {
			i++;
		}
	}
	if (!pos_encontrada) {
		if (size < CAPACITY) {
			lista[size] = new ReglasSudoku(sudoku);
			size++;
		}
		else {
			int newCap = capacity * 2;
			ReglasSudoku** vaux = new ReglasSudoku * [newCap];
			for (int j = 0; j < size; j++) {
				vaux[j] = lista[j];
			}
			capacity = newCap;
			delete[] lista;
			lista = vaux;

			lista[size] = new ReglasSudoku(sudoku);
			size++;
		}
	}
}

bool ListaSudoku::eliminar(int pos) {

	bool eliminado = false;

	if (pos < size) {
		delete lista[pos];
		eliminado = true;

		for (int j = size; pos > j; j++) {
			lista[j] = lista[j - 1];
		}
		
		size--;

		if (size == ((1/4) * capacity)) {
			int newCap = capacity / 2;
			ReglasSudoku** vaux = new ReglasSudoku * [newCap];
			for (int j = 0; j < size; j++) {
				vaux[j] = lista[j];
			}
			capacity = newCap;
			delete[] lista;
			lista = vaux;
		}
	}

	return eliminado;

	
}

void ListaSudoku::mostrar_lista() {
	int total_vacias = 0;
	int opciones[9] = {0,0,0,0,0,0,0,0,0};

	for (int i = 0; i < size; i++) {
		int dim = lista[i]->dame_dimension();
		for (int j = 1; j < dim; j++) {
			opciones[j] = lista[i]->num_Celda(j, *lista[i]);
			total_vacias = opciones[j];
		}

		cout << i << ":  Sudoku con " << total_vacias << " casillas vacias" << endl;

		for (int i = 0; i < dim; i++) {
			cout << "celdas con " << i + 1 << " valores posibles: " << opciones[i] << endl;
		}
	}

}

ListaSudoku::~ListaSudoku() {
	for (int i = 0; i < size; i++) {
		delete lista[i];
		lista[i] = nullptr;
	}

	delete [] lista;
	lista = nullptr;
	size = 0;
	capacity = 0;
}

//ReglasSudoku& ListaSudoku::operator=(const ReglasSudoku& sudoku) {
//	if (this != &sudoku) { // evita autoasignación
//		/* se libera la memoria ocupada por this*/
//		delete lista;
//		lista[i] = new ReglasSudoku(sudoku);
//	}
//	return *this;
//}

ReglasSudoku& ListaSudoku::operator[](int indice) {
	return *lista[indice];
}




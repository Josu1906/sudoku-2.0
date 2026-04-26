#include "listasudoku.h"
#include "reglasudoku.h"




int ListaSudoku::dame_num_elems() {

	return size;

}

const ReglasSudoku& ListaSudoku::dame_sudoku(int i) {
	return *lista[i];
}

bool ListaSudoku::insertar(const ReglasSudoku& sudoku) {

	bool pos_encontrada = false;
	bool insertado = false;
	int i = 0;

	while (!pos_encontrada && i < size) {
		if (sudoku < dame_sudoku(i)) {
			pos_encontrada = true;

			if (size < capacity) {
				for (int j = size; i < j; j--) {
					lista[j] = lista[j - 1];
				}
				lista[i] = new ReglasSudoku(sudoku);
				insertado = true;
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

				for (int j = size; i < j; j--) {
					lista[j] = lista[j - 1];
				}
				size++;
				lista[i] = new ReglasSudoku(sudoku);
				insertado = true;
			}
		}
		else if (sudoku == dame_sudoku(i)){
			if (size < capacity) {
				for (int j = size; i < j; j--) {
					lista[j] = lista[j - 1];
				}
				lista[i] = new ReglasSudoku(sudoku);
				insertado = true;
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

				for (int j = size; i < j; j--) {
					lista[j] = lista[j - 1];
				}
				size++;
				lista[i] = new ReglasSudoku(sudoku);
				insertado = true;
			}
		}
		else {
			i++;
		}
	}
	if (!pos_encontrada) {
		if (size < capacity) {
			lista[size] = new ReglasSudoku(sudoku);
			insertado = true;
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
			insertado = true;
			size++;
		}
	}

	return insertado;
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

int celdas_vacias(int dimension, const ReglasSudoku& s) {
	int cont = 0;

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (s.dame_celda(i, j).es_vacia()) {
				cont++;
			}
		}
	}

	return cont;
}

void ListaSudoku::mostrar_lista() {
	int total_vacias = 0;
	int sudokus[9] = {0,0,0,0,0,0,0,0,0};
	int n_vacias[9] = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < size; i++) {
		int dim = lista[i]->dame_dimension();
		for (int j = 0; j < dim; j++) {
			sudokus[j] = num_Celda(j+1, *lista[i]);
			//cout << sudokus[j] << endl;
		}

		n_vacias[i] = celdas_vacias(dim, *lista[i]);

		cout << ORANGE << i + 1 << RESET << ":  Sudoku con " << ORANGE <<  n_vacias[i] << RESET << " casillas vacias" << endl;

		this_thread::sleep_for(chrono::milliseconds(100));

		for (int j = 0; j < dim; j++) {
			cout << "celdas con "  << ORANGE << j + 1  << RESET << " valores posibles: " << BG_LGREEN  << BLACK << sudokus[j] << RESET << endl;
			this_thread::sleep_for(chrono::milliseconds(60));

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


ReglasSudoku& ListaSudoku::operator[](int indice) {
	return *lista[indice];
}



//ReglasSudoku& ListaSudoku::operator=(const ReglasSudoku& sudoku) {
//	if (this != &sudoku) { // evita autoasignación
//		/* se libera la memoria ocupada por this*/
//		delete lista;
//		lista[i] = new ReglasSudoku(sudoku);
//	}
//	return *this;
//}

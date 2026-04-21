#pragma once
#include <iostream>
#include "reglasudoku.h"

using namespace std;

const int CAPACITY = 5;

class ListaSudoku {
private:
	ReglasSudoku** lista;
	int size;
	int capacity = CAPACITY;

public:

	ListaSudoku() {
		size = 0;
	}

	ReglasSudoku& operator[](int indice);


	int dame_num_elems();
	const ReglasSudoku& dame_sudoku(int i);
	bool insertar(const ReglasSudoku& sudoku);
	bool eliminar(int pos); // elimina el elemento de la posición pos
	void mostrar_lista();
	~ListaSudoku();


};
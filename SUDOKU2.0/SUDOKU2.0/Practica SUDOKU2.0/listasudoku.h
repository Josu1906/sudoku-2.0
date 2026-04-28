#pragma once
#include <iostream>
#include "reglasudoku.h"
#include <thread>
#include <chrono>
#include "colors.h"
#include <string>

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
		lista = new ReglasSudoku*[capacity];
	}

	ReglasSudoku& operator[](int indice);


	int dame_num_elems();
	const ReglasSudoku& dame_sudoku(int i);
	bool insertar(const ReglasSudoku& sudoku);
	bool eliminar(int pos); // elimina el elemento de la posición pos
	void mostrar_lista();
	~ListaSudoku();


};
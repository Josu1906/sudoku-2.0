#pragma once
#include <iostream>
#include <string>
#include "celda.h"

using namespace std;

const int DIM_MAX = 20;

class Tablero {

private:
	int dim;
	tCelda tablero[DIM_MAX][DIM_MAX];


public:

	Tablero(int dimm) {
		dim = dimm;
	}

	int dimension();
	tCelda get_celda(int f, int c);
	bool set_valor(int f, int c, int v, string estado);
};

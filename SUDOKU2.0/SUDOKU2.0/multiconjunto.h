#pragma once
#include <iostream>
#include "tablero.h"

using namespace std;

typedef struct {
	int v;
	int multiplicidad;
} tStructMulti;

typedef tStructMulti tListaMulti[DIM_MAX];

class MultiConjunto {

private:
	tListaMulti lista;

public:

	MultiConjunto() {

		int i = 0;

		for (int i = 0; i < DIM_MAX; i++){
			lista[i].v = 0;
			lista[i].multiplicidad = 0;
		}
	}

	int dame_num_elems() const;

	bool pertenece(int v);

	bool insertar(int v);

	bool eliminar(int v);


};




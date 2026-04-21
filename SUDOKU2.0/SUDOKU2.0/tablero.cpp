#include <iostream>
#include <string>
#include "tablero.h"
#include "celda.h"

using namespace std;

int Tablero::dimension() {

	return this->dim;
}

bool Tablero::set_valor(int f, int c, int v, string estado) {
	bool asignado = false;
	tCelda celda(v);
	if (estado == "ORIGINAL") {
		celda.set_original();
	}
	else if (estado == "OCUPADA") {
		celda.set_ocupada();
	}
	else {
		celda.set_vacia();
	}

	if (f < this->dim && c < this->dim) {
		this->tablero[f][c] = celda;
		asignado = true;
	}

	return asignado;
}

tCelda Tablero::get_celda(int f, int c) {

	return this->tablero[f][c];
}
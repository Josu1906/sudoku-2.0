#include <iostream>
#include <string>
#include "celda.h"

using namespace std;

tCelda::tCelda() {
	this->v = 0;
	this->estado = VACIA;
}

tCelda::tCelda(int v) {
	this->v = v;
	this->estado = OCUPADA;
}

bool tCelda::es_vacia() {
	bool salida = false;
	if (estado == VACIA) {
		salida = true;
	}

	return salida;
}

bool tCelda::es_original() {
	bool salida = false;
	if (estado == ORIGINAL) {
		salida = true;
	}

	return salida;
}

bool tCelda::es_ocupada() {
	bool salida = false;
	if (estado == OCUPADA) {
		salida = true;
	}

	return salida;
}

void tCelda::set_valor(int valor) {
	this->v = valor;
	set_ocupada();
}

void tCelda::set_ocupada() {
	estado = OCUPADA;
}

void tCelda::set_original() {
	estado = ORIGINAL;
}

void tCelda::set_vacia() {
	estado = VACIA;
}

int tCelda::dame_valor() {

	return v;
}
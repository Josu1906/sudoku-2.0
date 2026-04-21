#pragma once
#include <iostream>
#include <string>

using namespace std;

typedef enum {ORIGINAL, OCUPADA, VACIA} tEstado;

class tCelda {
private:
	int v;
	tEstado estado;

public:

	tCelda();
	tCelda(int v);
	/* métodos de consulta */


	bool es_vacia();
	bool es_original();
	bool es_ocupada();
	int dame_valor();
	/* métodos modificadores*/
	void set_valor(int v);
	void set_ocupada();
	void set_original();
	void set_vacia();

};
#pragma once

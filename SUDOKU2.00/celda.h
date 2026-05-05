#pragma once
#include <iostream>
#include <string>

using namespace std;


class tCelda {
private:
	typedef enum {ORIGINAL, OCUPADA, VACIA} tEstado;
	int v;
	tEstado estado;

public:

	tCelda();
	tCelda(int v);
	/* métodos de consulta */


	bool es_vacia() const;
	bool es_original() const;
	bool es_ocupada() const;
	int dame_valor() const;
	/* métodos modificadores*/
	void set_valor(int v);
	void set_ocupada();
	void set_original();
	void set_vacia();

};
#pragma once

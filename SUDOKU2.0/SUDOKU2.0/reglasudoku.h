#pragma once

#include <iostream>
#include "tablero.h"
#include "multiconjunto.h"
#include <string>

using namespace std;

typedef struct {
	int f;
	int c;
} tPosBloqueada;

typedef tPosBloqueada tListaBloqueadas[(DIM_MAX * DIM_MAX)];

typedef struct {
	int cont;
	tListaBloqueadas lista_de_bloqueados;
} tBloqueada;

typedef struct {
	int nFilas;
	int nColumnas;
	MultiConjunto no_validos[DIM_MAX][DIM_MAX];
} tValores_invalidos;


class ReglasSudoku {

private:
	int cont;
	Tablero tablero = Tablero(9);
	tBloqueada pos_bloqueadas;
	tValores_invalidos info_valores_no_validos;
	void block(int nf, int nc);
	void mapeo(int f, int c);
	void unlock(int nf, int nc);

public:


	ReglasSudoku(int dim){
		cont = 0;

		tablero = Tablero(dim);
		this->info_valores_no_validos.nColumnas = dim;
		this->info_valores_no_validos.nFilas = dim;

		pos_bloqueadas.cont = 0;

		for (int i = 0; i < (DIM_MAX * DIM_MAX); i++) {
			pos_bloqueadas.lista_de_bloqueados[i].f = 0;
			pos_bloqueadas.lista_de_bloqueados[i].c = 0;
		}
	}

	ReglasSudoku() {
		cont = 0;

		pos_bloqueadas.cont = 0;

		for (int i = 0; i < (DIM_MAX * DIM_MAX); i++) {
			pos_bloqueadas.lista_de_bloqueados[i].f = 0;
			pos_bloqueadas.lista_de_bloqueados[i].c = 0;
		}
	}

	/* consultoras */
	int dame_dimension();
	tCelda dame_celda(int f, int c);
	bool terminado();
	bool bloqueo();
	int dame_num_celdas_bloqueadas();
	tCelda dame_celda_bloqueada(int p, int& f, int& c);
	bool es_valor_posible(int f, int c, int v);
	//int num_Celda(int k, ReglasSudoku sudoku1);

	/* modificadoras */
	bool pon_valor(int f, int c, int v);
	bool quita_valor(int f, int c);
	void reset();
	void autocompletar();
	int contBloq(int f, int c);

	/* inicializadora */
	bool carga_sudoku(ifstream& archivo, string arch);
}; 

bool operator<=(ReglasSudoku s1, ReglasSudoku s2);
//ReglasSudoku& operator=(const ReglasSudoku& sudoku);
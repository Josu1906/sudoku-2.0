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

//typedef tPosBloqueada tListaBloqueadas[(DIM_MAX * DIM_MAX)];

typedef struct {
	int cont;
	tPosBloqueada* lista_de_bloqueados[(DIM_MAX * DIM_MAX) / 2];
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
	string ID_SUDOKU;
	void block(int nf, int nc);
	void unlock(int nf, int nc);

public:

	ReglasSudoku& operator=(const ReglasSudoku& sudoku);

	ReglasSudoku(int dim){
		cont = 0;

		this->info_valores_no_validos.nFilas = DIM_MAX;
		this->info_valores_no_validos.nColumnas = DIM_MAX;

		tablero = Tablero(dim);
		this->info_valores_no_validos.nColumnas = dim;
		this->info_valores_no_validos.nFilas = dim;


		pos_bloqueadas.cont = 0;
	}

	ReglasSudoku() {
		cont = 0;


		pos_bloqueadas.cont = 0;

		/*for (int i = 0; i < ((DIM_MAX * DIM_MAX) / 2); i++) {
			this->pos_bloqueadas.lista_de_bloqueados[i] = new tPosBloqueada();
			this->pos_bloqueadas.lista_de_bloqueados[i]->f = 0;
			this->pos_bloqueadas.lista_de_bloqueados[i]->c = 0;
		}*/
	}


	ReglasSudoku(const ReglasSudoku& otro);

	~ReglasSudoku();
	
	/* consultoras */
	int dame_dimension() const;
	tCelda dame_celda(int f, int c) const;
	bool terminado();
	bool bloqueo();
	int dame_num_celdas_bloqueadas();
	tCelda dame_celda_bloqueada(int p, int& f, int& c);
	bool es_valor_posible(int f, int c, int v);
	string dame_ID() const;

	//int num_Celda(int k, ReglasSudoku sudoku1);

	/* modificadoras */
	void set_ID(string id);
	bool pon_valor(int f, int c, int v);
	bool quita_valor(int f, int c);
	void reset();
	void autocompletar();
	int contBloq(int f, int c) const;

	/* inicializadora */
	bool carga_sudoku(ifstream& archivo, string file_name);
}; 

bool operator<(const ReglasSudoku& s1, const ReglasSudoku& s2);
bool operator==(const ReglasSudoku& s1, const ReglasSudoku& s2);
int num_Celda(int k, const ReglasSudoku& sudoku1);

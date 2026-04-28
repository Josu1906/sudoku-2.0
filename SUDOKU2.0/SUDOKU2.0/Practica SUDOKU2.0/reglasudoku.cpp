#include <iostream>
#include <string>
#include <fstream>
#include "tablero.h"
#include "celda.h"
#include "reglasudoku.h"
#include <cmath>

using namespace std;

ReglasSudoku::ReglasSudoku(const ReglasSudoku& otro) {

	this->cont = otro.cont;

	this->ID_SUDOKU = otro.dame_ID();
	this->info_valores_no_validos = otro.info_valores_no_validos;
	this->tablero = otro.tablero;

	// 3. Copiar la lista de posiciones bloqueadas
	this->pos_bloqueadas.cont = otro.pos_bloqueadas.cont;

	for (int i = 0; i < otro.pos_bloqueadas.cont; i++) {
		this->pos_bloqueadas.lista_de_bloqueados[i] = new tPosBloqueada(*otro.pos_bloqueadas.lista_de_bloqueados[i]);
	}

	
}

ReglasSudoku::~ReglasSudoku() {

	// 3. Copiar la lista de posiciones bloqueadas

	for (int i = 0; i < this->pos_bloqueadas.cont; i++) {
		delete this->pos_bloqueadas.lista_de_bloqueados[i];
		this->pos_bloqueadas.lista_de_bloqueados[i] = nullptr;
	}


}

string ReglasSudoku::dame_ID() const {
	return this->ID_SUDOKU;
}

void ReglasSudoku::set_ID(string id) {
	this->ID_SUDOKU = id;
}

int ReglasSudoku::dame_dimension() const {

	return tablero.dimension();
}

tCelda ReglasSudoku::dame_celda(int f, int c) const {

	return this->tablero.get_celda(f, c);
}

bool ReglasSudoku::terminado() {

	int dimension = this->tablero.dimension();
	bool done = false;

	if ((dimension * dimension) == this->cont) {
		done = true;
	}

	return done;
}

int ReglasSudoku::dame_contador() {
	return this->cont;
}

bool ReglasSudoku::bloqueo() {

	bool blocked = false;

	if (this->pos_bloqueadas.cont > 0) {
		blocked = true;
	}

	return blocked;
}

int ReglasSudoku::dame_num_celdas_bloqueadas() {

	return this->pos_bloqueadas.cont;
}

tCelda ReglasSudoku::dame_celda_bloqueada(int p, int& f, int& c) {

	f = this->pos_bloqueadas.lista_de_bloqueados[p]->f;
	c = this->pos_bloqueadas.lista_de_bloqueados[p]->c;

	return this->tablero.get_celda(f, c);
}

bool ReglasSudoku::es_valor_posible(int f, int c, int v) {


	// primero para ver si el valor es posible, nos declaramos las variables fundamentales (direcciones del recorritdo, la dimension, si esta repetido y si es admitido o no)

	int dimension = this->tablero.dimension();
	bool es_posible = false;
	int k = 0;
	int nro_elms = this->info_valores_no_validos.no_validos[f][c].dame_num_elems();


	if (v > 0 && v <= dimension && this->tablero.get_celda(f, c).es_vacia()) { // se añade un campo de verificacion, que comprueba si el valor que se esta añadiendo esta dentro del rango posible y la celda en que se esta añadiendo esta vacia (no puede estar ni en estado original o ocupado)

			// en base al estado que debe de tener actualizado de las celdas de su alrededor, analiza si el valor que quieres poner pertenece a los valores no validos
			if (!this->info_valores_no_validos.no_validos[f][c].pertenece(v)) {
				es_posible = true;
			}

	}

	return es_posible;
}

bool ReglasSudoku::pon_valor(int f, int c, int v) {

	// primero para poner un valor, nos declaramos las variables fundamentales (direcciones del recorritdo, la dimension, si esta repetido y si es admitido o no)

	int dimension = this->tablero.dimension();
	int dir_x[4] = { 1, 0};
	int dir_y[4] = { 0, 1};

	int raiz_perfecta = sqrt(dimension);
	int lf = (f / raiz_perfecta) * raiz_perfecta; // calculamos la cuadricula en que esta para analizarla
	int lc = (c / raiz_perfecta) * raiz_perfecta;

	bool addit = false;

	if (this->tablero.get_celda(f, c).es_vacia() && v > 0 && f < dimension && c < dimension && v <= dimension && es_valor_posible(f, c, v)) {
		
		// para añadir el valor a la celda y aumentar su multiplicidad se debe cumplir que esta vacia la celda, que el valor entra dentro del rango, y que es un valor posible en su columna, su fila y su cuadricula
		
		this->tablero.set_valor(f, c, v, "OCUPADA");
		this->cont += 1;

		addit = true;


		for (int i = 0; i < 2; i++) { // se procede a actualizar a todos los valores no validos de la celda que estan en su direccion vertical, horizontal y la cuadricula

			int nf = f * dir_x[i];
			int nc = c * dir_y[i];


			while (nf >= 0 && nf < dimension && nc >= 0 && nc < dimension) { // para analizar la fila y la columna, se debe iniciar desde el inicio primero en la fila y luego en la columna para actualizar solo los valores que estan fuera de la cuadricula en la direccion de la fila y la columna dada por la celda de la cuadricula

				if (nf >= lf && (nf < (lf + raiz_perfecta)) && dir_x[i] == 0) { // si llegase a entrar en la cuadricula, la salta
					nf += raiz_perfecta;
				}
				else if (nc >= lc && (nc < (lc + raiz_perfecta)) && dir_y[i] == 0) {
					nc += raiz_perfecta;
				}
				else {
					
					info_valores_no_validos.no_validos[nf][nc].insertar(v);



					if (this->tablero.get_celda(nf, nc).es_vacia()) { // se comprueba si esta bloqueada solo si la celda es vacia
						block(nf, nc);
					}




					nc += dir_x[i];
					nf += dir_y[i];
				}

			}
		}

		int i = lf;

		while ((i >= lf) && (i < (lf + raiz_perfecta))) { // una vez culminado ese tramo, se procede a actualizar la cuadricula (se realiza de esta manera para que no se duplique)
			int j = lc;
			while ((j >= lc) && (j < (lc + raiz_perfecta))) {

				info_valores_no_validos.no_validos[i][j].insertar(v);


				if (this->tablero.get_celda(i, j).es_vacia()) { // se comprueba si esta bloqueada solo si la celda es vacia
					block(i, j);
				}

				j++;
			}

			i++;
		}

	}

	return addit;

}

void ReglasSudoku::block(int nf, int nc) {

	bool block_repetido = false;
	int p = 0;
	int dimension = this->tablero.dimension();


	while (p < this->pos_bloqueadas.cont && !block_repetido) { // primero para ver si hay celdas bloqueadas, se empieza analizando si la celda en que se esta ya pertenece a la lista de bloquedas

		if (this->pos_bloqueadas.lista_de_bloqueados[p]->f == nf && this->pos_bloqueadas.lista_de_bloqueados[p]->c == nc) {
			block_repetido = true;
		}
		p++;
	}
	if (!block_repetido) { // si dicha celda no se encontro dentro de las posiciones bloqueadas, entonces se procede a hacer un analisis de todos sus valores posibles, y si no tiene ni uno, es que esta bloqueada


		if (contBloq(nf, nc) == dimension) { // sera una celda bloqueada si los valores no valudos son todos los posibles
				this->pos_bloqueadas.lista_de_bloqueados[this->pos_bloqueadas.cont] = new tPosBloqueada();
				this->pos_bloqueadas.lista_de_bloqueados[this->pos_bloqueadas.cont]->f = nf;
				this->pos_bloqueadas.lista_de_bloqueados[this->pos_bloqueadas.cont]->c = nc;
				this->pos_bloqueadas.cont += 1;
		}
	}

}

int ReglasSudoku::contBloq(int f, int c) const { 

	return this->info_valores_no_validos.no_validos[f][c].dame_num_elems();
}

void ReglasSudoku::unlock(int nf, int nc) { // lo que hace el desbloqueo, es analizar el numero de elementos de la celda y ver si se ha liberado un espacio

	int k = 0;
	
	if (this->tablero.get_celda(nf, nc).es_vacia()) {
		while (k < dame_num_celdas_bloqueadas()) { // se procede a hacer una busqueda entre las celdas bloqueadas para ver si coincide con alguna que este vacia

			if (this->pos_bloqueadas.lista_de_bloqueados[k]->f == nf && this->pos_bloqueadas.lista_de_bloqueados[k]->c == nc) {
								
				if (this->info_valores_no_validos.no_validos[nf][nc].dame_num_elems() < this->tablero.dimension()) { // si hay un espacio liberado dentro de los valores no validos, de desbloqueda
					delete this->pos_bloqueadas.lista_de_bloqueados[k];

					for (int n = k; n < (dame_num_celdas_bloqueadas() - 1); n++) { // se hace el reordenamiento			
						this->pos_bloqueadas.lista_de_bloqueados[n] = this->pos_bloqueadas.lista_de_bloqueados[n + 1];
					}

					this->pos_bloqueadas.lista_de_bloqueados[(dame_num_celdas_bloqueadas() - 1)] = nullptr;
					this->pos_bloqueadas.cont -= 1;

				}
			}
			k++;

		}

	}
}

bool ReglasSudoku::quita_valor(int f, int c) {

	// primero para quitar un valor, nos declaramos las variables fundamentales (direcciones del recorritdo, la dimension, si esta repetido y si es admitido o no)

	bool deleit = false;

	int v = this->tablero.get_celda(f, c).dame_valor();
	int num_celdas_bloqueadas = dame_num_celdas_bloqueadas();

	int dimension = this->tablero.dimension();
	bool es_posible = false;
	int dir_x[2] = { 1, 0 };
	int dir_y[2] = { 0, 1 };
	int raiz_perfecta = sqrt(dimension);
	int lf = (f / raiz_perfecta) * raiz_perfecta; // calculamos la cuadricula en que esta para analizarla
	int lc = (c / raiz_perfecta) * raiz_perfecta;

	if ((this->tablero.get_celda(f, c).es_ocupada())) { // se verifica que la celda este vacia, para setearla como vacia 

		deleit = true;
		this->tablero.set_valor(f, c, 0, "VACIO");
		this->cont -= 1;

		for (int i = 0; i < 2; i++) { // se procede hacer la actualizacion de estado en base a las direcciones objetivo de la celda (columna y vertical) 

			int nf = f * dir_x[i];
			int nc = c * dir_y[i];


			while (nf >= 0 && nf < dimension && nc >= 0 && nc < dimension) {

				if (nf >= lf && (nf < (lf + raiz_perfecta)) && dir_x[i] == 0) {
					nf += raiz_perfecta;
				}
				else if (nc >= lc && (nc < (lc + raiz_perfecta)) && dir_y[i] == 0) {
					nc += raiz_perfecta;
				}
				else {
					info_valores_no_validos.no_validos[nf][nc].eliminar(v);

					unlock(nf, nc);


					nc += dir_x[i];
					nf += dir_y[i];
				}

			}
		}

		int i = lf;

		while ((i >= lf) && (i < (lf + raiz_perfecta))) { // una vez culminado ese tramo, se a actualizar los valores que afectan a la celda en la cuadricula
			int j = lc;
			while ((j >= lc) && (j < (lc + raiz_perfecta))) {

				
				info_valores_no_validos.no_validos[i][j].eliminar(v);

				unlock(i, j);


				j++;
			}

			i++;
		}
	}	

	return deleit;

}

void ReglasSudoku::autocompletar() {

	int dimension = this->tablero.dimension();

	for (int i = 0; i < dimension; i++) {

		for (int j = 0; j < dimension; j++) {

			int k = 1;
			bool addit = false;

			if (this->tablero.get_celda(i, j).es_vacia()) { // para autocompletar se analizan todos las celdas que estas vacias del sudoku
				 
				if ((dimension - this->info_valores_no_validos.no_validos[i][j].dame_num_elems()) == 1) { // si dentro de los valores no validos, falta solo 1 para completar, quiere decir que ese ultimo es el valor con que se debe auto completar
					while ((k <= dimension) && (k > 0) && !addit) {

						if (!this->info_valores_no_validos.no_validos[i][j].pertenece(k)) { // se procede a hacer la busqueda de cual es el valor que pertenece
							pon_valor(i, j, k);
							addit = true;
						}

						k++;
					}

				}

			}


		}

	}


}

bool ReglasSudoku::carga_sudoku(ifstream& archivo, string file_name) {

	bool done = false;
	int dim = 0;

	int dimension = this->tablero.dimension();
	bool es_posible = false;
	int dir_x[2] = { 1, 0 };
	int dir_y[2] = { 0, 1 };
	int raiz_perfecta = sqrt(dimension);


	archivo.open(file_name);
	if (archivo.is_open()) {

		archivo >> dim;
		int v = 0;



		this->tablero = Tablero(dim);
		this->info_valores_no_validos.nColumnas = dim;
		this->info_valores_no_validos.nFilas = dim;
		int dimension = this->tablero.dimension();

		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				archivo >> v;
					
				// lo que se hace es actualizar para todas las celdas sus valores no validos en base a los que estan pre cargados´

					int lf = (i / raiz_perfecta) * raiz_perfecta; // calculamos la cuadricula en que esta para analizarla
					int lc = (j / raiz_perfecta) * raiz_perfecta;

					for (int l = 0; l < 2; l++) {
						int nf = i * dir_x[l];
						int nc = j * dir_y[l];

						while (nf >= 0 && nf < dimension && nc >= 0 && nc < dimension) {

							if (nf >= lf && (nf < (lf + raiz_perfecta)) && dir_x[l] == 0) {
								nf += raiz_perfecta;
							}
							else if (nc >= lc && (nc < (lc + raiz_perfecta)) && dir_y[l] == 0) {
								nc += raiz_perfecta;
							}
							else {	 //primero para ver si el valor es posible hay que analizar los valores a su alrededor para calcular la multiplicidad de sus apariciones
									
									if (v > 0) {

										info_valores_no_validos.no_validos[nf][nc].insertar(v);

								}
								nc += dir_x[l];
								nf += dir_y[l];
							}
							}

						}

					int n = lf;

					while ((n >= lf) && (n < (lf + raiz_perfecta))) { // una vez culminado ese tramo, se procede a analizar los valores que afectan a la celda en la cuadricula
						int m = lc;
						while ((m >= lc) && (m < (lc + raiz_perfecta))) {

							if (v > 0) {
								info_valores_no_validos.no_validos[n][m].insertar(v);
							}

							m++;
						}

						n++;
					}

					if (v == 0) {
						this->tablero.set_valor(i, j, v, "VACIA");


					}
					else {
						this->tablero.set_valor(i, j, v, "ORIGINAL");
						this->cont += 1;
					}
					}



			}

		}

		done = true;

		archivo.close();

	return done;
}

void ReglasSudoku::reset() {

	int dim = this->tablero.dimension();
	int dir_x[2] = { 1, 0 };
	int dir_y[2] = { 0, 1 };
	
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
		
			if (this->tablero.get_celda(i, j).es_ocupada()) {

				quita_valor(i, j);

			}
		
		}
	}
}

ReglasSudoku& ReglasSudoku::operator=(const ReglasSudoku& sudoku) {
	if (this != &sudoku) { 

		this->cont = sudoku.cont;

		this->ID_SUDOKU = sudoku.dame_ID();
		this->info_valores_no_validos = sudoku.info_valores_no_validos;
		this->tablero = sudoku.tablero;

		/* se libera la memoria ocupada por this*/
		for (int i = 0; i < this->pos_bloqueadas.cont; i++) {
			delete this->pos_bloqueadas.lista_de_bloqueados[i];
			this->pos_bloqueadas.lista_de_bloqueados[i] = nullptr;
		}

		this->pos_bloqueadas.cont = sudoku.pos_bloqueadas.cont;

		for (int i = 0; i < sudoku.pos_bloqueadas.cont; i++) {
			this->pos_bloqueadas.lista_de_bloqueados[i] = new tPosBloqueada(*sudoku.pos_bloqueadas.lista_de_bloqueados[i]);
		}
	}
	return *this;
}

int num_Celda(int k,const ReglasSudoku& sudoku1) {
	int dimension = sudoku1.dame_dimension();
	int apariciones = 0;

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (sudoku1.dame_celda(i, j).es_vacia()) {
				int q = sudoku1.contBloq(i, j);
				if (k == (9 - q)) {
					apariciones++;
				}
			}
		}
	}

	return apariciones;

	
}

bool operator<(const ReglasSudoku& s1, const ReglasSudoku& s2) {

	bool menor = false;
	int dimension = s1.dame_dimension();
	int cont1 = 0, cont2 = 0;

	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (s1.dame_celda(i, j).es_vacia()) {
				cont1++;
			}
			if (s2.dame_celda(i, j).es_vacia()) {
				cont2++;
			}
		}
	}

	if (cont1 < cont2) {
		menor = true;
	}

	else if (cont1 == cont2) {
		int k = 0;
		while ((!menor) && k <= 9) {

			if ((num_Celda(k, s1) <= num_Celda(k, s2))) {
				if (num_Celda(k+1, s1) > num_Celda(k+1, s2)) {
					menor = true;
				}
			}

			k++;
		}
	}

	return menor;
}

bool operator==(const ReglasSudoku& s1, const ReglasSudoku& s2) {

	bool son_iguales = true;
	int i = 0, j = 0;
	int dimension = s1.dame_dimension();

	while (son_iguales && i < dimension) {

		while (son_iguales && j < dimension) {

			if (s1.dame_celda(i, j).dame_valor() != s2.dame_celda(i, j).dame_valor()) {

				son_iguales = false;

			}

			j++;
		}

		i++;
	}

	return son_iguales;
}

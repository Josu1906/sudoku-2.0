#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include "tablero.h"
#include "celda.h"
#include "reglasudoku.h"
#include "listasudoku.h"

using namespace std;

// Códigos ANSI para los colores
const string ORANGE = "\033[38;5;208m"; // Naranja brillante
const string RESET = "\033[0m";         // Volver al color original
const string GREEN   = "\x1b[32m";
const string DRED = "\x1b[31m";
const string BLUE = "\033[94m";
const string GOLD = "\033[93m"; // Dorado para estrellas
const string RED = "\033[91m"; // Rojo para globos


void title() {
    cout << BLUE;
    cout << "  ____  _   _  ____   ___  _  __ _   _" << endl;
    cout << " / ___|| | | ||  _ \\ / _ \\| |/ /| | | |" << endl;
    cout << " \\___ \\| | | || | | | | | | ' / | | | |" << endl;
    cout << "  ___) | |_| || |_| | |_| |  <  | |_| |" << endl;
    cout << " |____/ \\___/ |____/ \\___/|_|\\_\\ \\___/ " << endl;
    cout << RESET << endl;

    cout << GREEN << "By: Josue Gonzalez Villarroel y Jesus DeMiguel Perez \n" << RESET;
}

void reset(bool r) {
    if (r) {
        system("CLS");
        title();
    }
}

void visualizar(ReglasSudoku sudoku) {

    int dim = sudoku.dame_dimension();
    int dim_raiz = sqrt(dim);

    cout << endl;

    cout << "     ";



    for (int i = 1; i <= dim; i++) {
        cout << " " << setw(3) << i << " ";
        if ((i) % dim_raiz == 0) {
            cout << "|";
        }
    }

    cout << "\n";

    cout << setw(2) << "";

    for (int i = 0; i < sqrt(dim); i++) {
        cout << setw(dim_raiz - 1) << "" << i << setw(dim_raiz - 1) << "";
        cout << "+";
        for (int i = 0; i < dim_raiz; i++) {
            cout << "---";
        }
        cout << "+";
    }

    cout << setw(dim_raiz) << "|";
    cout << endl;

    for (int i = 0; i < dim; i++) {
        // Número de fila
        cout << setw(3) << i + 1 << " |";

        for (int j = 0; j < dim; j++) {
            cout << " ";

            // Si es 0 imprimimos un punto, sino el número en Naranja
            if (sudoku.dame_celda(i, j).dame_valor() == 0) {
                cout << setw(3) << ".";
            }
            else if (sudoku.dame_celda(i, j).es_original()) {
                cout << ORANGE << setw(3) << sudoku.dame_celda(i, j).dame_valor() << RESET;
            }
            else {
                cout << setw(3) << sudoku.dame_celda(i, j).dame_valor();

            }

            cout << " ";

            // Separador vertical cada 3 columnas
            if ((j + 1) % dim_raiz == 0) {
                cout << "|";
            }
        }
        cout << "\n";

        // Separador horizontal cada 3 filas
        if ((i + 1) % dim_raiz == 0) {
            
            cout << "    ";
            for (int i= 0; i < dim_raiz; i++) {
                cout << "+---------------";
            }
            cout << "+\n";
        }
    }

    // Imprimir el menú inferior

    // Aquí iría tu lógica para leer la opción del usuario
    // int opcion;
    // cin >> opcion;

}

void block(ReglasSudoku sudoku) {

    int n = sudoku.dame_num_celdas_bloqueadas();
    int f = 0, c = 0;

    cout << "Sudoku bloqueado... Las casillas son: ";

    if (n == 0) {
        cout << DRED << "NONE" << RESET;
    }

    for (int i = 0; i < n; i++) {
        sudoku.dame_celda_bloqueada(i, f, c);

        cout << DRED << " (" << (f + 1) << ", " << (c + 1) << ") " << RESET;
    }

    cout << endl;

}

void opciones() {

    cout << "\n";
    cout << "  1.- poner numero\n";
    cout << "  2.- quitar numero\n";
    cout << "  3.- reset\n";
    cout << "  4.- posibles valores de una celda vacia\n";
    cout << "  5.- autocompletar celdas con valor unico\n";
    cout << "  6.- salir\n";
    cout << "Elige una opcion: ";
}

int main() {

    bool am = true;
    int num_sudokus = 0;

    ListaSudoku lista_originales;
    ListaSudoku lista_partidas;
    ifstream archivo;
    ifstream archivo2;

    archivo.open("lista_sudokus.txt");
    if (archivo.is_open()) {
        cin >> num_sudokus;

        for (int i = 0; i < num_sudokus; i++) {
            string id_sudoku;
            cin >> id_sudoku;

            ReglasSudoku* sudoku = new ReglasSudoku();
            sudoku->carga_sudoku(archivo2, id_sudoku);
            lista_originales.insertar(*sudoku);
            delete sudoku;
        }
        

        archivo.close();
    }

    archivo.open("lista_sudokus.txt");
    if (archivo.is_open()) {
        cin >> num_sudokus;
        if (num_sudokus > 0) {
            for (int i = 0; i < num_sudokus; i++) {
                string id_sudoku;
                cin >> id_sudoku;

                ReglasSudoku* sudoku = new ReglasSudoku();
                sudoku->carga_sudoku(archivo2, id_sudoku);
                lista_partidas.insertar(*sudoku);
                delete sudoku;
            }
        }
    }

    char op;
    int index = 0;
    cout << "Partida nueva (N), continuar partida(C) o abandonar la aplicacion(A) ? ";
    cin >> op;

    if (op == 'N') {
        lista_originales.mostrar_lista();
        cout << "Elige un sudoku: ";
        cin >> index;
        ReglasSudoku sudoku = lista_originales.dame_sudoku(index);
    }


    //while (am) {

    //int request = 0;


    //bool salir = false;


    //system("CLS");



    //title();

    //bool r = false;
    //char hr;
    //cout << "DO YOU WANNA RESTART THE CONSOLE COMPLETELY EVERYTIME IT UPDATES (IF YOU SAY YES, YOU WONT BE ABLE TO VIEW YOUR SUDOKU HISTORY)?" << endl;
    //cout << "Y OR N: ";
    //cin >> hr;


    //if (toupper(hr) == 'Y') r = true;

    //system("CLS");

    //title();

    //ifstream archivo;
    //ReglasSudoku sudoku = ReglasSudoku();

    //sudoku.carga_sudoku(archivo);
    //int f = 0, c = 0, v = 0;
    //int dim = sudoku.dame_dimension();
    //int addit = 0;
    //    
    //visualizar(sudoku);
    //opciones();

    //while (!sudoku.terminado() && !salir) {
    //    cin >> request;

    //    switch (request) {
    //        case 1:
    //            cout << "/n Fila y columna entre 1 ... 9: ";
    //            cin >> f >> c;
    //            f -= 1;
    //            c -= 1;
    //            cout << "/n Valor: ";
    //            cin >> v;

    //            if (sudoku.pon_valor(f, c, v)) {
    //                cout << endl;
    //                reset(r);
    //                /*visualizar(sudoku, reset);
    //                block(sudoku);*/
    //                
    //                cout << GREEN << "--> THE VALUE: " << RESET << v << GREEN << " WAS ADDED IT CORRECTLY IN " << RESET << "(" << (f + 1) << ", " << (c + 1) << " )" << GREEN << " <--" << RESET << endl;
    //                /*opciones();*/
    //            }

    //            else {
    //                cout << endl;
    //                reset(r);
    //                
    //                /*visualizar(sudoku, reset);
    //                block(sudoku);*/

    //                cout << DRED << " --> ERROR: WE COULDNT ADD " << RESET << v << " IN " << RESET << "(" << (f + 1) << ", " << (c + 1) << ")" << DRED << ".IT IS NOT POSSIBLE <-- " << RESET << endl;
    //                /*opciones();*/
    //            }


    //            break;
    //        case 2:
    //            cout << "/n Fila y columna entre 1 ... 9: ";
    //            cin >> f >> c;
    //            f -= 1;
    //            c -= 1;


    //            if (sudoku.quita_valor(f, c)) {
    //                cout << endl;
    //                reset(r);
    //                /*visualizar(sudoku, reset);
    //                block(sudoku);*/
    //                cout << GREEN << "--> DELETED IT CORRECTLY <--" << RESET << endl;
    //            }

    //            else {
    //                cout << endl;
    //                reset(r);
    //                /*visualizar(sudoku, reset);
    //                block(sudoku);*/
    //                cout << DRED << "--> IT CANNOT BE DELETED <-- " << RESET << endl;
    //            }

    //            //opciones();
    //        break;
    //        case 3:
    //            sudoku.reset();
    //            cout << endl;
    //            reset(r);
    //            /*visualizar(sudoku, reset);
    //            opciones();*/
    //        break;
    //        case 4:
    //            cout << "/n Fila y columna entre 1 ... 9: ";
    //            cin >> f >> c;
    //            f -= 1;
    //            c -= 1;

    //            /*visualizar(sudoku, reset);
    //            block(sudoku);*/
    //            cout << endl;
    //            reset(r);
    //            cout << "En (" << (f + 1) << ", " << (c + 1) << ") ... Los valores posibles son: ";

    //            if (sudoku.dame_celda(f, c).es_vacia() && f < dim && c < dim) {
    //                for (int i = 1; i <= sudoku.dame_dimension(); i++) {
    //                    if (sudoku.es_valor_posible(f, c, i)) {
    //                        addit += 1;
    //                        cout << i << " ";
    //                    }
    //                }
    //                if (addit == 0) {
    //                    cout << RED << " NONE" << RESET << endl;
    //                }
    //                cout << endl;

    //            }
    //            else {
    //                cout << RED << " NONE" << RESET << endl;
    //            }

    //            addit = 0;

    //            /*opciones();*/

    //            break;

    //        case 5:
    //            sudoku.autocompletar();
    //            reset(r);
    //            //visualizar(sudoku, reset);
    //            /*block(sudoku);
    //            opciones();*/
    //        break;
    //        case 6:
    //            salir = true;
    //        break;
    //       default:
    //           reset(r);
    //            //visualizar(sudoku, reset);
    //            //block(sudoku);
    //            //opciones();
    //        break;
    //    }

    //    visualizar(sudoku);
    //    block(sudoku);
    //    opciones();


    //    }

    //    system("CLS");
    //    cout << endl;
    //        // Globos y Estrellas a los lados del mensaje principal
    //    if (!salir) {
    //        cout << RED << "  _  " << GOLD << " * " << RED << "_                                       _  " << GOLD << " * " << RED << "_  " << endl;
    //        cout << RED << " ( )   ( )      " << GREEN << " ##   ##  ######  ##   ##     " << RED << " ( )   ( ) " << endl;
    //        cout << RED << "  |  " << GOLD << " * " << RED << "|       " << GREEN << "  ## ##  ##    ## ##   ##     " << RED << "  |  " << GOLD << " * " << RED << "|  " << endl;
    //        cout << RED << "  |     |        " << GREEN << "   ###   ##    ## ##   ##     " << RED << " |     |  " << endl;
    //        cout << RED << "  v     v        " << GREEN << "   ###   ##    ## ##   ##     " << RED << " v     v  " << endl;
    //        cout << "                 " << GREEN << "   ###    ######   #####       " << endl;

    //        cout << endl;

    //            // WON con caracteres ASCII estándar (#)
    //        cout << "          " << GREEN << " ##     ##   ######  ###    ## " << endl;
    //        cout << "          " << GREEN << " ##     ##  ##    ## ####   ## " << endl;
    //        cout << "          " << GREEN << " ##  #  ##  ##    ## ## ##  ## " << endl;
    //        cout << "          " << GREEN << " ## ### ##  ##    ## ##  ## ## " << endl;
    //        cout << "          " << GREEN << "  ### ###    ######  ##   #### " << endl;
    //        cout << endl;

    //        cout << GOLD << "\n          * * * ¡CONGRATULATIONS!   * * * " << RESET << endl;
    //    }
    //    cout << endl;

    //    cout << "DO YOU WANNA PLAY ANOTHER MATCH?" << endl;
    //    cout << "Y OR N: ";
    //    cin >> hr;


    //    if (toupper(hr) != 'Y') am = false;
    //}

    return 0;
}
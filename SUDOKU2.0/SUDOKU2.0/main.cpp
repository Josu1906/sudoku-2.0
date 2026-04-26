#include <iostream>
#include "checkML.h"
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
//const string ORANGE = "\033[38;5;208m"; // Naranja brillante
//const string RESET = "\033[0m";         // Volver al color original
//const string GREEN   = "\x1b[32m";
//const string DRED = "\x1b[31m";
//const string BLUE = "\033[94m";
const string GOLD = "\033[93m"; // Dorado para estrellas
//const string RED = "\033[91m"; // Rojo para globos


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

void visualizar(const ReglasSudoku& sudoku) {

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

void block(ReglasSudoku& sudoku) {

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
    cout << "  6.- Resolver sudoku\n";
    cout << "  7.- salir\n";
    cout << "Elige una opcion: ";
}

void update(ReglasSudoku& sudoku, ofstream& arch, int num_sudokus, ifstream& input, char &aux_char) {
    int dim = sudoku.dame_dimension();
    string id;
    int cords[3] = { 0,0,0 };
    
    arch << sudoku.dame_ID() << endl;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (sudoku.dame_celda(i, j).es_ocupada()) {
                arch << "(" << i << ", " << j << "): " << sudoku.dame_celda(i, j).dame_valor() << endl;
            }
        }
    }
    arch << "-1" << endl;

    for (int i = 0; i < num_sudokus; i++) {

        input >> id;
        if (id != sudoku.dame_ID()) {

            /*archivo >> aux_str;
            archivo.ignore();*/
            input.get(aux_char);

            arch << id << endl;;

            input.get(aux_char);
            while (aux_char != '-') {
                input >> cords[0];
                input.get(aux_char);
                input >> cords[1];
                input.get(aux_char);
                input.get(aux_char);
                input >> cords[2];
                input.ignore();
                input.get(aux_char);

                arch << "(" << cords[0] << ", " << cords[1] << "): " << cords[2] << endl;

                //cout << id_sudoku << " (" << cords[0] << ", " << cords[1] << "). v: " << cords[2] << endl;
            }
            arch << "-1" << endl;

            input.get(aux_char);
            input.ignore();

        }
        else {
            input.ignore();
            input.get(aux_char);

            while (aux_char != '-') {
                input >> cords[0];
                input.get(aux_char);
                input >> cords[1];
                input.get(aux_char);
                input.get(aux_char);
                input >> cords[2];
                input.ignore();
                input.get(aux_char);
            }
            input.get(aux_char);
            input.ignore();
        }

    }

}

void fDelete(ReglasSudoku& sudoku, ofstream& arch, int num_sudokus, ifstream& input, char& aux_char) {
    int dim = sudoku.dame_dimension();
    string id;
    int cords[3] = { 0,0,0 };

    for (int i = 0; i < num_sudokus; i++) {
        
        input >> id;
        if (id != sudoku.dame_ID()) {

            /*archivo >> aux_str;
            archivo.ignore();*/
            input.get(aux_char);

            arch << id << endl;;

            input.get(aux_char);
            while (aux_char != '-') {
                input >> cords[0];
                input.get(aux_char);
                input >> cords[1];
                input.get(aux_char);
                input.get(aux_char);
                input >> cords[2];
                input.ignore();
                input.get(aux_char);

                arch << "(" << cords[0] << ", " << cords[1] << "): " << cords[2] << endl;

                //cout << id_sudoku << " (" << cords[0] << ", " << cords[1] << "). v: " << cords[2] << endl;
            }
            arch << "-1" << endl;

            input.get(aux_char);
            input.ignore();

        }
        else {
            input.ignore();
            input.get(aux_char);

            while (aux_char != '-') {
                input >> cords[0];
                input.get(aux_char);
                input >> cords[1];
                input.get(aux_char);
                input.get(aux_char);
                input >> cords[2];
                input.ignore();
                input.get(aux_char);
            }
            input.get(aux_char);
            input.ignore();
        }

    }

}

void resolver_sudoku(ReglasSudoku& sudoku) {

    if (!sudoku.terminado()) {
        sudoku.autocompletar();
        if (sudoku.dame_num_celdas_bloqueadas() == 0) {
            resolver_sudoku(sudoku);
        }
    }

}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    bool am = true;
    

    while (am) {
        int num_sudokus = 0;
        int request = 0;
        bool salir = false;
        bool r = false;
        bool is_repeat = false;
        char hr;
        string id;
        bool updateit = false;
        ListaSudoku lista_originales;
        ListaSudoku lista_partidas;
        ifstream archivo;
        ifstream archivo2;
        ofstream archivo_salida;
        string id_sudoku;
        char aux_char;
        string aux_str;
        char op;
        int index = 0;
        ReglasSudoku sudoku_play;
        ReglasSudoku* sudoku;
        bool insert = false;

        /*archivo.open("ord.txt");
        if (archivo.is_open()) {
            int i = 0;
            while ((aux_char != '-') && (i < 9)) {
                archivo >> index_partida[i];
                i++;
            }
            archivo.close();
        }*/
        
        archivo.open("lista_sudokus.txt");
        if (archivo.is_open()) {
                archivo >> num_sudokus;

                for (int i = 0; i < num_sudokus; i++) {
                    archivo >> id_sudoku;
                    //cout << id_sudoku << endl;

                    ReglasSudoku* sudoku = new ReglasSudoku();
                    sudoku->carga_sudoku(archivo2, id_sudoku);
                    sudoku->set_ID(id_sudoku);
                    lista_originales.insertar(*sudoku);
                    delete sudoku;
                    sudoku = nullptr;
                }


            archivo.close();
        }

        system("CLS");

        title();


        archivo2.open("lista_partidas.txt");
        if (archivo2.is_open()) {
            archivo2 >> num_sudokus;
            /*ReglasSudoku* sudoku;*/
            for (int i = 0; i < num_sudokus; i++) {
                int cords[3] = { 0,0,0 };
                archivo2 >> id;
                int j = 0;
                bool encontrado = false;
                while (!encontrado && j < 9) {
                    if(id == lista_originales.dame_sudoku(j).dame_ID()){
                        encontrado = true;
                        sudoku = new ReglasSudoku(lista_originales.dame_sudoku(j));
                        //archivo >> aux_str;
                        //archivo.ignore();
                        archivo2.get(aux_char);
                        archivo2.get(aux_char);

                        while (aux_char != '-') {
                            archivo2 >> cords[0];
                            archivo2.get(aux_char);
                            archivo2 >> cords[1];
                            archivo2.get(aux_char);
                            archivo2.get(aux_char);
                            archivo2 >> cords[2];
                            archivo2.ignore();
                            archivo2.get(aux_char);

                            sudoku->pon_valor(cords[0], cords[1], cords[2]);
                            //cout << id << " (" << cords[0] << ", " << cords[1] << "). v: " << cords[2] << endl;
                        }

                        archivo2.get(aux_char);
                        archivo2.ignore();

                        lista_partidas.insertar(*sudoku);
                        delete sudoku;
                    }
                    j++;
                }

            }
            archivo2.close();
        }

        cout << "Partida nueva (N), continuar partida(C) o abandonar la aplicacion(A) ? ";
        cin >> op;

        if (op == 'N') {
            lista_originales.mostrar_lista();
            cout << "Elige un sudoku: ";
            cin >> index;
            insert = true;
            if (index != -1) sudoku_play = lista_originales.dame_sudoku(index - 1);
            else salir = true;
        }
        else if (op == 'C') {
            if (lista_partidas.dame_num_elems() > 0) {
                lista_partidas.mostrar_lista();
                cout << "Elige un sudoku: ";
                cin >> index;
                if (index != -1) sudoku_play = lista_partidas.dame_sudoku(index - 1);
                else salir = true;
            }
            else {
                cout << "No hay partidas empezadas. Elige una partida nueva:" << endl;
                lista_originales.mostrar_lista();
                cout << "Elige un sudoku: ";
                cin >> index;
                insert = true;
                sudoku_play = lista_originales.dame_sudoku(index - 1);
            }
        }
        
        cout << "1. Ver un sudoku." << endl;
        cout << "2. Jugar un sudoku." << endl;
        cout << "Elige una opcion: ";
        cin >> op;

        if (op == '1') {
            visualizar(sudoku_play);
            cin.ignore();
            cin.get();
        }
        else {


            system("CLS");



            cout << "DO YOU WANNA RESTART THE CONSOLE COMPLETELY EVERYTIME IT UPDATES (IF YOU SAY YES, YOU WONT BE ABLE TO VIEW YOUR SUDOKU HISTORY)?" << endl;
            cout << "Y OR N: ";
            cin >> hr;


            if (toupper(hr) == 'Y') r = true;

            system("CLS");

            title();

            int f = 0, c = 0, v = 0;
            int dim = sudoku_play.dame_dimension();
            int addit = 0;
            int j = 0;
    
            visualizar(sudoku_play);
            block(sudoku_play);
            opciones();

            while (!sudoku_play.terminado() && !salir) {
                cin >> request;

                switch (request) {
                case 1:
                    cout << "/n Fila y columna entre 1 ... 9: ";
                    cin >> f >> c;
                    f -= 1;
                    c -= 1;
                    cout << "/n Valor: ";
                    cin >> v;

                    if (sudoku_play.pon_valor(f, c, v)) {
                        cout << endl;
                        reset(r);
                        /*visualizar(sudoku, reset);
                        block(sudoku);*/

                        cout << GREEN << "--> THE VALUE: " << RESET << v << GREEN << " WAS ADDED IT CORRECTLY IN " << RESET << "(" << (f + 1) << ", " << (c + 1) << " )" << GREEN << " <--" << RESET << endl;
                        /*opciones();*/
                    }

                    else {
                        cout << endl;
                        reset(r);

                        /*visualizar(sudoku, reset);
                        block(sudoku);*/

                        cout << DRED << " --> ERROR: WE COULDNT ADD " << RESET << v << " IN " << RESET << "(" << (f + 1) << ", " << (c + 1) << ")" << DRED << ".IT IS NOT POSSIBLE <-- " << RESET << endl;
                        /*opciones();*/
                    }


                    break;
                case 2:
                    cout << "/n Fila y columna entre 1 ... 9: ";
                    cin >> f >> c;
                    f -= 1;
                    c -= 1;


                    if (sudoku_play.quita_valor(f, c)) {
                        cout << endl;
                        reset(r);
                        /*visualizar(sudoku, reset);
                        block(sudoku);*/
                        cout << GREEN << "--> DELETED IT CORRECTLY <--" << RESET << endl;
                    }

                    else {
                        cout << endl;
                        reset(r);
                        /*visualizar(sudoku, reset);
                        block(sudoku);*/
                        cout << DRED << "--> IT CANNOT BE DELETED <-- " << RESET << endl;
                    }

                    opciones();
                    break;
                case 3:
                    sudoku_play.reset();
                    cout << endl;
                    reset(r);
                    /*visualizar(sudoku, reset);
                    opciones();*/
                    break;
                case 4:
                    cout << "/n Fila y columna entre 1 ... 9: ";
                    cin >> f >> c;
                    f -= 1;
                    c -= 1;

                    /*visualizar(sudoku, reset);
                    block(sudoku);*/
                    cout << endl;
                    reset(r);
                    cout << "En (" << (f + 1) << ", " << (c + 1) << ") ... Los valores posibles son: ";

                    if (sudoku_play.dame_celda(f, c).es_vacia() && f < dim && c < dim) {
                        for (int i = 1; i <= sudoku_play.dame_dimension(); i++) {
                            if (sudoku_play.es_valor_posible(f, c, i)) {
                                addit += 1;
                                cout << i << " ";
                            }
                        }
                        if (addit == 0) {
                            cout << RED << " NONE" << RESET << endl;
                        }
                        cout << endl;

                    }
                    else {
                        cout << RED << " NONE" << RESET << endl;
                    }

                    addit = 0;

                    /*opciones();*/

                    break;

                case 5:
                    sudoku_play.autocompletar();
                    reset(r);
                    /*block(sudoku);
                    opciones();*/
                    break;
                case 6: 
                    resolver_sudoku(sudoku_play);
                    reset(r);
                    break;
                case 7:
                    char save;
                    salir = true;
                    cout << "DO YOU WANNA SAVE THE GAME? Y or N: ";
                    cin >> save;

                    if (save == 'Y') {
                        archivo.open("lista_partidas.txt");
                        if (archivo.is_open()) {

                            archivo_salida.open("temp.txt");
                            if (archivo_salida.is_open()) {

                                archivo >> num_sudokus;
                            
                                if (insert) {
                                
                                    while (j < lista_partidas.dame_num_elems() && !is_repeat) {
                                        if (sudoku_play.dame_ID() == lista_partidas.dame_sudoku(j).dame_ID()) {
                                            is_repeat = true;
                                        }
                                        j++;
                                    }
                                    if(!is_repeat) archivo_salida << (num_sudokus + 1) << endl;
                                    else archivo_salida << (num_sudokus) << endl;
                                
                                    update(sudoku_play, archivo_salida, num_sudokus, archivo, aux_char);

                                }
                                else {
                                    archivo_salida << (num_sudokus) << endl;
                                    update(sudoku_play, archivo_salida, num_sudokus, archivo, aux_char);
                                }

                           

                                archivo_salida.close();
                            }
                            archivo.close();
                        }

                    }
                    else {
                        if (!insert) {
                            cout << "DO YOU WANNA DELETE ALL THE PROGRESS OF THE GAME " << sudoku_play.dame_ID() << "? ";
                            cin >> save;

                            if (save == 'Y') {
                                archivo.open("lista_partidas.txt");
                                if (archivo.is_open()) {
                                    archivo_salida.open("temp.txt");
                                    if (archivo_salida.is_open()) {
                                        archivo >> num_sudokus;
                                        archivo_salida << (num_sudokus - 1) << endl;
                                        fDelete(sudoku_play, archivo_salida, num_sudokus, archivo, aux_char);
                                        archivo_salida.close();
                                    }
                                    archivo.close();
                                }
                            }
                        }
                    }
                    remove("lista_partidas.txt");
                    rename("temp.txt", "lista_partidas.txt");
                    break;
                default:
                    reset(r);
                    break;
                }

                visualizar(sudoku_play);
                block(sudoku_play);
                opciones();


            }
        }

        cout << endl;
        //Globos y Estrellas a los lados del mensaje principal
            if (!salir &&  sudoku_play.terminado()) {
                cin.ignore();
                cin.get(op);
                system("CLS");
                cout << RED << "  _  " << GOLD << " * " << RED << "_                                       _  " << GOLD << " * " << RED << "_  " << endl;
                cout << RED << " ( )   ( )      " << GREEN << " ##   ##  ######  ##   ##     " << RED << " ( )   ( ) " << endl;
                cout << RED << "  |  " << GOLD << " * " << RED << "|       " << GREEN << "  ## ##  ##    ## ##   ##     " << RED << "  |  " << GOLD << " * " << RED << "|  " << endl;
                cout << RED << "  |     |        " << GREEN << "   ###   ##    ## ##   ##     " << RED << " |     |  " << endl;
                cout << RED << "  v     v        " << GREEN << "   ###   ##    ## ##   ##     " << RED << " v     v  " << endl;
                cout << "                 " << GREEN << "   ###    ######   #####       " << endl;

                cout << endl;

                //WON con caracteres ASCII estándar(#)
                    cout << "          " << GREEN << " ##     ##   ######  ###    ## " << endl;
                cout << "          " << GREEN << " ##     ##  ##    ## ####   ## " << endl;
                cout << "          " << GREEN << " ##  #  ##  ##    ## ## ##  ## " << endl;
                cout << "          " << GREEN << " ## ### ##  ##    ## ##  ## ## " << endl;
                cout << "          " << GREEN << "  ### ###    ######  ##   #### " << endl;
                cout << endl;

                cout << GOLD << "\n          * * * ¡CONGRATULATIONS!   * * * " << RESET << endl;
                
                if (!insert) {
                    fDelete(sudoku_play, archivo_salida, num_sudokus, archivo, aux_char);
                    lista_partidas.eliminar(index - 1);
                }
            }

            system("CLS");

        

        cout << "DO YOU WANNA PLAY ANOTHER SUDOKU?" << endl;
        cout << "Y OR N: ";
        cin >> hr;


        if (toupper(hr) != 'Y') am = false;
    }

    return 0;
}
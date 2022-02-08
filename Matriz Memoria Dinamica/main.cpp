#include <iostream>
#include "Matriz.h"
#include "Operaciones.h"

using namespace std;


void iniciar(int);

int main(int argv, char** argc) {


	cout << "Trabajo pa los dos extras: " << endl;
	cout << "ALEMAN JOSUE, MERINO JOSUE" << endl;

	system("PAUSE");
	system("cls");

	int dim;
	cout << "Ingresar la dimension de sus matrices:" << endl;
	cin >> dim;

	iniciar(dim);

	return 0;
}

void iniciar(int dim) {

	int** m1 = nullptr;
	int** m2 = nullptr;
	int** m3 = nullptr;

	Matriz matrices(m1, m2, m3, dim);
	Operaciones operacion(matrices);


	//ASIGNAMOS MEMORIA A LAS MATRICES
	operacion.segmentar1();
	operacion.segmentar2();
	operacion.segmentarR(); //matriz resultante de las primeras dos

	//ENCERAMOS LAS MATRICES
	operacion.encerar1();
	operacion.encerar2();
	operacion.encerarR();

	//GENERAMOS VALORES ALEATORIOS A LAS MATRICES

	operacion.generar1();
	operacion.generar2();

	//IMPRIMIMOS LAS MATRICES GENERADAS
	cout << "MATRIZ 1: " << endl;
	operacion.imprimir1();
	cout << endl << "_____" << endl;
	cout << "MATRIZ 2: " << endl;
	operacion.imprimir2();
	cout << endl << "_____" << endl;

	system("PAUSE");
	system("cls");

	//OPERACIONES
	int opc;
	do {
		cout << "1. Potencia de la matriz" << endl;
		cout << "2. Multiplicacion de las matrices" << endl;
		cout << "3. Salir" << endl; cin >> opc;

		if (opc == 1) {

			//POTENCIA DE LAS MATRICES
			int e;
			cout << "MATRIZ 1: " << endl;
			cout << "A que potencia desea elevar la primera matriz?:"; cin >> e;
			operacion.procesarPot(e);

			cout << endl << "MATRIZ RESULTANTE:" << endl;
			operacion.imprimirR();

			system("PAUSE");
			system("cls");

		}
		else if (opc == 2) {

			//MULTIPLICACION DE LAS MATRICES
			cout << "Multiplicando matrices..." << endl;
			operacion.procesarMulti();

			system("PAUSE");
			system("cls");

			cout << endl << "MATRIZ RESULTANTE:" << endl;
			operacion.imprimirR();

			system("PAUSE");
			system("cls");
		}
		else {
			exit(0);
		}

	} while (opc != 3);

}
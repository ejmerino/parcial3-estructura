/*
* Universidad De las Fuerzas Armadas "ESPE"
* Autores: Josu? Alem?n, Josu? Merino
* Cuadro Latino
* Fecha de Creaci?n: 08/02/2022
* Fecha de Modificaci?n 08/02/2022
*/

#include <iostream>
#include "CuadroLatino.h"
#include "Matrix.h"
#include "Utils.h"
using namespace std;

int main()
{
	cout << "---------------";
	cout << "\nCUADRO LATINO" << endl;
	cout << "---------------" << endl;
	int dimension;
	Utils::Validation valiation;
	do {
		dimension = Utils::Validation::validation_numbers<double>("Ingrese la dimension");
	} while (dimension < 1 || dimension % 2 == 0);
	Matrix m(dimension);
	CuadroLatino cuadro;
	m.segmentar(); m.encerar();
	cuadro.hacerCuadroLatino(m);
	m.imprimir();
}
/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josu? Alem?n, Josu? Merino
* Cuadro M?gico
* Fecha de Creaci?n: 08/02/2022
* Fecha de Modificaci?n: 08/02/2022
*/

#include "Matrix.h"
int** Matrix::get_matrix() {
	return matrix;
}

void Matrix::set_matrix(int** matrix_1) {
	matrix = matrix_1;
}
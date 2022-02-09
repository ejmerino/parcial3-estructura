/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Mágico
* Fecha de Creación: 08/02/2022
* Fecha de Modificación: 08/02/2022
*/

#include "Matrix.h"
int** Matrix::get_matrix() {
	return matrix;
}

void Matrix::set_matrix(int** matrix_1) {
	matrix = matrix_1;
}
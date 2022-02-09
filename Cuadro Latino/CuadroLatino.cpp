/*
* Universidad De las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Latino
* Fecha de Creación: 08/02/2022
* Fecha de Modificación 08/02/2022
*/

#include "CuadroLatino.h"
#include "Matrix.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void CuadroLatino::hacerCuadroLatino(Matrix matriz)
{
	int** a = matriz.get_matrix();
	for (int i = 0; i < matriz.get_dim(); i++)
	{
		for (int j = 0; j < matriz.get_dim(); j++)
		{
			if (i == 0)
				a[i][j] = j + 1;
			else {
				if (a[i - 1][j] < matriz.get_dim()) {
					a[i][j] = a[i - 1][j] + 1;
				}
				else {
					a[i][j] = 1;
				}
			}
		}
	}
}
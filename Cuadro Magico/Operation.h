/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Mágico
* Fecha de Creación: 08/02/2022
* Fecha de Modificación: 08/02/2022
*/

#pragma once
#include "Matrix.h"

class Operation
{
public:
	/**
	 * @brief Reserva memoria para la matriz
	 *
	 * @param longitud
	 * @return la dirreccion de una matriz
	 */
	int** segment(int);

	/**
	 * @brief Inicializa la matriz en cero
	 *
	 * @param matriz_a
	 * @param longitud
	 */
	void wax(Matrix matriz_a, int longitud);

	/**
	 * @brief Asigna Valores a la matriz
	 *
	 * @param matriz_a
	 * @param longitud
	 */
	void get_into(Matrix, int);

	/**
	 * @brief  Multiplicacion de Matrices
	 *
	 * @param _matrix_a
	 * @param _matrix_b
	 * @param _matrix_c
	 * @param longitud
	 */
	void print(Matrix, int);

	/**
	 * @brief Copia los datos de una matriz
	 *
	 * @param _matrix_a
	 * @param _matrix_b
	 * @param longitud
	 */

	void magic_square(Matrix matriz_a, int longitud);
	/**
	 * @brief Intercambia filas y columnas
	 *
	 * @param matriz_a
	 * @param longitud
	 */

};

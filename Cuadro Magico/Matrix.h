/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josu? Alem?n, Josu? Merino
* Cuadro M?gico
* Fecha de Creaci?n: 08/02/2022
* Fecha de Modificaci?n: 08/02/2022
*/

#pragma once

class Matrix
{
private:
	int** matrix;

public:
	/**
	 * @brief Construct a new Matrix object
	 *
	 */
	Matrix() = default;

	/**
	 * @brief Get the matrix object
	 *
	 * @return int**
	 */
	int** get_matrix();

	/**
	 * @brief Set the matrix object
	 *
	 */
	void set_matrix(int**);
};

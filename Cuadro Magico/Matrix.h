/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Mágico
* Fecha de Creación: 08/02/2022
* Fecha de Modificación: 08/02/2022
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

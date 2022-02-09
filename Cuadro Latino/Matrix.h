/*
* Universidad De las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Latino
* Fecha de Creación: 08/02/2022
* Fecha de Modificación 08/02/2022
*/

#pragma once
class Matrix
{
private:
	int** matrix;
	int dim;
public:
	/**
	 * @brief Construct a new Matrix object
	 *
	 */
	Matrix();

	/**
	 * @brief Construct a new Matrix object
	 *
	 * @param dim
	 */
	Matrix(int dim);

	/**
	 * @brief Get the matrix object
	 *
	 * @return int**
	 */
	int** get_matrix();

	/**
	 * @brief Get the dim object
	 *
	 * @return int
	 */
	int get_dim();

	/**
	 * @brief Set the matrix object
	 *
	 */
	void set_matrix(int**);

	/**
	 * @brief Set the dim object
	 *
	 */
	void set_dim(int);

	/**
	 * @brief reserve memory space
	 *
	 */
	void segmentar();

	/**
	 * @brief assigns 0 to the matrix data
	 *
	 */
	void encerar();

	/**
	 * @brief enter data into the matrix
	 *
	 */
	void ingresar();

	/**
	 * @brief print data to the matrix
	 *
	 */
	void imprimir();
};

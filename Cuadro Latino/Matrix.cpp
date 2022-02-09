/*
* Universidad De las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Latino
* Fecha de Creación: 08/02/2022
* Fecha de Modificación 08/02/2022
*/

#include "Matrix.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Matrix::Matrix()
{
}
Matrix::Matrix(int dim)
{
    this->dim = dim;
}

int** Matrix::get_matrix() {
    return matrix;
}

int Matrix::get_dim() {
    return dim;
}

void Matrix::set_matrix(int** matrix_1) {
    matrix = matrix_1;
}

void Matrix::set_dim(int dim)
{
    this->dim = dim;
}

void Matrix::segmentar() {
    int j;
    set_matrix((int**)malloc(dim * sizeof(int*)));
    for (j = 0; j < dim; j++) {
        *(matrix + j) = (int*)malloc(dim * sizeof(int));
    }
}
void Matrix::encerar() {
    int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            *(*(matrix + i) + j) = 0;
}
void Matrix::ingresar() {
    int i, j;
    cout << "Ingrese los datos:" << endl;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++) {
            cout << "[" << i + 1 << "]" << "[" << j + 1 << "] :";
            cin >> (*(*(this->matrix + i) + j));
        }
}
void Matrix::imprimir() {
    int i, j;
    printf("\n");
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            printf("%d", *(*(matrix + i) + j));
            printf("%*s", j + 5, "");
        }
        printf("\n");
    }

}
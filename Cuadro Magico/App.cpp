/*
* Universidad de las Fuerzas Armadas "ESPE"
* Autores: Josué Alemán, Josué Merino
* Cuadro Mágico
* Fecha de Creación: 08/02/2022
* Fecha de Modificación: 08/02/2022
*/
#include <iostream>
#include "Operation.h"
#include "Matrix.h"
#include "Utils.h"
using namespace std;

int main()
{
    int size, pot;
    Operation op;
    Matrix matrix_1, matrix_2, matrix_r;
    std::cout << "------------------" << std::endl;
    std::cout << "CUADRADO MAGICO\n";
    std::cout << "------------------" << std::endl;
    cout << "Ingrese la dimension del cuadrado";
    size = Utils::Validation::validation_numbers<int>("");
    while (size % 2 == 0) {
        cout << "Ingrese la dimension del cuadrado";
        size = Utils::Validation::validation_numbers<int>("");
    }
    matrix_1.set_matrix(op.segment(size));
    op.wax(matrix_1, size);
    op.magic_square(matrix_1, size);
    op.print(matrix_1, size);
}

/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josu? Alem?n, Josu? Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creaci?n: 16 de febrero del 2022
* Fecha de Modificaci?n: 22 de febrero del 2022
*/

#include <iostream>
#include "application.h"


int main()
{
    std::setlocale(LC_ALL, ".UTF-8");
    return Application::run(ApplicationState::RUN);
}
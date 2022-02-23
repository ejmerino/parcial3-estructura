/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#include <iostream>
#include "application.h"


int main()
{
    std::setlocale(LC_ALL, ".UTF-8");
    return Application::run(ApplicationState::RUN);
}
/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josu? Alem?n, Josu? Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creaci?n: 16 de febrero del 2022
* Fecha de Modificaci?n: 22 de febrero del 2022
*/

#pragma once
#include <string>
#include <iostream>
#include "avl_node.h"

class Trunk
{
public:
    Trunk* prev = nullptr;
    std::string str;
    Trunk(Trunk* prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

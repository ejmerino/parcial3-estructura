#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "Arbol.h"

Nodo* arbol = NULL;
void iniciar();

int main(int argv, char** argc) {

	std::cout << "Altura y Profundidad de un Arbol" << std::endl;
	system("pause");
	system("cls");


	iniciar();

	return 0;
}

void mainMenu() {

	std::cout << "1. Insertar Arbol" << std::endl;
	std::cout << "2. Mostrar Arbol" << std::endl;
	std::cout << "3. Altura del Arbol" << std::endl;
	std::cout << "4. Anchura del Arbol" << std::endl;
	std::cout << "5. Salir" << std::endl;
}
void iniciar() {
	int opc = 0;
	std::string str;

	Arbol objArbol;
	int contador = 0, opcion = 0, dato = 0;
	mainMenu();
	std::cin >> opc;
	do {
		switch (opc) {
			case 1:
				std::cout << "Ingrese un dato: ";
				std::cin >> dato;
				objArbol.insertarNodo(arbol, dato);
				/*llammos al objeto para usar el metodo*/
				std::cout << endl;
				system("pause");
				system("cls");
				break;
			case 2:

				objArbol.mostrar(arbol, contador);
				std::cout << endl;
				system("pause");
				system("cls");
				break;
			case 3:
				if (objArbol.altura(arbol) == 0) {
					std::cout << "No existe arbol construido" << std::endl;
					system("pause");
					system("cls");
					break;
				}
				std::cout << "La altura del arbol es:" << objArbol.altura(arbol) << std::endl;
				system("pause");
				system("cls");
				break;
			case 4:
				if (objArbol.anchura(arbol) == 0) {
					std::cout << "No existe arbol construido" << std::endl;
					system("pause");
					system("cls");
					break;
				}
				std::cout << "Anchura del arbol: " << objArbol.anchura(arbol) << std::endl;
				system("pause");
				system("cls");
				break;
			default:
				break;
		}

		mainMenu();
		std::cin >> opc;
	} while (opc != 5);
}
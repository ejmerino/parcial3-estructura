/*Universidad de las Fuerzas Armadas - ESPE
* Autor: Ednan Josué Merino Calderón
* Tema: Prueba Conjunta Parcial 3
* Órden: Ingresar el número de filas y columnas. Se genera la matriz. Generar por cada celda números aleatorios binarios, de 1 hasta 5 cifras.
* Fecha de Creación: Lunes 21 de febrero del 2022.
* Fecha de Modificación: Lunes 22 de febrero del 2022.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>

using namespace std;

int** segmentar(int, int);
void encerar(int, int);
void ingresar(int**, int, int);
void procesar(int**, int**, int, int);
int generar_aleatorio(int inicio, int fin);
int transformar_a_binario(long int);
void imprimir_matriz_binaria(int**, int, int);

int** segmentar(int d1, int d2) {
	int** mat, i;
	mat = (int**)malloc(d1 * sizeof(int*));
	for (i = 0; i < d1; i++) {
		*(mat + i) = (int*)malloc(d1 * sizeof(int));
	}
	return mat;
}

void encerar(int** mat, int d1, int d2) {
	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < d2; j++) {
			*(*(mat + i) + j) = 0;
		}
	}
	return;
}

void ingresar(int** mat, int d1, int d2)
{
	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < d2; j++) {
			*(*(mat + i) + j) = generar_aleatorio(1, 30);
		}
	}
	return;
}

void procesar(int** m1, int** mr, int d1, int d2) {
	for (int i = 0; i < d1; i++) {
		for (int j = 0; j < d2; j++) {

			*(*(mr + i) + j) = transformar_a_binario(*(*(m1 + i) + j));
		}
	}
}

int generar_aleatorio(int start, int end)
{
	int i = 0;
	i = start + rand() % (end + 1 - start);
	return i;
}

int transformar_a_binario(long int i)
{
	if (i == 0)
		return 0;
	else
		return (i % 2 + 10 * transformar_a_binario(i / 2));
}

void imprimir_matriz_binaria(int** mat, int dim_1, int dim_2)
{
	for (int j = 0; j < dim_2; j++) {
		for (int i = 0; i < dim_1; i++) {
			printf("%d", *(*(mat + i) + j));
			printf("%*s", j + 5, "");
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
	int dim_1, dim_2;
	int** matriz_inicial, ** matriz_resultante;
	char op = { };	
	do {
		cout << "Universidad de las Fuerzas Armadas - ESPE";
		cout << "\nNombre: Josue Merino";
		cout << "\nImprimir una matriz binaria de mxn";
		printf("\n\nIngrese el numero de filas de la matriz: ");
		scanf_s("%d", &dim_1);
		printf("\nIngrese el numero de columnas de la matriz: ");
		scanf_s("%d", &dim_2);
		matriz_inicial = segmentar(dim_1, dim_2);
		matriz_resultante = segmentar(dim_1, dim_2);
		encerar(matriz_inicial, dim_1, dim_2);
		encerar(matriz_resultante, dim_1, dim_2);
		ingresar(matriz_inicial, dim_1, dim_2);
		cout << "\n\n";
		procesar(matriz_inicial, matriz_resultante, dim_1, dim_2);
		cout << "****** Matriz Binaria ******\n\n";
		imprimir_matriz_binaria(matriz_resultante, dim_1, dim_2);
		cout << "\n\n";
		cout << "Desea hacer de nuevo?(S/N): ";
		cin >> op;
		system("cls");
	} while (op=='s' or op=='S');
	
	return 0;
}

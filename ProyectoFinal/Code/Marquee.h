/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once

#include <thread>
#include <iostream>
#include <Windows.h>
#include "String_p.h"


class Marquee {
private:
	const char* content;
	int lenght;
	COORD coord = { 0,0 };
	String_p string_op;

public:
	/*
	* @brief Constructor por default
	* @param
	* @return
	*/
	Marquee() = default;

	/*
	* @brief Constructor
	* @param
	* char cadena de texto a mostrar en la marquesina
	* int longitud de la cadena
	* @return
	*/
	Marquee(const char*, int);

	/*
	* @brief Marquee mueve los caracteres de la marquesina
	* @param
	* int posicion
	* @return char*
	*/
	char* marquee(int);

	/*
	* @brief Muestra el cursor en una posicion especifica
	* @param
	* int posicion x
	* int posicion y
	* @return
	*/
	void print_to(int x, int y);

	/*
	* @brief imprime la marquesina
	* @param
	* @return
	*/
	void show();

	/*
	* @brief se genera el hilo
	* @param
	* @return
	*/
	void animation();

	/**
	* @brief Get the Console Cursor Position object
	*
	* @param hConsoleOutput
	* @return COORD
	*/
	COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

	/**
	 * @brief Ocultar cursor
	 *
	 */
	void cursorHide();
};



Marquee::Marquee(const char* _content, int _lenght) {
	this->content = _content;
	this->lenght = _lenght;
}

char* Marquee::marquee(int position) {
	int counter = 0;
	char* display = (char*)malloc(sizeof(char) * (lenght + 1));
	char* travel = (char*)malloc(sizeof(char) * 256);
	char* temp = (char*)malloc(sizeof(char) * (strlen(content) + 1));
	string_op.strcpy(travel, content);
	cursorHide();
	while (counter < position) {
		temp[counter] = travel[0];
		travel++;
		counter = counter + 1;
	}
	temp[counter + 1] = '\0';
	string_op.strcat(travel, " ");
	string_op.strcat(travel, temp);
	string_op.strncpy(display, travel, lenght);
	display[lenght] = '\0';
	return display;
}

void Marquee::cursorHide()
{
	HANDLE hwnd;
	hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	info.bVisible = 0;
	info.dwSize = 1;

	SetConsoleCursorInfo(hwnd, &info);
}

COORD Marquee::GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void Marquee::show() {
	char* singboard;
	while (1) {
		for (int i = 0; i < lenght; i++) {
			singboard = marquee(i);
			print_to(50, 1);
			std::cout << singboard;
			print_to(150,1);
			std::cout << std::endl;
			Sleep(600);
		}
	}
}

void Marquee::print_to(int x, int y) {
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	fflush(stdout);
}

void Marquee::animation() {
	COORD cord;
	cord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	std::thread first(&Marquee::show, this);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
	fflush(stdout);
	first.detach();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

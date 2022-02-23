/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include <iostream>
typedef void (*Menu_Processing_Function_Ptr)();
class MenuOption
{
public:
	
	MenuOption(unsigned int, const std::string, Menu_Processing_Function_Ptr);	
	unsigned int get_number_option_() { return this->number_option_; };
	std::string get_title_() { return this->title_; };
	Menu_Processing_Function_Ptr get_fuction() { return this->p_processing_function_; };
private:
	unsigned int number_option_;
	const std::string title_;
	Menu_Processing_Function_Ptr p_processing_function_;
};


MenuOption::MenuOption(unsigned int number, const std::string title, Menu_Processing_Function_Ptr fuction)
	: number_option_(number), title_(title), p_processing_function_(fuction)
{

}

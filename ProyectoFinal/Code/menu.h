/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include "menu_option.h"
#include <conio.h>
#include <iostream>

constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_ENTER = 13;
constexpr auto KEY_ESCAPE = 27;

class Menu
{
public:
    
    Menu() = default;
    Menu(std::vector<MenuOption>);
    void navigation();
    void display(size_t);
private:
    std::vector<MenuOption> menu_option_;
    HANDLE console_;
};

Menu::Menu(std::vector<MenuOption> options) : menu_option_(options)
{
    console_ = GetStdHandle(STD_OUTPUT_HANDLE);
}
void Menu::navigation()
{

    if (menu_option_.empty())
    {
        return;
    }
    size_t i{ 1 };
    display(1);
    while (1)
    {
        int option = _getch();

        switch (option)
        {
        case KEY_UP:
        {
            if (i != 1)
            {
                i--;
                display(i);
            }
            break;
        }
        case KEY_DOWN:
        {
            if (i != menu_option_.size())
            {
                i++;
                display(i);
            }
            break;
        }
        case KEY_ENTER:
        {
            system("cls");
            menu_option_.at(i - 1).get_fuction()();
            navigation();
            break;
        }
        case KEY_ESCAPE:
        {
            std::exit(0);
            break;
        }

        default:
            break;
        }
    }
}

void Menu::display(size_t option)
{
    system("cls");
    unsigned int i = 0;
    SetConsoleCursorPosition(console_, { 35, 8 });
    std::cout << "Cancionero 2022 - ALEMAN MERINO" << std::endl;
    while (i < menu_option_.size())
    {
        if (option == i + 1)
        {
            SetConsoleCursorPosition(console_, { 50, short(i + 10) });
            SetConsoleTextAttribute(console_, BACKGROUND_BLUE);
            std::cout << "[" << menu_option_[i].get_number_option_() << "] " << menu_option_[i].get_title_() << std::endl;
            SetConsoleTextAttribute(console_, 15);
        }
        else
        {
            SetConsoleCursorPosition(console_, { 50, short(i + 10) });
            std::cout << "[" << menu_option_[i].get_number_option_() << "] " << menu_option_[i].get_title_() << std::endl;
        }
        i++;
    }
}

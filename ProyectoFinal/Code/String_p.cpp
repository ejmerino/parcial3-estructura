
#include "String_p.h"
#include <iostream>
using namespace std;
char String_p::to_lower(char character)
{
    if (character >= 65 && character <= 90) {
        return character + 32;
    }
    return character;
}

char String_p::to_upper(char character)
{
    if (character >= 97 && character <= 122) {
        return character - 32;
    }
    return character;
}

string String_p::capitalize(string cad)
{
    for (char& c : cad) {
        c = to_upper(c);
    }
    return cad;
}

string String_p::minusculize(string cad)
{
    for (char& c : cad) {
        c = to_lower(c);
    }
    return cad;
}

int String_p::find_character(string cad, char character, int position_initial)
{
    int position_found = -1;
    int cont = 0;
    for (char& c : cad) {
        if (cont >= position_initial && c == character) {
            return cont;
        }
        cont++;
    }

    return position_found;
}

int String_p::find(string cad, string cad_to_find, int position_initial)
{

    string data;
    for (int i = 0; i < length(cad); i++) {
        data = substract(cad, i, length(cad_to_find));
        if (is_equal(data, cad_to_find) && i >= position_initial) {
            return i;
        }
    }
    return -1;
}

int String_p::length(string cad)
{
    int size = 0;
    for (char& c : cad) {
        size++;
    }

    return size;
}

string String_p::substract(string cad, int position_initial, int number_character)
{
    string cad_sub;
    int cont = 0;
    int cont_ch = 1;
    for (char& c : cad) {
        if (cont >= position_initial && cont < (position_initial + number_character)) {
            if (c == ' ') {
                cad_sub += " ";
            }
            else {
                cad_sub += c;
            }

        }
        cont++;

    }
    return cad_sub;
}

bool String_p::is_equal(string cad1, string cad2)
{
    if (length(cad1) != length(cad2)) {
        return false;
    }
    bool flag = false;
    int cont = 0;
    for (int i = 0; i < length(cad1); i++) {
        if (substract(cad1, i, 1) == substract(cad2, i, 1)) {
            cont++;
        }
    }
    if (cont == length(cad1)) {
        flag = true;
    }
    return flag;
}

int String_p::atoi(char character)
{
    if (character >= 48 && character <= 57) {
        return character - 48;
    }
    return 0;
}

int String_p::stoi(string cad)
{
    int r = 0;
    int dato = 0;
    int cont = 0;
    if (substract(cad, 0, 1) == "-") {

        for (char& c : cad) {
            if (cont > 0) {
                dato = atoi(c);
                r = r * 10 + dato;

            }
            cont++;

        }
        r = r * -1;
    }
    else {
        for (char& c : cad) {
            dato = atoi(c);
            r = r * 10 + dato;

        }
    }
    return r;
}

long String_p::stol(string cad)
{
    long r = 0;
    int dato = 0;
    int cont = 0;
    if (substract(cad, 0, 1) == "-") {

        for (char& c : cad) {
            if (cont > 0) {
                dato = atoi(c);
                r = r * 10 + dato;

            }
            cont++;

        }
        r = r * -1;
    }
    else {
        for (char& c : cad) {
            dato = atoi(c);
            r = r * 10 + dato;

        }
    }
    return r;
}

string String_p::reverse(string cad)
{
    string cad_inverse;
    string aux;
    for (char& c : cad) {
        aux.push_back(c);
        cad_inverse = aux + cad_inverse;
        aux = "";

    }
    return cad_inverse;
}

char String_p::at(int position, string cad)
{
    const char* p = cad.c_str();
    char c = ' ';
    if (position <= length(cad)) {
        for (int i = 0; i < position; i++)
        {
            c = *p;
            p++;
        }
    }
    else {
        cout << "La posicion ingresada excede el tamaño de la cadena." << endl;
    }
    return c;
}

char* String_p::strcpy(char* destination, const char* source)
{
    if (destination == NULL) {
        return NULL;
    }

    char* ptr = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return ptr;
}

char* String_p::strcat(char* destination, const char* value)
{
    char* p = destination;

    while (*p != '\0') ++p;

    while (*p++ = *value++);

    return destination;
}

char* String_p::strncpy(char* destination, const char* source, size_t num)
{
    if (destination == NULL) {
        return NULL;
    }
    char* ptr = destination;

    while (*source && num--)
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return ptr;
}
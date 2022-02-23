/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include <string>
#include <regex>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <exception>
#include <Windows.h>
#include <algorithm>
#include "avl_tree.h"


namespace Utils
{
    enum InputType
    {
        USER,
        PASSWORD,
        WORD,
        OTHER
    };

    class Validation
    {
    public:
        static inline bool string_is_valid(const std::string& str);
        static inline int read_int(std::string, int min_digits = 1, int max_digits = 20);
        static inline std::string read_string(std::string label, int state, size_t size = 20);
        static inline bool is_ASCII(std::string& s);
        static inline bool format_password(std::string& password);
        static inline bool string_valid(std::string& str);
    };

    class Login
    {
    public:
        static inline bool login(std::string& user, std::string& password);
        static inline void encrypt(std::string& password);
        static inline void decrypt(std::string& password);
        static inline std::string masking_password(std::string label);
    };
    class File
    {
    public:
        static inline bool write_file(std::string& user, std::string& password);
        static inline bool read_file(std::string& user, std::string& password);
        static inline bool update_file(std::string& user, std::string& password);
        static inline void cargar_arbol(AvlTree& tree, std::string file_path, int type);
        static inline void guardar_arbol(AvlTree& tree, std::string file_path);
        static inline bool exists_file(const std::string name);
    };

    class Generator
    {
    public:
        static inline void generate_admins(std::string& user, std::string& password);
        static inline void remove_number(std::string& str);
    };

    ///////////////////////////////////////////////////////////////////////////
    inline bool Validation::string_is_valid(const std::string& str)
    {
        //regular expression to validate a string
        std::regex reg(
            "(?:[[:space:]]*"
            "([[:alpha:]_]+)"
            "[[:space:]]*)+");
        return std::regex_match(str, reg);
    }

    inline int Validation::read_int(std::string label, int min_digits, int max_digits)
    {
        int input;
        do
        {
            std::cout << label;
            std::cin >> input;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }

            int total_digits = static_cast<int>((input == 0 ? 1 : std::log10(std::abs(input)) + 1));

            if (total_digits < min_digits || total_digits > max_digits)
            {
                if (min_digits == max_digits)
                {
                    std::cout << std::endl
                        << "[ingrese un valor de " << max_digits << " digitos" << std::endl;
                }
                else
                {
                    std::cout << std::endl
                        << "[ingrese un valor entre "
                        << min_digits << " y " << max_digits << " digitos]" << std::endl;
                }
                continue;
            }
            break;
        } while (true);

        return input;
    }

    inline std::string Validation::read_string(std::string label, int state, size_t size)
    {
        std::string input;
        if (state == InputType::USER)
        {
            std::cout << label;
            std::getline(std::cin, input, '\n');
            std::string temp = input;
            Generator::remove_number(temp);

            while (!std::all_of(temp.begin(), temp.end(), ::islower) ||
                !Validation::is_ASCII(input) ||
                !(input.size() <= size))
            {
                std::cout << "\nFormato incorrecto" << std::endl;
                input.clear();
                temp.clear();
                std::cout << label;
                std::getline(std::cin, input, '\n');
                temp = input;
                Generator::remove_number(temp);
            }
        }
        else if (state == InputType::PASSWORD)
        {
            std::cout << label;
            input = Login::masking_password(input);
            while (!Validation::format_password(input) || !(input.size() < size))
            {
                std::cout << "\nFormato incorrecto." << std::endl;
                input.clear();
                std::cout << label;
                input = Login::masking_password(input);
            }
        }
        else if (state == InputType::WORD)
        {
            std::cout << label;
            std::getline(std::cin, input, '\n');
            while (!Validation::string_valid(input))
            {
                std::cout << "\nFormato incorrecto." << std::endl;
                input.clear();
                std::cout << label;
                std::getline(std::cin, input, '\n');
            }
        }

        return input;
    }

    inline bool Validation::is_ASCII(std::string& s)
    {
        return !std::any_of(s.begin(), s.end(), [](char c)
            { return static_cast<unsigned char>(c) > 127; });
    }

    inline bool Validation::format_password(std::string& password)
    {
        for (char& c : password)
        {
            if (isdigit(c) || isalpha(c))
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    inline bool Validation::string_valid(std::string& str)
    {
        return std::all_of(str.begin(), str.end(), ::isalpha);
    }

    inline bool Login::login(std::string& user, std::string& password)
    {
        std::string temp_user = user;
        std::string temp_password;
        if (Utils::File::read_file(temp_user, temp_password))
        {
            if (password == temp_password)
            {
                return true;
            }
        }
        return false;
    }

    inline void Login::encrypt(std::string& password)
    {
        std::string encrypted_password = "";
        std::string::iterator it = password.begin();

        for (; it != password.end(); ++it)
        {
            encrypted_password += static_cast<char>(*it + 1);
        }
        password = encrypted_password;
    }

    inline void Login::decrypt(std::string& password)
    {
        std::string decrypted_password = "";
        std::string::iterator it = password.begin();
        for (; it != password.end(); ++it)
        {
            decrypted_password += static_cast<char>(*it - 1);
        }
        password = decrypted_password;
    }

    inline std::string Login::masking_password(std::string label)
    {

        std::string result;
        DWORD mode, count;
        HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
        if (!GetConsoleMode(ih, &mode))
            throw std::runtime_error(
                "getpassword: You must be connected to a console to use this program.\n");
        SetConsoleMode(ih, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

        WriteConsoleA(oh, label.c_str(), label.length(), &count, NULL);
        char c;
        while (ReadConsoleA(ih, &c, 1, &count, NULL) && (c != '\r') && (c != '\n'))
        {
            if (c == '\b')
            {
                if (result.length())
                {
                    WriteConsoleA(oh, "\b \b", 3, &count, NULL);
                    result.erase(result.end() - 1);
                }
            }
            else
            {
                WriteConsoleA(oh, "*", 1, &count, NULL);
                result.push_back(c);
            }
        }

        SetConsoleMode(ih, mode);
        return result;
    }

    inline bool File::write_file(std::string& user, std::string& password)
    {

        std::ofstream file("user.txt", std::ios::out | std::ios::binary | std::ios::app);
        Utils::Login::encrypt(password);
        if (file.is_open())
        {
            file << user << ":" << password << std::endl;
            file.close();
        }
        else
        {
            return false;
        }
        return true;
    }
    inline bool File::read_file(std::string& user, std::string& password)
    {
        std::ifstream file("user.txt", std::ios::in | std::ios::binary);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line, '\n'))
            {
                std::string::size_type pos = line.find(':');
                if (pos != std::string::npos)
                {
                    std::string user_read = line.substr(0, pos);
                    if (user_read == user)
                    {
                        user = user_read;
                        password = line.substr(pos + 1);
                        Utils::Login::decrypt(password);
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            file.close();
        }
        return false;
    }

    inline bool File::update_file(std::string& user, std::string& password)
    {
        std::ofstream file("user.txt", std::ios::out | std::ios::binary);
        Utils::Login::encrypt(password);
        if (file.is_open())
        {
            file << user << ":" << password << std::endl;
            file.close();
        }
        else
        {
            return false;
        }
        return true;
    }

    inline void File::cargar_arbol(AvlTree& tree, std::string file_path, int type)
    {
        enum PIEZA
        {
            CANCION = 1,
            ARTISTA = 2,
        };
        std::ifstream file(file_path, std::ios::in);
        std::string line;
        std::string artista;
        std::string cancion;
        while (!file.eof())
        {
            std::getline(file, line);
            cancion = line.substr(0, line.find(","));
            artista = line.substr(line.find(",") + 1, line.length());
            if (type == PIEZA::CANCION)
            {
                tree.insert(artista, cancion);
            }
            if (type == PIEZA::ARTISTA)
            {
                tree.insert(cancion, artista);
            }
        }
        file.close();
    }

    inline void File::guardar_arbol(AvlTree& tree, std::string file_path)
    {
        std::wofstream file(file_path, std::ios::out | std::ios::binary);
        tree.for_each_inorder([&](AvlNode* node)
            {
                if (file.is_open())
                {
                    file << node->cancion().data() << "," << node->artista().data() << "\n";
                };
            });
        file.close();
    }


    inline bool File::exists_file(const std::string name)
    {
        std::ifstream f(name.c_str());
        return f.good();
    }
    
    inline void Generator::generate_admins(std::string& new_user, std::string& new_password)
    {
        Utils::File::write_file(new_user, new_password);
    }

    inline void Generator::remove_number(std::string& str)
    {
        std::string result;
        for (char& c : str)
        {
            if (!isdigit(c))
            {
                result += c;
            }
        }
        str = result;
    }
}
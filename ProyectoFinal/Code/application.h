/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include "utils.h"
#include <iostream>
#include <string>
#include "avl_tree.h"
#include <vector>
#include <thread>
#include "menu.h"
#include "Marquee.h"


void marquee_limit(std::string text, size_t limit) {
    bool ciclo = true;
    while (ciclo)
    {
        std::string temp = text;
        text.erase(0, 1);
        text += temp[0];
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        SetConsoleTitleA(text.substr(0, limit).c_str());
        if (GetAsyncKeyState(VK_RETURN)) {
            ciclo = false;
            break;
        }
    }
}

class AvlTree;

enum ApplicationState
{
    RUN,
    STOP,
    RUNNING
};

enum Pieza_musical
{
    CANCION = 1,
    ARTISTA = 2
};

class Application
{
public:
    static inline int run(int);
    static inline void exit();

private:
    static inline void main_menu();
    static inline void administrator_menu();
    static inline void user_menu();
    static inline void init_tree(AvlTree&, int state, int type);
    static inline void encontrar_cancion();
    static inline void lista_canciones();
    static inline void nuevo_admin();
    static inline void agregar_cancion();
    static inline void eliminar_cancion();

};

int inline Application::run(int state)
{
    //std::cout << "Cargando el cancionero" << std::endl;
    AvlTree tree{};
    AvlTree temp{};
    
    if (state == ApplicationState::RUN)
    {
        init_tree(tree, ApplicationState::RUN, Pieza_musical::CANCION);
        init_tree(temp, ApplicationState::RUN, Pieza_musical::ARTISTA);
        //std::this_thread::sleep_for(std::chrono::milliseconds(0010));
        system("cls");
        main_menu();
    }
    return 0;
}

inline void Application::main_menu()
{
    /*Marquee mark1("Universidad de Las Fuerzas Armadas - ESPE", 27);
    mark1.animation();*/
    while (true)
    {
       std::vector<MenuOption> menu_item{
       {1, "ADMINISTRADOR", administrator_menu},
       {2, "USUARIO", user_menu},
       {3, "SALIR", exit} };
       Menu menu{ menu_item };
       menu.navigation();            
    }
}

inline void Application::administrator_menu()
{
    std::cout << "Administrador" << std::endl;
    std::string user = Utils::Validation::read_string("Ingrese el usuario: ", Utils::InputType::USER);
    std::string password = Utils::Validation::read_string("Ingrese la contrasena: ", Utils::InputType::PASSWORD);
    std::cout << std::endl;

    if (Utils::Login::login(user, password))
    {
        std::vector<MenuOption> menu_item{
            {1, "BUSCAR UNA CANCION", encontrar_cancion},
            {2, "MOSTRAR CANCIONES", lista_canciones},
            {3, "INGRESAR UNA NUEVA CANCION", agregar_cancion},
            {4, "ELIMINAR UNA CANCION", eliminar_cancion},
            {5, "CREAR ADMINISTRADOR", nuevo_admin},
            {6, "REGRESAR", main_menu},
            {7, "CERRAR SESION", exit} };

        Menu menu{ menu_item };
        menu.navigation();
    }
    else
    {
        if (!Utils::File::exists_file("user.txt"))
        {
            std::cout << "Todavia no existe Administrador" << std::endl;
            std::string user = Utils::Validation::read_string("Ingrese un nombre de usuario: ", Utils::InputType::USER);
            std::string password = Utils::Validation::read_string("Ingrese la clave: ", Utils::InputType::PASSWORD);
            Utils::Generator::generate_admins(user, password);
            std::cout << "\nAdministrador creado" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            main_menu();
        }
        std::cout << "\nUSUARIO O CONTRASENA INCORRECTO" << std::endl;
        std::cin.get();
        std::cout << "\033[2J\033[1;1H";
        main_menu();
    }
}

inline void Application::user_menu()
{
    std::vector<MenuOption> menu_item{
        {1, "BUSCAR UNA CANCION", encontrar_cancion},
        {2, "MOSTRAR CANCIONES", lista_canciones},
        {3, "REGRESAR", main_menu},
    };

    Menu menu{ menu_item };
    menu.navigation();
}

inline void Application::exit()
{
    AvlTree tree;
    init_tree(tree, ApplicationState::RUNNING, Pieza_musical::CANCION);
    std::cout << "Cerrando Sesion..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    init_tree(tree, ApplicationState::STOP, Pieza_musical::CANCION);
    std::cout << "Gracias!" << std::endl;
    std::exit(0);
}

inline void Application::init_tree(AvlTree& tree, int state, int type)
{

    static AvlTree temp_tree_artista;
    static AvlTree temp_tree_cancion;
    if (state == ApplicationState::RUN)
    {
        if (type == Pieza_musical::CANCION)
        {
            Utils::File::cargar_arbol(temp_tree_cancion, "datos.txt", Pieza_musical::CANCION);
        }
        if (type == Pieza_musical::ARTISTA)
        {
            Utils::File::cargar_arbol(temp_tree_artista, "datos.txt", Pieza_musical::ARTISTA);
        }
    }
    else if (state == ApplicationState::RUNNING)
    {
        if (type == Pieza_musical::ARTISTA)
        {
            tree = temp_tree_artista;
        }
        if (type == Pieza_musical::CANCION)
        {
            tree = temp_tree_cancion;
        }
    }
    else if (state == ApplicationState::STOP)
    {
        Utils::File::guardar_arbol(tree, "datos.txt");
    }
}

inline void Application::encontrar_cancion()
{
    enum Pieza
    {
        CANCION = 1,
        ARTISTA = 2
    };
    int option = 0;
    while (true)
    {
        std::cout << "En que formato desea visualizar la busqueda?\n"
            << std::endl;
        std::cout << "[1] CANCION-ARTISTA" << std::endl;
        std::cout << "[2] ARTISTA-CANCION" << std::endl;
        option = (Utils::Validation::read_int("\nIngrese la opcion: ", 1, 1));

        if (option == CANCION || option == ARTISTA)
        {
            break;
        }
        std::cout << "\033[2J\033[1;1H";
    }
    std::cin.ignore();
    std::string word = Utils::Validation::read_string(
        "Ingrese la cancion o artista a buscar: ", Utils::InputType::WORD);
    AvlTree tree;
    Application::init_tree(tree, ApplicationState::RUNNING, Pieza_musical::CANCION);
    if (tree.has(word))
    {
        std::vector<AvlNode*> node = tree.find(word);

        if (option == CANCION)
        {
            std::cout << "\nTotal de canciones encontradas: " << node.size() << std::endl;
            int i = 1;
            for (auto& n : node)
            {
                std::cout << "[" << i << "] " << n->cancion() << ": "
                    << n->artista() << std::endl;
                i++;
            }
        }
        if (option == ARTISTA)
        {
            std::cout << "\nTotal de canciones encontradas: " << node.size() << std::endl;
            int i = 1;
            for (auto& n : node)
            {
                std::cout << "[" << i << "] " << n->artista() << ": "
                    << n->cancion() << std::endl;
                i++;
            }
        }
        node.clear();
    }
    else
    {
        std::cout << "\nNO EXISTE LA CANCION" << std::endl;
    }
    std::cin.get();
    std::cout << "\033[2J\033[1;1H";
}

inline void Application::lista_canciones()
{
    enum TypeTraversal
    {
        PREORDER = 1,
        INORDER = 2,
        POSTORDER = 3
    };
    enum LanguageType
    {
        CANCION = 1,
        ARTISTA = 2
    };

    int option = 0;
    int op = 0;
    while (true)
    {
        std::cout << "LISTA DE CANCIONES" << std::endl;
        std::cout << "Como desea mostrar las canciones?\n" << std::endl;
        std::cout << "1.- Cancion/Artista" << std::endl;
        std::cout << "2.- Artista/Cancion" << std::endl;
        op = (Utils::Validation::read_int("\nIngrese la opcion: ", 1, 1));
        if (op == CANCION || op == ARTISTA)
        {
            break;
        }
        system("cls");
    }
    AvlTree tree_artista;
    AvlTree tree_cancion; 
    Application::init_tree(tree_artista, ApplicationState::RUNNING, Pieza_musical::ARTISTA);
    Application::init_tree(tree_cancion, ApplicationState::RUNNING, Pieza_musical::CANCION);     
        if (op == CANCION)
        {
            tree_cancion.for_each_inorder([](AvlNode* node)
                { std::cout << node->cancion() << ": " << node->artista() << std::endl; });
            std::cout << "\nTOTAL DE CANCIONES: " << tree_cancion.get_size() << std::endl;          
        }
        if (op == ARTISTA)
        {
            tree_artista.for_each_inorder([](AvlNode* node)
                { std::cout << node->cancion() << ": " << node->artista() << std::endl; });
            std::cout << "\nTOTAL DE CANCIONES: " << tree_artista.get_size() << std::endl;            
        }   
    system("pause");
}

inline void Application::nuevo_admin()
{
    std::cout << "Desea Crear un nuevo administrador[s/n]: ";
    char option = 0;
    std::cin >> option;
    std::cin.ignore();
    if (option == 's' || option == 'S')
    {
        system("cls");
        std::cout << "Ingrese los datos del administrador principal: " << std::endl;
        std::string user_admin = Utils::Validation::read_string("Ingrese el usuario: ", Utils::InputType::USER);
        std::string password_admin = Utils::Validation::read_string("Ingrese la contrasena: ", Utils::InputType::PASSWORD);
        std::cout << std::endl;

        if (Utils::Login::login(user_admin, password_admin))
        {
            std::string new_user = Utils::Validation::read_string("Crear usuario: ", Utils::InputType::USER);
            std::string new_password = Utils::Validation::read_string("Ingrese la contraseña: ", Utils::InputType::PASSWORD);
            Utils::Generator::generate_admins(new_user, new_password);
            std::cout << "Administrado creado con exito" << std::endl;
            main_menu();
        }
        else
        {
            std::cout << "Credenciales incorrectas, regresando al menu principal. " << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            administrator_menu();
        }
    }
    else
    {
        administrator_menu();
    }
}

inline void Application::agregar_cancion()
{
    AvlTree tree;
    Application::init_tree(tree, ApplicationState::RUNNING, Pieza_musical::CANCION);
    while (true)
    {
        std::cout << "Ingrese la cancion a insertar." << std::endl;

        std::string artista = Utils::Validation::read_string("Artista: ", Utils::InputType::WORD);
        std::string cancion = Utils::Validation::read_string("Cancion: ", Utils::InputType::WORD);

        if (tree.has(cancion))
        {
            std::cout << "La cancion ya existe ." << std::endl;
        }
        else
        {
            tree.insert(artista, cancion);
        }
        std::cout << "Desea agregar otra cancion[s/n]: ";
        char option = 0;
        std::cin >> option;
        std::cin.ignore();
        if (option == 's' || option == 'S')
        {
            continue;
        }
        else
        {
            break;
        }
    }    
}

inline void Application::eliminar_cancion()
{

    while (true)
    {
        std::cout << "ELIMINAR CANCIONES" << std::endl;
        std::cout << "Ingrese la cancion a eliminar." << std::endl;
        std::string word = Utils::Validation::read_string("\Cancion: ", Utils::InputType::WORD);
        AvlTree tree;
        Application::init_tree(tree, ApplicationState::RUNNING, Pieza_musical::CANCION);

        if (tree.has(word))
        {
            tree.remove(word);
            std::cout << "ELIMINACION EXITOSA" << std::endl;
        }
        else
        {
            std::cout << "LA CANCION INGRESADA NO EXISTE" << std::endl;
        }
        std::cout << "\nDesea eliminar otra palabra[s/n]: ";
        char option = 0;
        std::cin >> option;
        std::cin.ignore();
        if (option == 's' || option == 'S')
        {
            continue;
        }
        else
        {
            break;
        }
    }
}
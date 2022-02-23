/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include "avl_node.h"
#include <string>
#include <functional>
#include <stack>
#include <algorithm>
#include "trunk.h"
#include <vector>

class Trunk;
class AvlNode;

class AvlTree
{
public:
    AvlTree() = default;
    inline void insert(std::string artista, std::string cancion);
    inline void remove(std::string);
    inline bool has(std::string);
    inline std::vector<AvlNode*> find(std::string word);
    inline void modify(std::string, std::string);
    inline void for_each_inorder(std::function<void(AvlNode*)>);
    inline void for_each_preorder(std::function<void(AvlNode*)>);
    inline void for_each_postorder(std::function<void(AvlNode*)>);
    inline void print_tree(AvlNode*, Trunk*, bool, int);
    inline void show_trunks(Trunk* p);
    inline AvlNode* rotar_izq(AvlNode*);
    inline AvlNode* rotar_der(AvlNode*);
    inline int max_height(int a, int b);
    inline int find_height(AvlNode*);
    inline int balance_factor(AvlNode*);
    inline AvlNode* max_value_node(AvlNode*);
    inline std::string infer_pieza(std::string);
    inline void to_lower_case(std::string&);
    inline int get_size() { return size; };
    inline AvlNode* get_root() { return root; };

private:
    AvlNode* insertAvl(AvlNode*, std::string, std::string);
    AvlNode* borrarAvl(AvlNode*, std::string);
    AvlNode* root = nullptr;
    int size = 0;
};

inline void AvlTree::insert(std::string artista, std::string cancion)
{
    to_lower_case(cancion);
    to_lower_case(artista);
    root = insertAvl(root, artista, cancion);
}

inline void AvlTree::remove(std::string word)
{
    if (has(word))
    {
        word = infer_pieza(word);
        to_lower_case(word);
        root = borrarAvl(root, word);
    }
}

inline bool AvlTree::has(std::string word)
{
    return find(word) != std::vector<AvlNode*>{};
}

inline std::vector<AvlNode*> AvlTree::find(std::string word)
{
    if (root == nullptr)
    {
        return std::vector<AvlNode*>{};
    }
    to_lower_case(word);
    std::vector<AvlNode*> temp;
    for_each_inorder([&](AvlNode* node)
        {
            if (node->cancion() == word ||
                node->artista() == word)
            {
                temp.push_back(node);
            }
        });
    return temp;
}

inline void AvlTree::modify(std::string word, std::string new_word)
{
    if (root)
    {
        to_lower_case(word);
        to_lower_case(new_word);
        root = borrarAvl(root, word);
        root = insertAvl(root, new_word, new_word);
    }
    else
    {
        std::cout << "La palabra \"" << word << "\" no se encuentra en el diccionario." << std::endl;
    }
}

inline AvlNode* AvlTree::insertAvl(AvlNode* current, std::string artista, std::string cancion)
{
    if (current == nullptr)
    {
        size++;
        return new AvlNode(cancion, artista);
    }

    if (cancion < current->cancion())
    {
        current->set_left(insertAvl(current->left(), artista, cancion));
    }
    else if (cancion >= current->cancion())
    {
        current->set_right(insertAvl(current->right(), artista, cancion));
    }

    current->set_height(max_height(find_height(current->left()), find_height(current->right())) + 1);

    //* Obtiene el nuevo factor de equilibrio
    int bf = balance_factor(current);

    //* Rotacion simple a la derecha
    if (bf > 1 && cancion < current->left()->cancion())
    {
        return rotar_der(current);
    }

    //* Rotacion simple a la izquierda
    if (bf < -1 && cancion > current->right()->cancion())
    {
        return rotar_izq(current);
    }

    //* Rotacion izquierda derecha
    if (bf > 1 && cancion > current->left()->cancion())
    {
        current->set_left(rotar_izq(current->left()));
        return rotar_der(current);
    }

    //* Rotacion derecha izquierda
    if (bf < -1 && cancion < current->right()->cancion())
    {
        current->set_right(rotar_der(current->right()));
        return rotar_izq(current);
    }
    return current;
}

inline AvlNode* AvlTree::borrarAvl(AvlNode* current, std::string word)
{
    if (current == nullptr)
    {
        return current;
    }
    if (word < current->cancion())
    {
        current->set_left(borrarAvl(current->left(), word));
    }
    else if (word > current->cancion())
    {
        current->set_right(borrarAvl(current->right(), word));
    }
    else
    {
        if ((current->left() == nullptr) || (current->right() == nullptr))
        {
            AvlNode* temp = nullptr;

            if (temp == current->left())
            {
                temp = current->right();
            }
            else
            {
                temp = current->left();
            }

            //* Si no hay hijos, se elimina el nodo
            if (temp == nullptr)
            {
                current = nullptr;
                size--;
            }
            else
            {
                current = temp;
            }
        }
        else
        {
            //* Si hay hijos, se busca el nodo más alto
            AvlNode* temp = max_value_node(current->left());

            //* Se asigna el valor del nodo más alto a la raiz
            current->set_cancion(temp->cancion());
            current->set_artista(temp->artista());

            current->set_left(borrarAvl(current->left(), temp->cancion()));
        }
    }

    if (current == nullptr)
    {
        return { current };
    }

    current->set_height(max_height(find_height(current->left()), find_height(current->right())) + 1);

    //* Obtiene el nuevo factor de equilibrio
    int bf = balance_factor(current);
    //* Rotacion simple a la derecha
    if (bf > 1 && balance_factor(current->left()) >= 0)
    {
        return rotar_der(current);
    }

    //* Rotacion simple a la izquierda
    if (bf < -1 && balance_factor(current->right()) <= 0)
    {
        return rotar_izq(current);
    }
    //* Rotacion izquierda derecha
    if (bf > 1 && balance_factor(current->left()) < 0)
    {
        current->set_left(rotar_izq(current->left()));
        return rotar_der(current);
    }
    //* Rotacion derecha izquierda
    if (bf < -1 && balance_factor(current->right()) > 0)
    {
        current->set_right(rotar_der(current->right()));
        return rotar_izq(current);
    }

    return current;
}

/////////////////////////////////////////////////////////////////////////////

inline void AvlTree::for_each_inorder(std::function<void(AvlNode*)> callback)
{
    //* Construct the following tree
    //*
    //*      5
    //*     / \
    //*    3   7
    //*   / \   \
    //*  1   4   8
    //*        / \
    //*       6   9
    //*
    //* inorder traversal should be:
    //* 1, 3, 4, 5, 6, 7, 8, 9
    //*
    if (root == nullptr)
    {
        return;
    }
    std::stack<AvlNode*> stack;
    AvlNode* current = root;
    while (!stack.empty() || current != nullptr)
    {
        if (current != nullptr)
        {
            stack.push(current);
            current = current->left();
        }
        else
        {
            current = stack.top();
            stack.pop();
            callback(current);
            current = current->right();
        }
    }
}

inline void AvlTree::for_each_preorder(std::function<void(AvlNode*)> callback)
{
    if (root == nullptr)
    {
        return;
    }
    std::stack<AvlNode*> stack;
    stack.push(root);
    while (!stack.empty())
    {
        AvlNode* current = stack.top();
        stack.pop();
        callback(current);
        if (current->right() != nullptr)
        {
            stack.push(current->right());
        }
        if (current->left() != nullptr)
        {
            stack.push(current->left());
        }
    }
}

inline void AvlTree::for_each_postorder(std::function<void(AvlNode*)> callback)
{
    if (root == nullptr)
    {
        return;
    }
    std::stack<AvlNode*> stack;
    stack.push(root);
    std::stack<AvlNode*> postorder;
    while (!stack.empty())
    {
        AvlNode* current = stack.top();
        stack.pop();
        postorder.push(current);
        if (current->left() != nullptr)
        {
            stack.push(current->left());
        }
        if (current->right() != nullptr)
        {
            stack.push(current->right());
        }
    }
    while (!postorder.empty())
    {
        callback(postorder.top());
        postorder.pop();
    }
}

inline void AvlTree::print_tree(AvlNode* current, Trunk* prev, bool isLeft, int melodia)
{
    if (current == nullptr)
    {
        return;
    }

    std::string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    print_tree(current->right(), trunk, true, melodia);

    if (!prev)
    {
        trunk->str = "----";
    }
    else if (isLeft)
    {
        trunk->str = ".----";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`----";
        prev->str = prev_str;
    }

    show_trunks(trunk);
    if (melodia == 1)
    {
        printf("\033[%d;2;%d;%d;%dm%s\033[0;00m", 38, 224, 86, 253, current->cancion().c_str());
        std::cout << std::endl;
    }
    if (melodia == 2)
    {
        printf("\033[%d;2;%d;%d;%dm%s\033[0;00m", 38, 24, 220, 255, current->artista().c_str());
        std::cout << std::endl;
    }

    if (prev)
    {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    print_tree(current->left(), trunk, false, melodia);
}

inline void AvlTree::show_trunks(Trunk* p)
{
    if (p == nullptr)
    {
        return;
    }

    show_trunks(p->prev);
    printf("\033[%d;2;%d;%d;%dm%s\033[0;00m", 38, 255, 255, 255, p->str.c_str());
}

inline AvlNode* AvlTree::rotar_izq(AvlNode* node)
{
    AvlNode* current = node->right();
    AvlNode* temp = current->left();
    current->set_left(node);
    node->set_right(temp);
    node->set_height(max_height(find_height(node->left()), find_height(node->right())) + 1);
    current->set_height(max_height(find_height(current->left()), find_height(current->right())) + 1);
    return current;
}

inline AvlNode* AvlTree::rotar_der(AvlNode* current)
{
    AvlNode* nueva_raiz = current->left();
    AvlNode* temp = nueva_raiz->right();

    nueva_raiz->set_right(current);
    current->set_left(temp);

    current->set_height(max_height(find_height(current->left()), find_height(current->right())) + 1);
    nueva_raiz->set_height(max_height(find_height(nueva_raiz->left()), find_height(nueva_raiz->right())) + 1);
    return nueva_raiz;
}

inline int AvlTree::max_height(int a, int b)
{
    return (a > b) ? a : b;
}

inline int AvlTree::find_height(AvlNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height();
}

inline int AvlTree::balance_factor(AvlNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return find_height(node->left()) - find_height(node->right());
}

inline AvlNode* AvlTree::max_value_node(AvlNode* node)
{
    AvlNode* max = node;
    while (max->right() != nullptr)
    {
        max = max->right();
    }
    return max;
}

inline std::string AvlTree::infer_pieza(std::string word)
{
    std::string pieza_artistica;
    for_each_inorder([&](AvlNode* node)
        {
            if ((node->cancion() == word) ||
                (node->artista() == word))
            {
                pieza_artistica = node->cancion();
            }
        });
    return pieza_artistica;
}

inline void AvlTree::to_lower_case(std::string& word)
{
    std::transform(word.begin(), word.end(), word.begin(),
        [](unsigned char c)
        { return std::tolower(c); });
}

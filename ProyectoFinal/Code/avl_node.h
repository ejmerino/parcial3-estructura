/*Universidad de Las Fuerzas Armadas - ESPE
* Autores: Josué Alemán, Josué Merino
* PROYECTO 3er PARCIAL - TCANCIONERO 2022
* Fecha de Creación: 16 de febrero del 2022
* Fecha de Modificación: 22 de febrero del 2022
*/

#pragma once
#include <string>

class AvlNode
{
public:
    AvlNode(std::string, std::string);
    AvlNode(std::string, std::string, int);  
    AvlNode(std::string, std::string, int, AvlNode*, AvlNode*);
    inline AvlNode* left();
    inline AvlNode* right();
    inline void set_left(AvlNode*);
    void set_right(AvlNode* n);
    inline void set_height(int);
    inline void set_cancion(std::string);
    inline void set_artista(std::string);
    inline int height();
    inline std::string cancion();
    inline std::string artista();

private:
    AvlNode* _left = nullptr;
    AvlNode* _right = nullptr;
    std::string _cancion;
    std::string _artista;
    int _height{ 1 };
};

AvlNode::AvlNode(std::string cancion, std::string artista)
    : _cancion(cancion), _artista(artista), _height(1)
{
}

AvlNode::AvlNode(std::string cancion, std::string artista, int height)
    : _cancion(cancion), _artista(artista), _height(height)
{
}

AvlNode::AvlNode(std::string cancion, std::string artista, int height, AvlNode* left, AvlNode* right)
    : _cancion(cancion), _artista(artista), _height(height)
{
    _left = left;
    _right = right;
}

inline AvlNode* AvlNode::left()
{
    return _left;
}

inline AvlNode* AvlNode::right()
{
    return _right;
}

inline void AvlNode::set_left(AvlNode* node)
{
    _left = node;
}

inline void AvlNode::set_right(AvlNode* node)
{
    _right = node;
}

inline int AvlNode::height()
{
    return _height;
}

inline void AvlNode::set_height(int height)
{
    _height = height;
}

inline std::string AvlNode::cancion()
{
    return _cancion;
}

inline std::string AvlNode::artista()
{
    return _artista;
}

inline void AvlNode::set_cancion(std::string cancion)
{
    _cancion = cancion;
}

inline void AvlNode::set_artista(std::string artista)
{
    _artista = artista;
}


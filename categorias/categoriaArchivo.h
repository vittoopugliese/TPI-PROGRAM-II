#pragma once
#include "categoria.h"

class CategoriaArchivo {
    private:
        char _nombreArchivo[30];
    public:
        CategoriaArchivo(const char *nombreArchivo);
        bool guardarArchivo(Categoria categoria);
        int contarRegistros();
        Categoria leerRegistro(int posicion);
        int buscar(int idCategoria);
        bool modificar(Categoria categoria, int posicion);
};

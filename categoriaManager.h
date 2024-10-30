#pragma once
using namespace std;
#include "categoriaArchivo.h"

class CategoriaManager {
    private:
        CategoriaArchivo _archivo = CategoriaArchivo("categorias.dat");
        void mostrarTodos();
        void modificar();

    public:
        void menu();
        Categoria Cargar();
        void Mostrar (Categoria categoria);
        void buscarPorIdCategoria(); // a definir
        void baja();
};

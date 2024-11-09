#pragma once
using namespace std;
#include "categoriaArchivo.h"

class CategoriaManager {
    private:
        CategoriaArchivo _archivo = CategoriaArchivo("categorias.dat");
        void modificar();
    public:
        Categoria Cargar();
        void Mostrar (Categoria categoria);
        void baja(); // Eliminar
        void mostrarTodos();
        void buscarPorIdCategoria(); // a definir
        int getTipoDeMovimientoFromIdCategoria(int idCategoria);
        void mostrarTodasInline();
        string getNombreCategoria(int idCategoria);
        void menu(const Usuario &user);
};

#pragma once
using namespace std;
#include "categoria.h"
#include "categoriaArchivo.h"
#include "usuarioManager.h"
#include "funcionesGlobales.h"
#include <cstring>

class CategoriaManager {
    private:
        CategoriaArchivo _archivo = CategoriaArchivo("categorias.dat");
        void modificar();
    public:
        void menu(const Usuario &user);
        Categoria cargar();
        void mostrar (Categoria categoria);
        void baja(); // Eliminar
        void mostrarTodos();
        void buscarPorIdCategoria(); // a definir
        int getTipoDeMovimientoFromIdCategoria(int idCategoria);
        void mostrarTodasInline();
        string getNombreCategoria(int idCategoria);
        int contarCategoriasActivas();
};

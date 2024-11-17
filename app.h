#pragma once
#include "./movimientos/movimientoManager.h"
#include "./categorias/categoriaManager.h"
#include "informes/informeManager.h"
#include "usuarios/usuarioManager.h"

class App {
private:
    MovimientoManager subMenuMovimientos;
    CategoriaManager subMenuCategorias;
    InformeManager subMenuInformes;
public:
    void menuLogin();
    void MenuPrincipal(const Usuario &user);
};

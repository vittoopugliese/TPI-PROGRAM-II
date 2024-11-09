#pragma once
#include "movimientoManager.h"
#include "categoriaManager.h"
#include "informeManager.h"
#include "usuarioManager.h"

class App {
private:
    MovimientoManager subMenuMovimientos;
    CategoriaManager subMenuCategorias;
    InformeManager subMenuInformes;
public:
    void menuLogin();
    void MenuPrincipal(const Usuario &user);
};

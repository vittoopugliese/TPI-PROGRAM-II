#pragma once
#include "movimientoManager.h"
#include "categoriaManager.h"
#include "informeManager.h"
#include "usuario.h"
class App {
private:
   MovimientoManager subMenuMovimientos;
   CategoriaManager subMenuCategorias;
   InformeManager subMenuInformes;
public:
   void MenuPrincipal(const Usuario &user);
   void menuApp();
};

#pragma once
#include "movimientoManager.h"
#include "categoriaManager.h"
/*
#include "productoManager.h"
#include "empleadoManager.h"
#include "ventaManager.h"
#include "proveedorManager.h"
#include "informes.h"
*/

 class App{
    private:
        MovimientoManager subMenuMovimientos;
        CategoriaManager subMenuCategorias;
   /*
    ProductoManager subMenuP;
    EmpleadoManager subMenuE;
    VentaManager subMenuV;
    ProveedorManager subMenuProveedor;
    Informes subMenuInformes;
    */

   public:
    void MenuPrincipal();
 };

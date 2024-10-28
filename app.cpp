#include <iostream>
#include "funcionesGlobales.h"
using namespace std;
#include "app.h"

 void App::MenuPrincipal()
 {
   int opcion;
    while(true)
    {

      clear();
      cout << "  MENU PRINCIPAL" << endl;
      cout << "-----------------" << endl;
      cout << "1 - MOVIMIENTOS" << endl;
      cout << "2 - CATEGORIAS" << endl;
      cout << "3 - INFORMES" << endl;
      cout << "4 - ???" << endl;
      cout << "5 - Logout" << endl;
      cout << endl;
      cout << "0 - PARA SALIR" << endl;
      cout << "-----------------" << endl;

      cout << "INGRESE UNA OPCION: ";
      opcion = ingresoEntero();
      clear();
      switch (opcion)
      {
       case 1:
        {
          //subMenuP.menuProducto();
        }
        break;
       case 2:
        {
          //subMenuV.menuVentas();
          break;
        }
       case 3:
        {
          //subMenuE.menuEmpleado();
          break;
        }
        break;
       case 4:
        {
          //subMenuProveedor.menuProveedor();
        }
        break;
        case 5:
        {
          //subMenuInformes.MenuInforme();
        }
        break;
       case 0:
        {
          return;
        }
        break;
       default:
        {
          cout << "OPCION INCORRECTA" << endl;
          pausa();
        }
      }
      clear();
    }
   return;
 }

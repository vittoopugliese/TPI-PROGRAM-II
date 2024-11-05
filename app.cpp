#include <iostream>
#include "funcionesGlobales.h"
using namespace std;
#include "app.h"

void App::MenuPrincipal(){
  int opcion;

  while (true){
    clear();
    
    cout << "-- MENU PRINCIPAL --" << endl;
    cout << "--------------------" << endl;
    cout << "1 - MOVIMIENTOS" << endl;
    cout << "2 - CATEGORIAS" << endl;
    cout << "3 - INFORMES" << endl;
    cout << "0 - SALIR" << endl;
    cout << "--------------------" << endl;
    cout << "INGRESE UNA OPCION: ";

    opcion = ingresoEntero();
    clear();

    switch (opcion) {
    case 1:
      subMenuMovimientos.mostrarMenuDeMovimientos();
      break;
    case 2:
      subMenuCategorias.mostrarMenuDeCategorias();
      break;
    case 3:
      // subMenuInformes.menu();
      break;
      break;
    case 4:
      // subMenuProveedor.menuProveedor();
      break;
    case 0:
      return;
      break;
    default:
      cout << "OPCION INCORRECTA" << endl;
      pausa();
    }

    clear();
  }

  return;
}

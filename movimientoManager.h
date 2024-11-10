#pragma once
#include "movimiento.h"
#include "movimientoArchivo.h"
#include "usuarioManager.h"
#include <string>
using namespace std;

class MovimientoManager{
public:
    void menu(const Usuario &user);
    void cargar();
    void mostrar(Movimiento reg);
    void eliminarMovimiento();
    void mostrarTodos();
    //-------FILTROS------
    void menuFiltros();
    void porTipo();
    void porCategoria();
    void porFecha();
};

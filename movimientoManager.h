#pragma once
#include <string>
#include "movimiento.h"
using namespace std;

class MovimientoManager{
public:
    void cargar();
    void mostrar(Movimiento reg);
    void eliminarMovimiento();
    void mostrarTodos();
    void abrirFiltrosDeMovimientos();
    void menu(const Usuario &user);
};

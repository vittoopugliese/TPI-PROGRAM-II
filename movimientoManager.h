#ifndef MOVIMIENTO_MANAGER_H
#define MOVIMIENTO_MANAGER_H
#include <string>
#include "movimiento.h"
using namespace std;

class MovimientoManager{
public:
    void cargarMovimiento();
    void mostrarMovimiento(Movimiento reg);
    void eliminarMovimiento();
    void mostrarTodosLosMovimientos();
    void eliminarTodosLosMovimientos();
    void menu();
    void abrirFiltrosDeMovimientos();
};

#endif

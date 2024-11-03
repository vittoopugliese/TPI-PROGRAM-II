#ifndef MOVIMIENTO_MANAGER_H
#define MOVIMIENTO_MANAGER_H
#include <string>
#include "movimiento.h"
using namespace std;

class MovimientoManager{
public:
    void cargar();
    void mostrar(Movimiento reg);
    void mostrarTodos();
    void eliminarTodos();
    void menu();
};

#endif

#pragma once
#include "movimiento.h"

class MovimientoArchivo {
private:
    char nombreArchivo[30];
public:
    MovimientoArchivo(const char *nombre);
    bool guardarArchivo(Movimiento reg);
    Movimiento leer(int pos);
    int contarRegistros();
    bool modificar(Movimiento reg, int pos);
};

#ifndef MOVIMIENTOARCHIVO_H
#define MOVIMIENTOARCHIVO_H
#include "movimiento.h"

class MovimientoArchivo {
private:
    char nombreArchivo[30];

public:
    MovimientoArchivo(const char *nombre);
    bool guardarArchivo(Movimiento reg);
    bool guardarArchivo(Movimiento reg, int pos);
    Movimiento leer(int pos);
    int contarRegistros();
    bool modificar(Movimiento reg, int pos);
    bool vaciarArchivo();
};

#endif
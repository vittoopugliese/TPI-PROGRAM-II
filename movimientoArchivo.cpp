#include "movimientoArchivo.h"
#include <cstdio>
#include <string.h>

MovimientoArchivo::MovimientoArchivo(const char *nombre) {
    strcpy(nombreArchivo, nombre);
}

bool MovimientoArchivo::guardarArchivo(Movimiento reg) {
    // ab: Append Binary - Abre el archivo para agregar datos en modo binario al final del archivo...
    FILE *p = fopen(nombreArchivo, "ab");
    if (p == NULL) return false;
    bool escribio = fwrite(&reg, sizeof(Movimiento), 1, p);
    fclose(p);
    return escribio;
}

Movimiento MovimientoArchivo::leer(int pos) {
    // rb: Read Binary - Abre el archivo solo para lectura en modo binario...
    Movimiento reg;
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) return reg;
    fseek(p, pos * sizeof(Movimiento), SEEK_SET);
    fread(&reg, sizeof(Movimiento), 1, p);
    fclose(p);
    return reg;
}

Movimiento MovimientoArchivo::getMovimientoFromId(int idMovimiento) {
    Movimiento aux;
    for (int i = 0; i < contarRegistros(); i++) {
        aux = leer(i);
        if (aux.getIdMovimiento() == idMovimiento) {
            return aux;
        }
    }
    return aux;
}

int MovimientoArchivo::contarRegistros() {
    FILE *p = fopen(nombreArchivo, "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Movimiento);
}

bool MovimientoArchivo::modificar(Movimiento reg, int pos) {
    FILE *p = fopen(nombreArchivo, "rb+");
    if (p == NULL) return false;
    fseek(p, pos * sizeof(Movimiento), SEEK_SET);
    bool escribio = fwrite(&reg, sizeof(Movimiento), 1, p);
    fclose(p);
    return escribio;
}

bool MovimientoArchivo::modificarFromID(Movimiento reg) {
    FILE *p = fopen(nombreArchivo, "rb+");
    bool escribio;
    if (p == NULL) return false;

    Movimiento aux;
    for (int i = 0; i < contarRegistros(); i++) {
        aux = leer(i);
        if (aux.getIdMovimiento() == reg.getIdMovimiento()) {
            fseek(p, i * sizeof(Movimiento), SEEK_SET);
            escribio = fwrite(&reg, sizeof(Movimiento), 1, p);
            fclose(p);
        }
    }
    return escribio;
}

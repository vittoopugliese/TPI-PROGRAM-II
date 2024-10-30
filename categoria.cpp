#include <iostream>
#include "categoria.h"
#include "categoriaManager.h"
using namespace std;

Categoria::Categoria(int tipoDeMovimiento, char nombreCategoria[20], char descripcion[50]) {
    _tipoDeMovimiento = tipoDeMovimiento;
    strcpy(_nombreCategoria, nombreCategoria);
    strcpy(_descripcion, descripcion);
}

Categoria::Categoria() {
    _tipoDeMovimiento = 0;
    strcpy(_nombreCategoria, "S/N");
    strcpy(_descripcion, "S/N");
}

const char *Categoria::getNombreCategoria() {
    return _nombreCategoria;
}

void Categoria::setNombreCategoria(const char *nombre) {
    strcpy(_nombreCategoria, nombre);
}


void Categoria::setDescripcionCategoria(const char *categoria) {
    strcpy(_descripcion, categoria);
}

int Categoria::getIdCategoria() {
    return _idCategoria;
}

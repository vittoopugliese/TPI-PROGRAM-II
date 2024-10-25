#include "movimientoManager.h"
#include <iostream>
using namespace std;

ManagerMovimientos::ManagerMovimientos():
    idMovimiento(0),
    tipoMovimiento(false),
    categoria("") {
    // constructor
}

void ManagerMovimientos::abrir() {
    cout << "abrir()" << endl;
}

bool ManagerMovimientos::guardar() {
    cout << "guardar()" << endl;
    return true;
}

int ManagerMovimientos::buscar() {
    cout << "buscar()" << endl;
    return 0;
}

void ManagerMovimientos::filtrar() {
    cout << "filtrar()" << endl;
}

int ManagerMovimientos::getIdMovimiento() const {
    return idMovimiento;
}

bool ManagerMovimientos::getTipoMovimiento() const {
    return tipoMovimiento;
}

string ManagerMovimientos::getCategoria() const {
    return categoria;
}

void ManagerMovimientos::setIdMovimiento(int id) {
    idMovimiento = id;
}

void ManagerMovimientos::setTipoMovimiento(bool tipo) {
    tipoMovimiento = tipo;
}

void ManagerMovimientos::setCategoria(const string& cat) {
    categoria = cat;
}
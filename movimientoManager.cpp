#include "movimientoManager.h"
#include <iostream>
using namespace std;

void MovimientoManager::cargar() {
    cout << "Cargando movimiento" << endl;
}

void MovimientoManager::mostrar() {
    cout << "Mostrando movimiento" << endl;
}

void MovimientoManager::mostrarTodos() {
    cout << "Mostrando todos" << endl;
}

void MovimientoManager::menuEmpleado() {
    cout << "Menu de empleado:" << endl;
    cout << "1 - CARGAR MOVIMIENTO" << endl;
    cout << "2 - MOSTRAR MOVIMIENTO" << endl;
    cout << "3 - MOSTRAR TODOS" << endl;
    cout << "0 - VOLVER" << endl;
}
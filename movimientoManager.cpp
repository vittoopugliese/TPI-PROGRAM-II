#include "movimientoManager.h"
#include "movimiento.h"
#include "fecha.h"
#include "funcionesGlobales.h"
#include <iostream>
#include <string>
using namespace std;

void MovimientoManager::cargar() {
    clear();
    Movimiento movimientos[30];
    int mes;

    cout << "Ingrese el numero del mes (1-12): ";
    cin >> mes;

    while(mes < 1 || mes > 12) {
        cout << "Mes invalido. Por favor ingrese un mes entre 1 y 12: ";
        cin >> mes;
    }

    for(int dia = 0; dia < 30; dia++) {
        clear();
        cout << "Dia: " << (dia + 1) << endl;

        int idMovimiento = mes * 100 + dia + 1; // a definir
        movimientos[dia].setIdMovimiento(idMovimiento);

        // temporalmente pido el id de movmimiento luego se sacara de la categoria
        int tipoMovimiento;
        cout << "Tipo de movimiento (0-Credito, 1-Debito, -1 Salir): ";
        cin >> tipoMovimiento;

        if(tipoMovimiento == -1) return;

        while(tipoMovimiento != 0 && tipoMovimiento != 1) {
            cout << "Tipo invalido. Ingrese 0 para Credito o 1 para Debito: ";
            cin >> tipoMovimiento;
        }

        movimientos[dia].setIdTipo(tipoMovimiento);
        // temporalmente pido el id de movmimiento luego se sacara de la categoria

        int categoria;
        cout << "Ingrese el ID de categoria: ";
        cin >> categoria;
        movimientos[dia].setIdCategoria(categoria);

        float importe;
        cout << "Ingrese el importe del movimiento: $";
        cin >> importe;

        while(importe < 0) {
            cout << "El importe no puede ser negativo. Ingrese nuevamente: $";
            cin >> importe;
        }

        movimientos[dia].setImporte(importe);

        Fecha fecha;
        fecha.setMes(mes);
        fecha.setDia(dia + 1);
        fecha.setAnio(2024);
        movimientos[dia].setFecha(fecha);

        char recurrente;
        cout << "Es un movimiento recurrente? (S/N): ";
        cin >> recurrente;
        movimientos[dia].setRecurrencia(toupper(recurrente) == 'S');


        char descripcion[100];
        cout << "Ingrese una descripcion: ";
        cin >> descripcion;
        movimientos[dia].setDescripcion(descripcion);

        movimientos[dia].setEstado(true);
        pausa();
    }

    clear();
    cout << "Se han cargado exitosamente los movimientos del mes " << mes << endl;
    pausa();
    return;
}

void MovimientoManager::mostrar() {
    clear();
    cout << "Mostrando movimiento" << endl;
    pausa();
}

void MovimientoManager::mostrarTodos() {
    clear();
    cout << "Mostrando todos los movimientos" << endl;
    pausa();
}

void MovimientoManager::menu() {
    clear();

    int opcion;

    do {
    clear();
        cout << "Menu De Movimientos:" << endl << endl;
        cout << "1 - CARGAR MOVIMIENTO" << endl;
        cout << "2 - MOSTRAR MOVIMIENTO" << endl;
        cout << "3 - MOSTRAR TODOS" << endl;
        cout << "0 - VOLVER" << endl << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cargar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                mostrarTodos();
                break;
            case 0:
                clear();
                cout << "Volviendo al menu principal..." << endl;
                pausa();
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
                pausa();
                break;
                break;
        }
    } while(opcion != 0);
}

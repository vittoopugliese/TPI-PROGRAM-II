#include <iostream>
#include "informeBalance.h"
#include "movimientoArchivo.h"
using namespace std;

void InformeBalance::mostrarMenuDeBalances() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    int opcion;

    if (cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        return;
    }

    cout << "----- BALANCES -----" << endl;
    cout << "1 - BALANCE MENSUAL" << endl;
    cout << "2 - BALANCE ANUAL" << endl;
    cout << "0 - VOLVER" << endl;
    cout << "---------------------" << endl << endl;
    cout << "INGRESE OPCION: ";
    opcion = ingresoEntero();

    while (opcion < 0 || opcion > 2) {
        cout << "OPCION INCORRECTA. Ingrese una opcion valida: ";
        opcion = ingresoEntero();
    }

    clear();

    switch (opcion) {
        case 1:
            iniciarBalanceMensual();
            break;
        case 2:
            inicialBalanceAnual();
            break;
        case 0:
            return;
    }

    clear();
    return;
}

void InformeBalance::iniciarBalanceMensual() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    int anio;
    int mes;

    cout << "Ingrese el anio: ";
    anio = ingresoEntero();

    while (anio < 0) {
        cout << "Anio invalido. Ingrese un numero positivo: ";
        anio = ingresoEntero();
    }

    cout << "Ingrese el mes (1-12): ";
    mes = ingresoEntero();

    while (mes < 1 || mes > 12) {
        cout << "Mes invalido. Ingrese un mes entre 1 y 12: ";
        mes = ingresoEntero();
    }

    clear();

    cout << "BALANCE MENSUAL - " << mes << "/" << anio << endl;
    cout << "----------------------------------------" << endl << endl;

    float balanceTotal = 0;
    bool hayMovimientos = false;

    cout << "INGRESOS (CREDITOS):" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        Movimiento mov = archivoMovimiento.leer(i);
        bool mostrarIngreso = mov.getEstado() && mov.getFecha().getMes() == mes && mov.getFecha().getAnio() == anio && mov.getIdTipo() == 0;
        string nombreDeCategoria = categoria.getNombreCategoria(mov.getIdCategoria());

        if (mostrarIngreso) {
            hayMovimientos = true;
            cout << "- $" << mov.getImporte() << " | " << nombreDeCategoria << " | " << mov.getDescripcion() << endl;;
            balanceTotal += mov.getImporte();
        }
    }

    cout << endl;

    cout << "EGRESOS (DEBITOS):" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        Movimiento mov = archivoMovimiento.leer(i);
        bool mostrarEgreso = mov.getEstado() && mov.getFecha().getMes() == mes && mov.getFecha().getAnio() == anio && mov.getIdTipo() == 1;
        string nombreDeCategoria = categoria.getNombreCategoria(mov.getIdCategoria());

        if (mostrarEgreso) {
            hayMovimientos = true;
            cout << "- $" << mov.getImporte() << " | " << nombreDeCategoria << " | " << mov.getDescripcion() << endl;;
            balanceTotal -= mov.getImporte();
        }
    }

    mostrarResultadoBalance(hayMovimientos, balanceTotal, "el periodo " + to_string(mes) + "/" + to_string(anio));
}

void InformeBalance::iniciarBalanceAnual() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    int anio;

    if (cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        return;
    }

    cout << "Ingrese el anio: ";
    anio = ingresoEntero();

    while (anio < 0) {
        cout << "Anio invalido. Ingrese un numero positivo: ";
        anio = ingresoEntero();
    }

    clear();

    cout << "BALANCE ANUAL - " << anio << endl;
    cout << "----------------------------------------" << endl << endl;

    float balanceTotal = 0;
    bool hayMovimientos = false;

    mostrarMovimientosDependiendoDeSuTipo(cantidad, anio, 0, balanceTotal, hayMovimientos);
    mostrarMovimientosDependiendoDeSuTipo(cantidad, anio, 1, balanceTotal, hayMovimientos);
    mostrarResultadoBalance(hayMovimientos, balanceTotal, "el anio " + to_string(anio));
}

void InformeBalance::mostrarMovimientosDependiendoDeSuTipo(int cantidad, int anio, int tipoDeMovimiento, float&balanceTotal, bool&hayMovimientos) {
    cout << tipoDeMovimiento == 0 ? "INGRESOS (CREDITOS):" : "EGRESOS (DEBITOS):" << endl;
    cout << "----------------------------------------" << endl;
    
    for (int i = 0; i < cantidad; i++) {
        Movimiento mov = archivoMovimiento.leer(i);
        bool mostrarEgreso = mov.getEstado() && mov.getFecha().getAnio() == anio && mov.getIdTipo() == tipoDeMovimiento;
        string nombreDeCategoria = categoria.getNombreCategoria(mov.getIdCategoria());

        if (mostrarEgreso) {
            hayMovimientos = true;
            cout << "- $" << mov.getImporte() << " | " << nombreDeCategoria << " | " << mov.getDescripcion() << endl;

            if(tipoDeMovimiento == 0){
                balanceTotal += mov.getImporte();
            } else {
                balanceTotal -= mov.getImporte();
            }
        }
    }
}

void InformeBalance::mostrarResultadoBalance(bool hayMovimientos, float balanceTotal, const string& periodo) {
    if (!hayMovimientos) {
        clear();
        cout << "No hay movimientos registrados para " << periodo << endl;
    } else {
        cout << endl << "----------------------------------------" << endl;
        cout << "BALANCE FINAL: $" << balanceTotal << endl;

        if (balanceTotal > 0) {
            cout << "Balance POSITIVO" << endl;
        } else if (balanceTotal < 0) {
            cout << "Balance NEGATIVO" << endl;
        } else {
            cout << "Balance NEUTRO" << endl;
        }
    }
    
    cout << "----------------------------------------" << endl;
    pausa();
}
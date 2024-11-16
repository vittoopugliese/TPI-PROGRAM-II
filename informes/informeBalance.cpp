#include <iostream>
#include "informeBalance.h"
#include "../movimientoManager.h"
#include "../usuario.h"
using namespace std;

void InformeBalance::mostrarMenuDeBalances(const Usuario &user) {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    int opcion;

    if (cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        return;
    }

    cout << "----- BALANCES -----" << endl;
    cout << "[1] BALANCE MENSUAL" << endl;
    cout << "[2] BALANCE ANUAL" << endl;
    cout << endl;
    cout << "[0] - VOLVER" << endl;
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
            iniciarBalanceMensual(user);
            break;
        case 2:
            iniciarBalanceAnual(user);
            break;
        case 0:
            return;
    }

    clear();
    return;
}

void InformeBalance::iniciarBalanceMensual(const Usuario &user) {
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

    mostrarMovimientosDependiendoDeSuTipo(TipoBalance::MENSUAL, TipoMovimiento::CREDITO, cantidad, anio, mes, balanceTotal, hayMovimientos, user);
    mostrarMovimientosDependiendoDeSuTipo(TipoBalance::MENSUAL, TipoMovimiento::DEBITO, cantidad, anio, mes, balanceTotal, hayMovimientos, user);
    mostrarResultadoBalance(hayMovimientos, balanceTotal, "el periodo " + to_string(mes) + "/" + to_string(anio));
}

void InformeBalance::iniciarBalanceAnual(const Usuario &user) {
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
    cout << "----------------------------------------" << endl;

    float balanceTotal = 0;
    bool hayMovimientos = false;

    mostrarMovimientosDependiendoDeSuTipo(TipoBalance::ANUAL, TipoMovimiento::CREDITO, cantidad, anio, 0, balanceTotal, hayMovimientos, user);
    mostrarMovimientosDependiendoDeSuTipo(TipoBalance::ANUAL, TipoMovimiento::DEBITO, cantidad, anio, 0, balanceTotal, hayMovimientos, user);
    mostrarResultadoBalance(hayMovimientos, balanceTotal, "el anio " + to_string(anio));
}

void InformeBalance::mostrarMovimientosDependiendoDeSuTipo(int tipoDeBalance, int tipoDeMovimiento, int cantidad, int anio, int mes, float&balanceTotal, bool&hayMovimientos, const Usuario &user) {
    if(tipoDeMovimiento == 0){
        cout << endl << endl << "INGRESOS (CREDITOS):" << endl;
    } else {
        cout << endl << endl << "EGRESOS (DEBITOS):" << endl;
    }

    cout << "----------------------------------------" << endl;

    for (int i = 0; i < cantidad; i++) {
        MovimientoArchivo archivoMovimiento("movimientos.dat");
        Movimiento mov = archivoMovimiento.leer(i);

        if (user.getUsuarioID() != mov.getIdUsuario()) {
            continue; // TODO
        }

        bool mostrarEgreso;

        if(tipoDeBalance == TipoBalance::ANUAL){
            mostrarEgreso = mov.getEstado() && mov.getFecha().getAnio() == anio && mov.getIdTipo() == tipoDeMovimiento;
        } else if(tipoDeBalance == TipoBalance::MENSUAL){
            mostrarEgreso = mov.getEstado() && mov.getFecha().getAnio() == anio && mov.getFecha().getMes() == mes && mov.getIdTipo() == tipoDeMovimiento;
        }

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
        cout << endl << endl << "----------------------------------------" << endl;
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

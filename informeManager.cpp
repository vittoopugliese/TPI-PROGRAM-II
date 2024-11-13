#include <iostream>
#include "funcionesGlobales.h"
#include "informeManager.h"
#include "categoriaManager.h"
#include "porCategoria.h"
#include "indicadores.h"
using namespace std;

void InformeManager::menu(const Usuario &user) {
    int opcion;

    while (true) {
        clear();
        cout << "--------- INFORMES ---------" << endl;
        cout << "1 - BALANCE MENSUAL O ANUAL" << endl;
        cout << "2 - INGRESOS POR CATEGORIA" << endl;
        cout << "3 - EGRESOS POR CATEGORIA" << endl;
        cout << "4 - INDICADORES" << endl << endl;
        //cout << "5 - GASTOS POR USUARIO (ADMIN)" << endl << endl;

        cout << "0 - SALIR" << endl;
        cout << "----------------------------" << endl;

        cout << "INGRESE OPCION: ";
        opcion = ingresoEntero();;

        clear();

        switch (opcion) {
            case 1:
                mostrarBalanceMensual();
                break;
            case 2:
                mostrarIngresosPorCategoria();
                break;
            case 3:
                mostrarEgresosPorCategoria();
                break;
            case 4:
                mostrarIndicadores();
                break;
            case 5:
                //mostrarGastosPorUsuario();
                break;
            case 0:
                return;
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
        }

        clear();
    }
};

void InformeManager::mostrarBalanceMensual() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    CategoriaManager categoria;
    int cantidad = archivoMovimiento.contarRegistros();

    if (cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        return;
    }

    int anio;
    cout << "Ingrese el anio: ";
    anio = ingresoEntero();

    while (anio < 0) {
        cout << "Anio invalido. Ingrese un numero positivo: ";
        anio = ingresoEntero();
    }

    int mes;
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

    if (!hayMovimientos) {
        clear();
        cout << "No hay movimientos registrados para el periodo " << mes << "/" << anio << endl;
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

void InformeManager::mostrarIngresosPorCategoria() { //Juli
    PorCategoria aux;
    aux.balancePorCateoria();
}

void InformeManager::mostrarEgresosPorCategoria() { //Juli

}

void InformeManager::mostrarIndicadores() { // Fran
    Indicadores aux;
    aux.showIndicadores();
}

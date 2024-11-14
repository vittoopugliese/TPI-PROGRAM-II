#include <iostream>
#include "funcionesGlobales.h"
#include "informeManager.h"
#include "categoriaManager.h"
#include "indicadores.h"
using namespace std;

void InformeManager::menu(const Usuario &user) {
    int opcion;

    InformeBalance informeBalance;

    while (true) {
        clear();
        cout << "--------- INFORMES ---------" << endl;
        cout << "1 - BALANCE MENSUAL O ANUAL" << endl;
        cout << "2 - INGRESOS POR CATEGORIA" << endl;
        cout << "3 - EGRESOS POR CATEGORIA" << endl;
        cout << "4 - INDICADORES" << endl;
        //cout << "5 - GASTOS POR USUARIO (ADMIN)" << endl << endl;

        cout << "0 - SALIR" << endl;
        cout << "----------------------------" << endl;

        cout << "INGRESE OPCION: ";
        opcion = ingresoEntero();;

        clear();

        switch (opcion) {
            case 1:
                informeBalance.mostrarMenuDeBalances(user);
                break;
            case 2:
                mostrarIngresosPorCategoria(user);
                break;
            case 3:
                mostrarEgresosPorCategoria(user);
                break;
            case 4:
                mostrarIndicadores(user);
                break;
            case 5:
                //mostrarGastosPorUsuario(user);
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

void InformeManager::mostrarIngresosPorCategoria(const Usuario &user) { //Juli

}

void InformeManager::mostrarEgresosPorCategoria(const Usuario &user) { //Juli

}

void InformeManager::mostrarIndicadores(const Usuario &user) { // Fran
    Indicadores aux;
    aux.showIndicadores();
}

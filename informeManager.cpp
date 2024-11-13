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
                informeBalance.mostrarMenuDeBalances();
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

#include <iostream>
#include "funcionesGlobales.h"
#include "informeManager.h"
#include "categoriaManager.h"
#include "indicadores.h"
#include "porCategoria.h"
using namespace std;

void InformeManager::menu(const Usuario &user) {
    int opcion;

    InformeBalance informeBalance;

    while (true) {
        clear();
        cout << "--------- INFORMES ---------" << endl;
        cout << "1 - BALANCE MENSUAL O ANUAL" << endl;
        cout << "2 - BALANCES POR CATEGORIA" << endl;
        cout << "3 - INDICADORES" << endl << endl;

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
                PorCategoria aux;
                aux.balancePorCateoria(user);
                break;
            case 3:
                //Indicadores aux;
                //aux.showIndicadores(user);
                break;
            case 0:
                return;
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
        }
        clear();
    }
}

#include <iostream>
#include "funcionesGlobales.h"
#include "informeManager.h"
using namespace std;

void InformeManager::menu() {
    int opcion;

    while (true) {
        clear();
        cout << "------ INFORMES ------" << endl;
        cout << "1 - BALANCE MENSUAL O ANUAL" << endl;
        cout << "2 - EGRESOS POR CATEGORIA" << endl;
        cout << "3 - INGRESOS POR FUENTE" << endl;
        cout << "4 - GASTOS POR USUARIO (ADMIN)" << endl << endl;
        cout << "0 - SALIR" << endl;
        cout << "-----------------------" << endl;

        cout << "INGRESE OPCION: ";
        cin >> opcion;

        clear();

        switch (opcion) {
        case 1:
            mostrarBalanceMensual();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
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
    
};

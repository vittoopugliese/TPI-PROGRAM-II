#include <iostream>
#include <fstream>
#include <ctime>

#include "funcionesGlobales.h"
#include "informeManager.h"
#include "categoriaManager.h"
#include "indicadores.h"
#include "porCategoria.h"
#include "movimientoArchivo.h"
#include "informeGenerador.h"
#include "fecha.h"

using namespace std;

void InformeManager::menu(const Usuario &user) {
    InformeBalance informeBalance;
    PorCategoria balancePorCategorias;
    Indicadores indicadores;
    InformeGenerador informeGenerador;
    int opcion;

    while (true) {
        clear();
        cout << "--------- INFORMES ---------" << endl;
        cout << "1 - BALANCE MENSUAL O ANUAL" << endl;
        cout << "2 - BALANCES POR CATEGORIA" << endl;
        cout << "3 - INDICADORES" << endl;
        cout << "4 - GENERAR " << endl;

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
                balancePorCategorias.balancePorCateoria(user);
                break;
            case 3:
                indicadores.showIndicadores();
                break;
            case 4:
                informeGenerador.generarInformeTXT(user);
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
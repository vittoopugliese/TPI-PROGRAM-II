#pragma once
#include "funcionesGlobales.h"
#include "categoriaManager.h"

using namespace std;

class InformeBalance {
    CategoriaManager categoria;
public:
    enum TipoMovimiento {
        CREDITO = 0,
        DEBITO = 1,
    };

    enum TipoBalance {
        MENSUAL = 0,
        ANUAL = 1
    };

    void mostrarMenuDeBalances(const Usuario &user);
    void iniciarBalanceMensual();
    void iniciarBalanceAnual();
    void mostrarResultadoBalance(bool hayMovimientos, float balanceTotal, const string&periodo);
    void mostrarMovimientosDependiendoDeSuTipo(int tipoDeBalance, int tipoDeMovimiento, int cantidad, int anio, int mes, float&balanceTotal, bool&hayMovimientos);
};



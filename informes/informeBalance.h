#pragma once
#include "../funcionesGlobales.h"
#include "../categorias/categoriaManager.h"

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
    void iniciarBalanceMensual(const Usuario &user);
    void iniciarBalanceAnual(const Usuario &user);
    void mostrarResultadoBalance(bool hayMovimientos, float balanceTotal, const string&periodo);
    void mostrarMovimientosDependiendoDeSuTipo(int tipoDeBalance, int tipoDeMovimiento, int cantidad, int anio, int mes, float&balanceTotal, bool&hayMovimientos, const Usuario &user);
};



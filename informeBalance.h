#pragma once
#include "funcionesGlobales.h"
#include "categoriaManager.h"

using namespace std;

class InformeBalance{
    CategoriaManager categoria;
public:
    void mostrarMenuDeBalances();
    void iniciarBalanceMensual();
    void iniciarBalanceAnual();
    void mostrarResultadoBalance(bool hayMovimientos, float balanceTotal, const string&periodo);
    void mostrarMovimientosDependiendoDeSuTipo(int cantidad, int anio, int tipoDeMovimiento, float&balanceTotal, bool&hayMovimientos);
};

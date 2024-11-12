#pragma once
using namespace std;
#include "usuarioManager.h"
#include "informeBalance.h"

class InformeManager{
    InformeBalance informeBalance;
public:
    void menu(const Usuario &user);
    void mostrarIngresosPorCategoria();
    void mostrarEgresosPorCategoria();
    void mostrarIndicadores();
};

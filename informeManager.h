#pragma once
using namespace std;
#include "usuarioManager.h"

class InformeManager{
public:
    void menu(const Usuario &user);
    void mostrarBalanceMensual();
    void mostrarIngresosPorCategoria();
    void mostrarEgresosPorCategoria();
};

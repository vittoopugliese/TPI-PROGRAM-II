#pragma once
using namespace std;
#include "usuarioManager.h"
#include "informeBalance.h"

class InformeManager {
    InformeBalance informeBalance;
public:
    void menu(const Usuario &user);
    void mostrarIngresosPorCategoria(const Usuario &user);
    void mostrarEgresosPorCategoria(const Usuario &user);
    void mostrarIndicadores(const Usuario &user);
};

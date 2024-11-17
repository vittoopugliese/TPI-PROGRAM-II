#pragma once
using namespace std;
#include "../usuarios/usuarioManager.h"
#include "informeBalance.h"
#include "informePorCategoria.h"
#include "informeIndicadores.h"
#include "informeGenerador.h"

class InformeManager {
    InformeBalance informeBalance;
public:
    void menu(const Usuario &user);
};

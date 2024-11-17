#pragma once
using namespace std;
#include "informeBalance.h"
#include "../usuarios/usuarioManager.h"

class InformeGenerador {
public:
    void generarInformeTXT(const Usuario &user);
};

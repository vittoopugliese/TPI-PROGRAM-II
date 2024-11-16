#pragma once
using namespace std;
#include "../usuarioManager.h"
#include "informeBalance.h"

class InformeGenerador {
public:
    void generarInformeTXT(const Usuario &user);
};

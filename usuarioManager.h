#pragma once
#include "usuario.h"

class UsuarioManager {
    public:
        bool esUsuarioExistente(Usuario &usuario);
        Usuario registrarUsuario();
};

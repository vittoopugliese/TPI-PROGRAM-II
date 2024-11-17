#pragma once
#include "usuario.h"
#include "usuarioArchivo.h"
#include "../funcionesGlobales.h"

class UsuarioManager {
    public:
        bool esUsuarioExistente(Usuario &usuario);
        Usuario registrarUsuario();
        bool iniciarSesion(Usuario &usuario);
};

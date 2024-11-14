#pragma once
#include "usuario.h"

/*
Esta clase, sólo va a guardar usuarios, o leer usuarios del archivo "usuarios.dat".
Lo demas, como ver si ya hay un usuario creado dentro de ese archivo "usuarios.dat", o crear un usuario nuevo, lo hará la clase usuarioManager.
En todo caso, esta clase, guardará ese Usuario en el archivo "usuarios.dat".
*/

class UsuarioArchivo {
    private:
        std::string _nombreArchivo = "usuarios.dat";
    public:
        UsuarioArchivo();
        bool guardarUsuario(const Usuario &usuario);
        Usuario leerUsuario(const int idUsuario);
        int cantidadUsuarios();
};

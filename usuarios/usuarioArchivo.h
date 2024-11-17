#pragma once
#include "usuario.h"

/*
Esta clase, s�lo va a guardar usuarios, o leer usuarios del archivo "usuarios.dat".
Lo demas, como ver si ya hay un usuario creado dentro de ese archivo "usuarios.dat", o crear un usuario nuevo, lo har� la clase usuarioManager.
En todo caso, esta clase, guardar� ese Usuario en el archivo "usuarios.dat".
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

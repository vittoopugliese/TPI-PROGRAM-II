#include "usuarioArchivo.h"

bool UsuarioArchivo::guardarUsuario(const Usuario &usuario) {
    FILE * archivo = fopen(_nombreArchivo.c_str(), "ab");
    if (archivo == nullptr) {
        return false;
    }
    bool guardado = fwrite(&usuario, sizeof(Usuario), 1, archivo);
    fclose(archivo);
    return guardado;
}

Usuario UsuarioArchivo::leerUsuario(int idUsuario) {
    FILE * archivo = fopen(_nombreArchivo.c_str(), "rb");
    Usuario usuario;
    if (archivo == nullptr) {
        return usuario;
    }
    bool existe = false;
    while (fread(&usuario, sizeof(Usuario), 1, archivo)) {
        if (usuario.getUsuarioID() == idUsuario) {
            existe = true;
            break;
        }
    }
    fclose(archivo);
    if (!existe) {
        Usuario usuario;
        return usuario;
    }
    return usuario;
}

int UsuarioArchivo::cantidadUsuarios() {
    FILE * archivo = fopen(_nombreArchivo.c_str(), "rb");
    if (archivo == nullptr) {
        return 0;
    }
    fseek(archivo, 0, SEEK_END);
    int countUsuarios = (ftell(archivo) / sizeof(Usuario));
    fclose(archivo);
    return countUsuarios;
}

UsuarioArchivo::UsuarioArchivo() {}

#include "usuario.h"
#include "usuarioArchivo.h"
#include <cstring>
#include <functional>

size_t Usuario::hashPassword(std::string password) {
    std::hash<std::string> hash_fn;
    return hash_fn(password);
}

int Usuario::getUsuarioID() {
    return _usuarioID;
}

std::string Usuario::getNombreUsuario() const {
    return _nombreUsuario;
}

size_t Usuario::getPassword() {
    size_t _password;
}

bool Usuario::validarPassword(std::string password) {
    return _password == hashPassword(password);
}

Usuario::Usuario() {
    _usuarioID = -1;
    strcpy(_nombreUsuario, "N/A");
}

Usuario::Usuario(std::string userName, std::string userPassword) {
    UsuarioArchivo mgmtArchivoUsuario;
    int newID = mgmtArchivoUsuario.cantidadUsuarios() + 1;

    _usuarioID = newID;
    strcpy(_nombreUsuario, userName.c_str());
    _password = hashPassword(userPassword);
}

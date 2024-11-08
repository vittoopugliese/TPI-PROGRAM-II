#include <iostream>
#pragma once

class Usuario {
    private:
        int _usuarioID;
        char _nombreUsuario[15];
        size_t _password;
    public:
        Usuario();
        Usuario(std::string nombreUsuario, std::string password);

        int getUsuarioID();
        std::string getNombreUsuario() const;
        size_t getPassword();
        size_t hashPassword(std::string password);
        bool validarPassword(std::string password);
};

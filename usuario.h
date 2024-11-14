#include <iostream>
#pragma once

class Usuario {
    private:
        int _usuarioID;
<<<<<<< HEAD
        char _nombreUsuario[31];
=======
        char _nombreUsuario[33];
>>>>>>> 164c5c886e3c2ad990c6e7a0708ec533b57a9039
        size_t _password;
    public:
        Usuario();
        Usuario(std::string nombreUsuario, std::string password);

        int getUsuarioID() const;
        std::string getNombreUsuario() const;
        size_t getPassword();
        size_t hashPassword(std::string password);
        bool validarPassword(std::string password);
};

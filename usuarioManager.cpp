#include "funcionesGlobales.h"
#include "usuarioManager.h"
#include "usuarioArchivo.h"

bool UsuarioManager::esUsuarioExistente(Usuario &usuario) {
    if (usuario.getUsuarioID() == -1) {
        return false;
    }
    return true;
}

Usuario UsuarioManager::registrarUsuario() {
    UsuarioArchivo mgmtArchivoUsuario;

    std::string userName;
    std::string userPassword;

    std::cout << "Nombre de usuario: ";
    std::cin >> userName;

    std::cout << "Contrasenia: ";
    std::cin >> userPassword;

    Usuario newUser(userName, userPassword);
    mgmtArchivoUsuario.guardarUsuario(newUser);
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Usuario creado exitosamente!" << std::endl;
    std::cout << "Tu numero de usuario es: " << newUser.getUsuarioID() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Guarda este numero en un lugar seguro." << std::endl;
    std::cout << "Deberas usarlo luego para poder ingresar." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    pausa();
    return newUser;
}

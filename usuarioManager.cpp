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

    std::cout << "Ingrese un nombre de usuario: ";
    std::cin >> userName;

    std::cout << "Ingrese una contraseña: ";
    std::cin >> userPassword;

    Usuario newUser(userName, userPassword);
    mgmtArchivoUsuario.guardarUsuario(newUser);
    std::cout << "Se creo el usuario de forma exitosa." << std::endl;
    std::cout << "Tu numero de usuario es: " << newUser.getUsuarioID() << std::endl;
    std::cout << "Guarda este numero en un lugar seguro. sin el no podras acceder al sistema" << std::endl;
    pausa();
    return newUser;
    //std::cout << "getPassword = " << newUser.getPassword() << std::endl;
}

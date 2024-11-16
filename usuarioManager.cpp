#include "usuarioManager.h"

bool UsuarioManager::esUsuarioExistente(Usuario &usuario) {
    if (usuario.getUsuarioID() == -1) {
        return false;
    }
    return true;
}

bool UsuarioManager::iniciarSesion(Usuario &usuario) {
    int userID;
    string password;
    UsuarioArchivo mgmtArchivoUsuario;

    std::cout << "-- INICIAR SESION --" << std::endl;
    std::cout << endl;
    cout << "Ingrese su ID de usuario: ";
    userID = ingresoEntero();

    usuario = mgmtArchivoUsuario.leerUsuario(userID);
    if (usuario.getUsuarioID() == -1) {
        clear();
        std::cout << "-- INICIAR SESION --" << std::endl;
        std::cout << endl;
        cout << "El usuario no existe." << endl;
        pausa();
        return false;
    }
    cout << "Ingrese su contrasenia: ";
    cin.ignore();
    getline(cin, password);

    if (!usuario.validarPassword(password)) {
        cout << "Contrasenia invalida." << endl;
        pausa();
        return false;
    }
    return true;
}

Usuario UsuarioManager::registrarUsuario() {
    UsuarioArchivo mgmtArchivoUsuario;

    std::string userName;
    std::string userPassword;

    std::cout << "-- REGISTRAR USUARIO NUEVO --" << std::endl;
    std::cout << endl;
    std::cout << "Nombre de usuario: ";
    cin.ignore();
    getline(cin, userName);

    while (userName.size() < 4 || userName.size() > 32) {
        clear();
        std::cout << "-- REGISTRAR USUARIO NUEVO --" << std::endl;
        std::cout << endl;
        std::cout << "ERROR: El nombre de usuario debe tener entre 4 y 32 caracteres." << endl;
        std::cout << "Nombre de usuario: ";
        getline(cin, userName);
    }

    std::cout << "Contrasenia: ";
    getline(cin, userPassword);
    while (userPassword.size() < 4 || userPassword.size() > 32) {
        clear();
        std::cout << "-- REGISTRAR USUARIO NUEVO --" << std::endl;
        std::cout << endl;
        std::cout << "ERROR: La contrasenia del usuario debe tener entre 4 y 32 caracteres." << endl;
        std::cout << "Nombre de usuario: " << userName << endl;
        std::cout << "Contrasenia: ";
        getline(cin, userPassword);
    }

    Usuario newUser(userName, userPassword);
    mgmtArchivoUsuario.guardarUsuario(newUser);
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Usuario creado exitosamente!" << std::endl;
    std::cout << "Tu numero de usuario es: " << newUser.getUsuarioID() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "--------!!!-----ATENCION-----!!!--------" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "GUARDE ESTE NUMERO EN UN LUGAR SEGURO." << std::endl;
    std::cout << "Deberas usarlo luego para poder ingresar." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    pausa();
    return newUser;
}

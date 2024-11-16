#include <iostream>
#include "funcionesGlobales.h"
#include "usuario.h"
#include "usuarioArchivo.h"
#include "usuarioManager.h"
using namespace std;
#include "app.h"

void App::menuLogin() {
    int opcion;
    UsuarioManager mgmtUsuarios;
    while (true) {
        clear();

        cout << "SISTEMA DE FINANZAS" << endl;
        cout << "   PERSONALES" << endl;
        cout << "-------------------" << endl;
        cout << "[1] INGRESAR" << endl;
        cout << "[2] REGISTRARSE" << endl;
        cout << endl;
        cout << "[0] PARA SALIR" << endl;
        cout << "-------------------" << endl;

        cout << "INGRESE UNA OPCION: ";

        opcion = ingresoEntero();
        clear();

        switch (opcion) {
            case 1:
                {
                Usuario usuario;
                if (!mgmtUsuarios.iniciarSesion(usuario)) {
                    break;
                }
                MenuPrincipal(usuario);
                break;
                }
            case 2:
                {
                Usuario usuario = mgmtUsuarios.registrarUsuario();
                MenuPrincipal(usuario);
                break;
                }
            case 0:
                exit(-1);
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
        }
    }
}

void App::MenuPrincipal(const Usuario &user) {
    int opcion;
    while (true) {
        clear();
        cout << "Bienvenido " << user.getNombreUsuario() << "!" << endl;
        cout << "-----------------" << endl;
        cout << "  MENU PRINCIPAL " << endl;
        cout << "-----------------" << endl;
        cout << "[1] MOVIMIENTOS" << endl;
        cout << "[2] CATEGORIAS" << endl;
        cout << "[3] INFORMES" << endl;

        cout << endl;
        cout << "[0] LOGOUT" << endl;
        cout << "-----------------" << endl;

        cout << "INGRESE UNA OPCION: ";
        opcion = ingresoEntero();
        clear();
        switch (opcion) {
            case 1:
                subMenuMovimientos.menu(user);
                break;
            case 2:
                subMenuCategorias.menu(user);
                break;
            case 3:
                subMenuInformes.menu(user);
                break;
            case 0:
                clear();
                cout << "Saliste del sistema." << endl;
                pausa();
                return;
                break;
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
        }
        clear();
    }
    return;
}

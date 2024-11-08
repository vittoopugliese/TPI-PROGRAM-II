#include <iostream>
#include "funcionesGlobales.h"
#include "usuario.h"
#include "usuarioArchivo.h"
#include "usuarioManager.h"
using namespace std;
#include "app.h"

void App::MenuPrincipal(const Usuario &user) {
    int opcion;
    while (true) {
        clear();
        cout << "Bienvenido " << user.getNombreUsuario() << "!" << endl;
        cout << "  MENU PRINCIPAL " << endl;
        cout << "-----------------" << endl;
        cout << "1 - MOVIMIENTOS" << endl;
        cout << "2 - CATEGORIAS" << endl;
        cout << "3 - INFORMES" << endl;
        cout << "5 - LOGOUT" << endl;
        cout << endl;
        cout << "0 - PARA SALIR" << endl;
        cout << "-----------------" << endl;

        cout << "INGRESE UNA OPCION: ";
        opcion = ingresoEntero();
        clear();
        switch (opcion) {
            case 1: {
                subMenuMovimientos.menu();
                }
                break;
            case 2: {
                subMenuCategorias.menu();
                break;
            }
           case 3:
            {
              //subMenuInformes.menu();
              break;
            }
           case 4:
            {
              //subMenuProveedor.menuProveedor();
            }
            break;
            case 5:
            {
                // log out
            }
            break;
           case 0:
            {
              return;
            }
            break;
           default:
            {
              cout << "OPCION INCORRECTA" << endl;
              pausa();
            }
          }
      clear();
    }
   return;
 }

void App::menuApp() {
    int opcion;
    UsuarioArchivo mgmtArchivoUsuario;
    UsuarioManager mgmtUsuarios;
    while (true) {
        clear();

        cout << "  SISTEMA DE FINANZAS PERSONALES" << endl;
        cout << "-----------------" << endl;
        cout << "1 - INGRESAR" << endl;
        cout << endl;
        cout << "0 - PARA SALIR" << endl;
        cout << "-----------------" << endl;

        cout << "INGRESE UNA OPCION: ";

        opcion = ingresoEntero();
        clear();

        switch (opcion) {
            case 1: {
                int userID;
                std::string password;

                cout << "Ingrese su identificacion: ";
                userID = ingresoEntero();

                Usuario usuario;
                usuario = mgmtArchivoUsuario.leerUsuario(userID);
                if (usuario.getUsuarioID() == -1) {
                    clear();
                    cout << "El usuario no existe." << endl;
                    cout << "Creando nuevo usuario nuevo..." << endl;
                    cout << endl;
                    usuario = mgmtUsuarios.registrarUsuario();
                } else {
                    cout << "Ingrese la contraseña de su usuario: ";
                    cin >> password;

                    if (!usuario.validarPassword(password)) {
                        cout << "Contraseña invalida." << endl;
                        pausa();
                        break;
                    }
                }
                MenuPrincipal(usuario);
                break;
            }
            default: {
                break;
            }
        }
    }
}

#include <iostream>
#include "funcionesGlobales.h"
using namespace std;
#include "app.h"
#include "menu.h"

void App::inicio() {
    while (true) {
        system("cls");
        Menu menu("SISTEMA DE FINANZAS PERSONALES");

        menu.addItem("INICIAR SESION");
        menu.addItem("REGISTRARSE");
        menu.addItem("SALIR");

        menu.showMenu();

        int seleccion = menu.getSelection();

        switch (seleccion) {
            case 1: {
                iniciarSesion();
                break;
            };
            case 2: {
                registrarse();
                break;
            };
            case 3: {
                break;
            }
            break;
        }
    }
}

void App::iniciarSesion() {
    system("cls");

    //Usuario usuarioNuevo;
    //if (!usuarioNuevo.registrarUsuarioNuevo()) {
    //    return;
    //}
    MenuPrincipal();
}

void App::registrarse() {

}

void App::MenuPrincipal() {
    Menu menu("MENU PRINCIPAL");

    menu.addItem("MOVIMIENTOS");
    menu.addItem("CATEGORIAS");
    menu.addItem("INFORMES");
    menu.addItem("?????");
    menu.addItem("Logout");

    menu.showMenu();

    int seleccion = menu.getSelection();
}

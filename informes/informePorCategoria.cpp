#include <iostream>
#include "informePorCategoria.h"
#include "../usuarios/usuario.h"
#include "../categorias/categoriaManager.h"
#include "../movimientos/movimientoManager.h"
#include "../funcionesGlobales.h"

void InformePorCategoria::balancePorCateoria(const Usuario &user) {
    MovimientoArchivo movArch("movimientos.dat");
    Movimiento mov;
    CategoriaArchivo categoriaArchivo("categorias.dat");
    int cantReg = categoriaArchivo.contarRegistros();
    Categoria categoriaAuxiliar;

    float * ingresoCat = new float[cantReg]{0};
    if (ingresoCat == nullptr) exit(-1);

    for (int i = 0; i < cantReg; i++) {
        mov = movArch.leer(i);
        if (user.getUsuarioID() == mov.getIdUsuario()) {
            ingresoCat[mov.getIdCategoria() - 1] += mov.getImporte();
        }

    }

    cout << "Ingresos por categoria" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < cantReg; i++) {
        categoriaAuxiliar = categoriaArchivo.leerRegistro(i);
        if (categoriaAuxiliar.getEstado()) {
            string nombreDeCategoria = categoriaAuxiliar.getNombre();
            cout << i+1 << " - " << nombreDeCategoria << ": $" << ingresoCat[i] << endl;
        }
    }
    cout << "------------------------------" << endl;
    delete []ingresoCat;
    pausa();
};

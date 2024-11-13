#include <iostream>
#include "porCategoria.h"
#include "categoriaManager.h"
#include "movimientoManager.h"
#include "funcionesGlobales.h"

void PorCategoria::balancePorCateoria() {
    MovimientoArchivo movArch("movimientos.dat");
    int cantMov = movArch.contarRegistros();
    Movimiento mov;
    float ingresoCat[20]={};

    for (int i = 0; i < cantMov; i++) {
        mov = movArch.leer(i);
        ingresoCat[mov.getIdCategoria()-1] += mov.getImporte();
    }

    CategoriaArchivo catArch("categorias.dat");
    int cantCat= catArch.contarRegistros();
    Categoria cat;

    cout << "Ingresos por categoria" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < cantCat; i++) {
        cat = catArch.leerRegistro(i);
        string nombreDeCategoria = cat.getNombre();
        cout << i+1 << " - " << nombreDeCategoria << ": $" << ingresoCat[i] << endl;
    }
    cout << "------------------------------" << endl;
    pausa();
};

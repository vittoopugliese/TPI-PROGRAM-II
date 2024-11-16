#pragma once
#include "usuarioManager.h"
#include "movimiento.h"
#include "movimientoArchivo.h"
#include "categoriaManager.h"
#include "funcionesGlobales.h"
#include "fecha.h"
#include <string>
using namespace std;

class MovimientoManager{
public:
    void menu(const Usuario &user);
    void cargar(const Usuario &user);
    void mostrar(Movimiento reg);
    void baja(const Usuario &user);
    void mostrarTodos(const Usuario &user);
    //-------FILTROS------
    void menuFiltros(const Usuario &user);
    void porTipo(const Usuario &user);
    void porCategoria(const Usuario &user);
    void porFecha(const Usuario &user);
};

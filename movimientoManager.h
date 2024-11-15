#pragma once
#include "movimiento.h"
#include "movimientoArchivo.h"
#include "usuarioManager.h"
#include <string>
using namespace std;

class MovimientoManager{
public:
    void menu(const Usuario &user);
    void cargar(const Usuario &user);
    void mostrar(Movimiento reg);
    void eliminarMovimiento(const Usuario &user);
    void mostrarTodos(const Usuario &user);
    void modificar(const Usuario &user);
    //-------FILTROS------
    void menuFiltros(const Usuario &user);
    void menuModificarMovimiento(const Usuario &user);
    void porTipo(const Usuario &user);
    void porCategoria(const Usuario &user);
    void porFecha(const Usuario &user);

    // ---------- MODIFICADORES DE MOVIMIENTO ----------
    void modificarMovimientoCategoria(Movimiento &movimientoAModificar);
    void modificarMovimientoFecha(Movimiento &movimientoAModificar);
    void modificarMovimientoImporte(Movimiento &movimientoAModificar);
    void modificarMovimientoRecurrencia(Movimiento &movimientoAModificar);
    void modificarMovimientoTipoDeRecurrencia(Movimiento &movimientoAModificar);
    void modificarMovimientoEsFijo(Movimiento &movimientoAModificar);
    void modificarMovimientoDescripcion(Movimiento &movimientoAModificar);
};

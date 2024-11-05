#include <iostream>
using namespace std;
#include "movimiento.h"
#include "funcionesGlobales.h"
#include "movimientoArchivo.h"

Movimiento::Movimiento(int idMovimiento, bool idTipo, int idUsuario, int idCategoria, Fecha fecha, float importe, bool recurrencia, const char *descripcion, bool estado){
    _idMovimiento = idMovimiento;
    _idTipo = idTipo;
    _idUsuario = idUsuario;
    _idCategoria = idCategoria;
    _fecha = fecha;
    _importe = importe;
    _recurrencia = recurrencia;
    _tipoDeRecurrencia = 0;
    strcpy(_descripcion, descripcion);
    _estado = estado;
};

Movimiento::Movimiento(){
    _idMovimiento = 0;
    _idTipo = 0;  // 0-Credito | 1-Debito
    _idUsuario = 1;
    _idCategoria = 0;
    _fecha = Fecha();
    _importe = 0;
    _recurrencia = 0;
    _tipoDeRecurrencia = 0; // 0-Mensual | 1-Bimestral | 2-Anual
    strcpy(_descripcion, "S/D"); // SD = Sin Descripcion
    _estado = true;
};

// SETTERS
void Movimiento::setIdMovimiento(int idMovimiento){_idMovimiento = idMovimiento;}
void Movimiento::setIdTipo(bool idTipo){_idTipo = idTipo;}
void Movimiento::setIdUsuario(int idUsuario){_idUsuario = idUsuario;}
void Movimiento::setIdCategoria(int idCategoria){_idCategoria = idCategoria;}
void Movimiento::setFecha(Fecha fecha){_fecha = fecha;}
void Movimiento::setImporte(float importe){_importe = importe;}
void Movimiento::setRecurrencia(bool recurrencia){_recurrencia = recurrencia;}
void Movimiento::setDescripcion(const char *descripcion){strcpy(_descripcion, descripcion);}
void Movimiento::setEstado(bool estado){_estado = estado;}
void Movimiento::setTipoDeRecurrencia(int tipoDeRecurrencia){_tipoDeRecurrencia = tipoDeRecurrencia;}

// GETTERS
int Movimiento::getIdMovimiento(){return _idMovimiento;}
bool Movimiento::getIdTipo(){return _idTipo;}
int Movimiento::getIdUsuario(){return _idUsuario;}
int Movimiento::getIdCategoria(){return _idCategoria;}
Fecha Movimiento::getFecha(){return _fecha;}
float Movimiento::getImporte(){return _importe;}
bool Movimiento::getRecurrencia(){return _recurrencia;}
const char* Movimiento::getDescripcion(){return _descripcion;}
bool Movimiento::getEstado(){return _estado;}
int Movimiento::getTipoDeRecurrencia(){return _tipoDeRecurrencia;}
string Movimiento::getNombreDeRecurrencia(){
    switch(_tipoDeRecurrencia){
        case 0: return "Mensual";
        case 1: return "Bimestral";
        case 2: return "Anual";
        default: return "Sin Recurrencia";
    }
}

int Movimiento::generarIdDeMovimiento(int mes, int dia){
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    return (mes * 1000) + (dia * 10) + archivoMovimiento.contarRegistros() + 1;
}
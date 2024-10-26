#include <iostream>
using namespace std;
#include "movimiento.h"
#include "funcionesGlobales.h"

Movimiento::Movimiento(int idMovimiento, bool idTipo, int idUsuario, int idCategoria, Fecha fecha, float importe, bool recurrencia, const char *descripcion, bool estado){
    _idMovimiento = idMovimiento;
    _idTipo = idTipo;  // 0-Credito | 1-Debito
    _idUsuario = idUsuario;
    _idCategoria = idCategoria;
    _fecha = fecha;
    _importe = importe;
    _recurrencia = recurrencia;
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
    strcpy(_descripcion, "S/D"); // SD = Sin Descripcion
    _estado = true;
};

//SETS
void Movimiento::setIdMovimiento(int idMovimiento){_idMovimiento = idMovimiento;}
void Movimiento::setIdTipo(bool idTipo){_idTipo = idTipo;}
void Movimiento::setIdUsuario(int idUsuario){_idUsuario = idUsuario;}
void Movimiento::setIdCategoria(int idCategoria){_idCategoria = idCategoria;}
void Movimiento::setFecha(Fecha fecha){_fecha = fecha;}
void Movimiento::setImporte(float importe){_importe = importe;}
void Movimiento::setRecurrencia(bool recurrencia){_recurrencia = recurrencia;}
void Movimiento::setDescripcion(const char *descripcion){strcpy(_descripcion, descripcion);}
void Movimiento::setEstado(bool estado){_estado = estado;}

//GETS
int Movimiento::getIdMovimiento(){return _idMovimiento;}
bool Movimiento::getIdTipo(){return _idTipo;}
int Movimiento::getIdUsuario(){return _idUsuario;}
int Movimiento::getIdCategoria(){return _idCategoria;}
Fecha Movimiento::getFecha(){return _fecha;}
float Movimiento::getImporte(){return _importe;}
bool Movimiento::getRecurrencia(){return _recurrencia;}
const char* Movimiento::getDescripcion(){return _descripcion;}
bool Movimiento::getEstado(){return _estado;}

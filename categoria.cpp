#include <iostream>
#include "categoria.h"
#include "categoriaManager.h"
using namespace std;

//CONSTRUCTORES
Categoria::Categoria(int tipoDeMovimiento, int idCategoria,char nombre[20], char descripcion[50], bool estado) {
    _idUsuario = 0;
    _tipoMovimiento = tipoDeMovimiento;
    strcpy(_nombre, nombre);
    strcpy(_descripcion, descripcion);
    _estado = true;
}

Categoria::Categoria() {
    _idUsuario = 0;
    _tipoMovimiento = 0;
    strcpy(_nombre, "S/N");
    strcpy(_descripcion, "S/N");
    _estado = true;
}

//SET
void Categoria::setTipoMovimiento(int tipoMovimiento) {_tipoMovimiento = tipoMovimiento;}
void Categoria::setIdCategoria(int idCategoria) {_idCategoria = idCategoria;}
void Categoria::setNombre(const char *nombre) {strcpy(_nombre, nombre);}
void Categoria::setDescripcion(const char *categoria) {strcpy(_descripcion, categoria);}
void Categoria::setEstado(bool estado) {_estado = estado;}
void Categoria::setCategoriaIDUsuario(int idUsuario) {_idUsuario = idUsuario;}

//GET
int Categoria::getTipoMovimiento() {return _tipoMovimiento;}
int Categoria::getIdCategoria() {return _idCategoria;}
const char *Categoria::getNombre() {return _nombre;}
const char *Categoria::getDescripcion() {return _descripcion;}
bool Categoria::getEstado(){return _estado;}
int Categoria::getCategoriaIDUsuario() {return _idUsuario;}

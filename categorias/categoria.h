#pragma once
#include <cstring>
using namespace std;
class Categoria {
private:
    int _tipoMovimiento; // 0-Credito | 1-Debito
    int _idCategoria;
    char _nombre[20];
    char _descripcion[50];
    bool _estado;

public:
    Categoria(int tipoMovimiento, int idCategoria, char nombre[20], char descripcion[50], bool estado = true);
    Categoria();
    // SETTERS
    void setTipoMovimiento(int tipoMovimiento);
    void setIdCategoria(int idCategoria);
    void setNombre(const char *nombre);
    void setDescripcion(const char *categoria);
    void setEstado(bool estado);
    // GETTERS
    int getTipoMovimiento();
    int getIdCategoria();
    const char *getNombre();
    const char *getDescripcion();
    bool getEstado();
};

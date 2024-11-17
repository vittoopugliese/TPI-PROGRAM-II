#pragma once
using namespace std;
#include "../fecha.h"
class Movimiento {
private:
    int _idMovimiento;
    bool _idTipo; // 0-Credito | 1-Debito
    int _idUsuario;
    int _idCategoria;
    Fecha _fecha;
    float _importe;
    bool _recurrencia;
    int _tipoDeRecurrencia; // 0-Unico, 1-Mensual, 2-Bimestral, 3-Anual
    char _descripcion[100];
    bool _estado;
    bool _esFijo;

public:
    Movimiento(int idMovimiento, bool idTipo, int idUsuario, int idCategoria, Fecha fecha, float importe, bool recurrencia, const char *descripcion, bool estado, bool esFijo);
    Movimiento();

    // SETTERS
    void setIdMovimiento(int idMovimiento);
    void setIdTipo(bool idTipo);
    void setIdUsuario(int idUsuario);
    void setIdCategoria(int idCategoria);
    void setFecha(Fecha fecha);
    void setImporte(float importe);
    void setRecurrencia(bool recurrencia);
    void setTipoDeRecurrencia(int tipoDeRecurrencia);
    void setDescripcion(const char *descripcion);
    void setEstado(bool estado);
    void setEsFijo(bool esFijo);

    // GETTERS
    int getIdMovimiento();
    bool getIdTipo();
    int getIdUsuario();
    int getIdCategoria();
    Fecha getFecha();
    float getImporte();
    bool getRecurrencia();
    const char *getDescripcion();
    bool getEstado();
    int getTipoDeRecurrencia();
    string getNombreDeRecurrencia();
    bool getEsFijo(); // LO AGREGUE PARA INDICADORES, NECESITO IDENTIFICAR QUE ES FIJO
};

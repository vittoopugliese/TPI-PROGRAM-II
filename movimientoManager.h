#ifndef MANAGER_MOVIMIENTOS_H
#define MANAGER_MOVIMIENTOS_H
#include <string>
using namespace std;

class ManagerMovimientos {
private:
    int idMovimiento;
    bool tipoMovimiento; // tipo movimiento en nuestro diagrama es bool pero no creo que sea lo mejor
    string categoria;

public:
    ManagerMovimientos();

    void abrir();
    bool guardar();
    int buscar();
    void filtrar();

    int getIdMovimiento() const;
    bool getTipoMovimiento() const;
    string getCategoria() const;

    void setIdMovimiento(int id);
    void setTipoMovimiento(bool tipo);
    void setCategoria(const std::string& cat);
};

#endif
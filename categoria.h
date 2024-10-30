#pragma once
#include <cstring>
using namespace std;

class Categoria {
    private:
        int _tipoDeMovimiento;
        int _idCategoria;
        char _nombreCategoria[20];
        char _descripcion[50];
    public:
        //void GenerarInforme();
        Categoria(int tipoDeMovimiento, char nombreCategoria[20], char descripcion[50]);
        Categoria();

        const char *getNombreCategoria();
        int getIdCategoria();
        void setNombreCategoria(const char *nombre);
        void setDescripcionCategoria(const char *categoria);
};

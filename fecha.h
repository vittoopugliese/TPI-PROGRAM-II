#pragma once
#include <string>
using namespace std;

class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;
        int _diasPorMes[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    public:
        Fecha();
        Fecha(int dia, int mes, int anio);
        void validar();
        //----------
        void setDia(int dia);
        void setMes(int mes);
        void setAnio(int anio);
        //-----------
        int getDia();
        int getMes();
        int getAnio();
        int getDiasMes();
        //-----------
        void Cargar();
        void Mostrar();
        //-----------
        string toString();
};

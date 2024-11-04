#pragma once
#include <string>
using namespace std;

class Fecha
 {
   private:
    int _dia;
    int _mes;
    int _anio;

   public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);
    //-----------
    int getDia();
    int getMes();
    int getAnio();
    //-----------
    void Cargar();
    void Mostrar();
    //-----------
    string toString();
 };

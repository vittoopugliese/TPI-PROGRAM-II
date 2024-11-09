#include <iostream>
using namespace std;
#include "fecha.h"
#include <ctime>

Fecha::Fecha()
{
    time_t now = time(0);
    tm* tmPtr = localtime(&now);
    _anio=tmPtr->tm_year+1900;
    _mes=tmPtr->tm_mon+1;
    _dia=tmPtr->tm_mday;
}

Fecha::Fecha(int dia, int mes, int anio)
{
    if (dia > 0 && dia <32 && mes > 0 && mes < 13 && anio > 0)
    {
        _dia = dia;
        _mes = mes;
        _anio = anio;
    } else {
        cout << "INGRESE UNA FECHA VALIDA";
    }

    validar();
}

void Fecha::validar(){
    if(_mes==2 && (_anio%4)==0){ //Agrego 1 dia a Febrero si es bisisesto
        _diasPorMes[1]++;
    }

    if(!(_dia >= 1 && _dia <= _diasPorMes[_mes-1])
        || !(_mes >=1 && _mes <= 12)
        || !(_anio > 0)
    )
    {
        _dia = 1;
        _mes = 1;
        _anio = 2023;
    }
}

//SETS
void Fecha::setDia(int dia){_dia = dia;}
void Fecha::setMes(int mes){_mes = mes;}
void Fecha::setAnio(int anio){_anio = anio;}

//GETS
int Fecha::getDia(){return _dia;}
int Fecha::getMes(){return _mes;}
int Fecha::getAnio(){return _anio;}
int Fecha::getDiasMes(){return _diasPorMes[_mes-1];}

void Fecha::Cargar()
{
    cout << "DIA: ";
    cin >> _dia;
    cout << "MES: ";
    cin >> _mes;
    cout << "ANIO: ";
    cin >> _anio;
}

void Fecha::Mostrar()
{
    cout << (_dia <= 9 ? "0" : "" ) << _dia << "/";
    cout << (_mes <= 9 ? "0" : "" ) << _mes << "/";
    cout << (_anio <= 9 ? "0" : "" ) << _anio << endl;
}

string Fecha::toString()
{
    return to_string(_dia) + "/" + to_string (_mes) + "/" + to_string (_anio);
}

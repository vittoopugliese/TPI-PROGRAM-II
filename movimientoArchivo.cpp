#include <iostream>
using namespace std;

struct RegistroDiario {
    string categoria;
    int monto;
};

class MovimientoArchivo {
private:
    string nombreArchivo;
    RegistroDiario registros[12][30];

public:
    MovimientoArchivo(string nombre){
        nombreArchivo = nombre;
    }

    bool guardarRegistros(int mes, RegistroDiario registrosMes[30]) {
        if (mes < 1 || mes > 12) return false;

        for (int i = 0; i < 30; i++) registros[mes - 1][i] = registrosMes[i];

        ofstream archivo(nombreArchivo, ios::binary);

        if (!archivo) return false;

        archivo.write((char *)&registros, sizeof(registros));
        archivo.close();

        return true;
    }

    bool leerRegistros(int mes, RegistroDiario registrosMes[30]) {
        if (mes < 1 || mes > 12) return false;

        ifstream archivo(nombreArchivo, ios::binary);

        if (!archivo) return false;

        archivo.read((char *)&registros, sizeof(registros));

        for (int i = 0; i < 30; i++) registrosMes[i] = registros[mes - 1][i];

        archivo.close();

        return true;
    }
};
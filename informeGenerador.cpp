#include <iostream>
#include <fstream>
#include <ctime>

#include "funcionesGlobales.h"
#include "movimientoArchivo.h"
#include "fecha.h"
#include "categoriaManager.h"
#include "Usuario.h"
#include "Movimiento.h"

using namespace std;

class InformeGenerador {
public:
    void generarInformeTXT(const Usuario &user);
};

void InformeGenerador::generarInformeTXT(const Usuario &user) {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    CategoriaManager categoriaManager;
    int cantidad = archivoMovimiento.contarRegistros();

    if (cantidad == 0) {
        cout << "No hay movimientos para generar el informe." << endl;
        pausa();
        return;
    }

    time_t now = time(0);
    tm* ltm = localtime(&now);
    string nombreArchivo = "informe_" +
                          to_string(ltm->tm_mday) + "-" +
                          to_string(1 + ltm->tm_mon) + "-" +
                          to_string(1900 + ltm->tm_year) + ".txt";

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo de informe." << endl;
        pausa();
        return;
    }

    archivo << "INFORME DE MOVIMIENTOS" << endl;
    archivo << "======================" << endl << endl;

    archivo << "INGRESOS (CREDITOS)" << endl;
    archivo << "===================" << endl;
    float totalIngresos = 0;

    // TODO:  se puede separar en funciones como en informeBalance...

    for (int i = 0; i < cantidad; i++) {
        Movimiento mov = archivoMovimiento.leer(i);
        if (mov.getIdUsuario() == user.getUsuarioID() && mov.getEstado() && mov.getIdTipo() == 0) {
            archivo << "Fecha: " << mov.getFecha().toString() << endl;
            archivo << "Importe: $" << mov.getImporte() << endl;
            archivo << "Categoría: " << categoriaManager.getNombreCategoria(mov.getIdCategoria()) << endl;
            archivo << "Descripción: " << mov.getDescripcion() << endl;
            archivo << "------------------------" << endl;
            totalIngresos += mov.getImporte();
        }
    }
    archivo << "Total Ingresos: $" << totalIngresos << endl << endl;

    archivo << "EGRESOS (DEBITOS)" << endl;
    archivo << "=================" << endl;
    float totalEgresos = 0;

    for (int i = 0; i < cantidad; i++) {
        Movimiento mov = archivoMovimiento.leer(i);
        if (mov.getIdUsuario() == user.getUsuarioID() && mov.getEstado() && mov.getIdTipo() == 1) {
            archivo << "Fecha: " << mov.getFecha().toString() << endl;
            archivo << "Importe: $" << mov.getImporte() << endl;
            archivo << "Categoría: " << categoriaManager.getNombreCategoria(mov.getIdCategoria()) << endl;
            archivo << "Descripción: " << mov.getDescripcion() << endl;
            archivo << "------------------------" << endl;
            totalEgresos += mov.getImporte();
        }
    }
    archivo << "Total Egresos: $" << totalEgresos << endl << endl;

    archivo << "BALANCE FINAL" << endl;
    archivo << "=============" << endl;
    float balanceFinal = totalIngresos - totalEgresos;
    archivo << "Total: $" << balanceFinal << endl;
    archivo << "Estado: " << (balanceFinal > 0 ? "POSITIVO" : balanceFinal < 0 ? "NEGATIVO" : "NEUTRO") << endl;

    archivo.close();

    cout << "Informe generado exitosamente como '" << nombreArchivo << "'" << endl;
    pausa();
}

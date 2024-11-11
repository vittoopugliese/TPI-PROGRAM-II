#include "indicadores.h"
#include <iostream>
#include <vector>
#include <cstring>
#include "movimientoArchivo.h"  // Incluye MovimientoArchivo para acceder a sus métodos
#include "funcionesGlobales.h"

//Indicadores::Indicadores(MovimientoManager* mManager) : movimientoManager(mManager) {}

float Indicadores::calcularRelacionIngresoGasto() {
    float ingresosTotales = 0;
    float gastosTotales = 0;

    MovimientoArchivo archivoMovimientos("movimientos.dat");
    int cantRegistros = archivoMovimientos.contarRegistros();

    for (int i = 0; i < cantRegistros; i++) {
        Movimiento movimiento = archivoMovimientos.leer(i);
        if (movimiento.getIdTipo() == 0) { // Ingreso
            ingresosTotales += movimiento.getImporte();
        } else if (movimiento.getIdTipo() == 1) { // Gasto
            gastosTotales += movimiento.getImporte();
        }
    }

    if (ingresosTotales == 0) return (gastosTotales > 0) ? 100 : 0;
    return (gastosTotales / ingresosTotales) * 100;
}

void Indicadores::calcularDistribucionGastos(float &gastosFijos, float &gastosVariables) {
    gastosFijos = 0;
    gastosVariables = 0;
    float gastosTotales = 0;

    MovimientoArchivo archivoMovimientos("movimientos.dat");
    int cantRegistros = archivoMovimientos.contarRegistros();

    for (int i = 0; i < cantRegistros; i++) {
        Movimiento movimiento = archivoMovimientos.leer(i);
        if (movimiento.getIdTipo() == 1) { // Gasto
            gastosTotales += movimiento.getImporte();

            // Aquí asumimos que existe un método esGastoFijo() que verifica el tipo de gasto
            if (movimiento.getEsFijo()) {
                gastosFijos += movimiento.getImporte();
            } else {
                gastosVariables += movimiento.getImporte();
            }
        }
    }

    if (gastosTotales > 0) {
        gastosFijos = (gastosFijos / gastosTotales) * 100;
        gastosVariables = (gastosVariables / gastosTotales) * 100;
    } else {
        gastosFijos = gastosVariables = 0;
    }
}

void Indicadores::mostrarGraficoRelacion() {
    float relacion = calcularRelacionIngresoGasto();
    std::cout << "Relacion Ingreso vs. Gasto: " << relacion << "%" << std::endl;
    if (relacion > 100) {
        std::cout << "Deficit: Gastos superan ingresos." << std::endl;
    } else {
        std::cout << "Superavit: Ingresos superan gastos." << std::endl;
    }
}

void Indicadores::mostrarGraficoDistribucion() {
    float gastosFijos = 0, gastosVariables = 0;
    calcularDistribucionGastos(gastosFijos, gastosVariables);
    std::cout << "Distribucion de Gastos:" << std::endl;
    std::cout << "Gastos Fijos: " << gastosFijos << "%" << std::endl;
    std::cout << "Gastos Variables: " << gastosVariables << "%" << std::endl;
}

void Indicadores::showIndicadores() {
    cout << "RELACION INGRESO VS GASTO" << endl;
    mostrarGraficoRelacion(); //Agrego para indicadores --> FRAN

    float gastosFijos =0; //Agrego para indicadores --> FRAN
    float gastosVariables = 0;//Agrego para indicadores --> FRAN
    calcularDistribucionGastos(gastosFijos, gastosVariables); //Agrego para indicadores --> FRAN

    cout << "\n=== Distribución de Gastos ===" << endl;
    cout << "Gastos Fijos: " << gastosFijos << "%" << endl;
    cout << "Gastos Variables: " << gastosVariables << "%" << endl;
    pausa();
}

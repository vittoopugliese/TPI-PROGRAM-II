#include <iostream>
#include <vector>
#include <cstring>

#include "informeIndicadores.h"
#include "../movimientoManager.h"  // Incluye MovimientoArchivo para acceder a sus métodos
#include "../funcionesGlobales.h"
#include "../asciichart/ascii.h"

float InformeIndicadores::calcularRelacionIngresoGasto() {
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

void InformeIndicadores::calcularDistribucionGastos(float &gastosFijos, float &gastosVariables) {
    gastosFijos = 0;
    gastosVariables = 0;
    float gastosTotales = 0;

    MovimientoArchivo archivoMovimientos("movimientos.dat");
    int cantRegistros = archivoMovimientos.contarRegistros();

    for (int i = 0; i < cantRegistros; i++) {
        Movimiento movimiento = archivoMovimientos.leer(i);
        if (movimiento.getIdTipo() == 1) { // Gasto
            gastosTotales += movimiento.getImporte();


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

void InformeIndicadores::mostrarGraficoRelacion() {
    float relacion = calcularRelacionIngresoGasto();
    std::cout << "==========================================================================" << std::endl;
    std::cout << "======================= Relacion Ingreso vs. Gasto =======================" << std::endl;
    std::cout << "==========================================================================" << std::endl;
    std::cout << "Relacion Ingreso vs. Gasto: " << relacion << "%" << std::endl;

    cout << "Superavit: Ingresos superan gastos." << endl;
    cout << "La relacion representa la proporcion porcentual de los gastos sobre el ingreso, y se representa en un eje porcentual de 0 a 100." << endl;
    cout << "La linea Roja representa el porcentaje del gasto sobre el Ingreso." << endl;
    cout <<"\n"<<endl;
    if (relacion > 100) {
        std::cout << "Deficit: Gastos superan ingresos." << std::endl;
    } else {

        const int puntosGrafico = 30; //eje X
        std::vector<double> lineaRelacion(puntosGrafico, relacion); // Línea gasto

        // Configurar el gráfico ASCII
        ascii::Asciichart grafico({
            {"Relacion del Gasto", lineaRelacion}
        });

        grafico.height(10)
               .min(0)
               .max(100)
               .show_legend(true)
               .styles({
                   ascii::Style().fg(ascii::Foreground::From(ascii::Color::BRIGHT_RED))
               });



        std::cout << grafico.Plot() << std::endl;
    }
}

void InformeIndicadores::mostrarGraficoDistribucion() {
    float gastosFijos = 0, gastosVariables = 0;
    calcularDistribucionGastos(gastosFijos, gastosVariables);

    const int puntosGrafico = 30;
    std::vector<double> lineaGastosFijos(puntosGrafico, gastosFijos);
    std::vector<double> lineaGastosVariables(puntosGrafico, gastosVariables);


    ascii::Asciichart graficoDistribucion({
        {"Gastos Fijos (%)", lineaGastosFijos},
        {"Gastos Variables (%)", lineaGastosVariables}
    });

    graficoDistribucion.height(10)
                       .min(0)
                       .max(100)
                       .show_legend(true)
                       .styles({
                           ascii::Style().fg(ascii::Foreground::From(ascii::Color::BRIGHT_CYAN)),
                           ascii::Style().fg(ascii::Foreground::From(ascii::Color::BRIGHT_RED))
                       });



    std::cout << graficoDistribucion.Plot() << std::endl;
}

void InformeIndicadores::showIndicadores() {

    mostrarGraficoRelacion(); //Agrego para indicadores --> FRAN

    float gastosFijos =0; //Agrego para indicadores --> FRAN
    float gastosVariables = 0;//Agrego para indicadores --> FRAN


    calcularDistribucionGastos(gastosFijos, gastosVariables); //Agrego para indicadores --> FRAN

    cout << "============================================================================" << endl;
    cout << "========================== Distribución de Gastos ==========================" << endl;
    cout << "============================================================================" << endl;
    cout << "Gastos Fijos: " << gastosFijos << "%" << endl;
    cout << "Gastos Variables: " << gastosVariables << "%" << endl;
    cout << "\n" << endl;
    mostrarGraficoDistribucion();

    pausa();
}

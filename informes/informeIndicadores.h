#pragma once
#include "../movimientoManager.h"
#include "../movimiento.h"

class InformeIndicadores {
public:
    // Calcula la relación entre ingresos y gastos totales
    float calcularRelacionIngresoGasto();

    // Calcula la distribución de gastos fijos y variables
    void calcularDistribucionGastos(float &gastosFijos, float &gastosVariables);

    // Métodos para mostrar resultados en la consola
    void showIndicadores();
    void mostrarGraficoRelacion();
    void mostrarGraficoDistribucion();
};

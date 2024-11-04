#include "movimientoManager.h"
#include "movimiento.h"
#include "fecha.h"
#include "funcionesGlobales.h"
#include <iostream>
#include "movimientoArchivo.h"
using namespace std;

void MovimientoManager::cargar() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento aux;

    int mes;
    int anio;
    int cantidadDeDiasEnElMes = 30;

    float subtotalDia = 0;
    float subtotalMes = 0;

    cout << "Ingrese el anio de lo movimientos a cargar (0 para salir): ";
    cin >> anio;

    if(anio == 0) return;

    cout << "Ingrese el numero del mes (1-12): ";
    cin >> mes;

    while(mes < 1 || mes > 12) {
        cout << "Mes invalido. Por favor ingrese un mes entre 1 y 12: ";
        cin >> mes;
    }

    if(mes == 2) {
        if(anio % 4 == 0) cantidadDeDiasEnElMes = 29;
        else cantidadDeDiasEnElMes = 28;
    } else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        cantidadDeDiasEnElMes = 30;
    } else {
        cantidadDeDiasEnElMes = 31;
    }

    for(int dia = 1; dia <= cantidadDeDiasEnElMes; dia++) {
        clear();
        cout << "Dia: " << dia << endl;
        cout << "------------------------------------" << endl;

        subtotalDia = 0;
        int respuesta = 1;

        while(respuesta == 1) {
            int categoria;
            cout << "Ingrese el ID de categoria (0 para no registrar movimientos): ";
            cin >> categoria;

            if(categoria == 0) break;

            // Genero el ID del dia, logica a discutir...
            int idMovimiento = (mes * 1000) + (dia * 10) + archivoMovimiento.contarRegistros() + 1;
            aux.setIdMovimiento(idMovimiento);

            int tipoMovimiento;
            cout << "Tipo de movimiento (0-Credito, 1-Debito): ";
            cin >> tipoMovimiento;

            while(tipoMovimiento != 0 && tipoMovimiento != 1) {
                cout << "Tipo invalido. Ingrese 0 para Credito o 1 para Debito: ";
                cin >> tipoMovimiento;
            }

            aux.setIdTipo(tipoMovimiento);
            aux.setIdCategoria(categoria);

            float importe;
            cout << "Ingrese el importe del movimiento: $";
            cin >> importe;

            while(importe < 0) {
                // Aca podemos validar la categoria y su tipo con el monto ingresado
                // si se ingresa un monto positivo y la categoria es DEBITO, deberiamos
                // mostrar el mensaje de que se esta ingresando al reves.
                // o sino, no darle importancia al signo y calcular si es un monto que RESTA
                // si la categoria es debito... a debatir
                cout << "El importe no puede ser negativo. Ingrese nuevamente: $";
                cin >> importe;
            }

            aux.setImporte(importe);

            if(tipoMovimiento == 0) {
                subtotalDia += importe;
                subtotalMes += importe;
            } else {
                subtotalDia -= importe;
                subtotalMes -= importe;
            }

            Fecha fecha;
            fecha.setMes(mes);
            fecha.setDia(dia);
            fecha.setAnio(anio);
            aux.setFecha(fecha);

            char recurrente;
            cout << "Es un movimiento recurrente? (S/N): ";
            cin >> recurrente;
            aux.setRecurrencia(toupper(recurrente) == 'S');

            char descripcion[100];
            cout << "Ingrese descripcion: ";
            cin.ignore();
            cin.getline(descripcion, 100);
            aux.setDescripcion(descripcion);

            aux.setEstado(true);

            // Guardo el movimiento en el archivo
            if(archivoMovimiento.guardarArchivo(aux)) {
                cout << "Movimiento guardado exitosamente!" << endl << endl;
            } else {
                cout << "Error al guardar el movimiento." << endl << endl;
            }

            cout << "Subtotal del dia: $" << subtotalDia << endl;
            cout << "------------------------------------" << endl;

            cout << "Cargar otro movimiento para este dia? (1-Si, 0-No): ";
            cin >> respuesta;
        }

        cout << "Total del dia " << dia << ": $" << subtotalDia << endl;
        pausa();
    }

    clear();
    cout << "Resumen del mes " << mes << ":" << endl;
    cout << "Total del mes: $" << subtotalMes << endl;
    pausa();
}

void MovimientoManager::mostrar(Movimiento reg) {
    if(reg.getEstado()) {
        cout << "ID Movimiento: " << reg.getIdMovimiento() << endl;
        cout << "Fecha: " << reg.getFecha().toString() << endl;
        cout << "Categoria: " << reg.getIdCategoria() << endl;
        cout << "Tipo: " << (reg.getIdTipo() == 0 ? "Credito" : "Debito") << endl;
        cout << "Importe: $" << reg.getImporte() << endl;
        cout << "Descripcion: " << reg.getDescripcion() << endl;
        cout << "Recurrente: " << (reg.getRecurrencia() ? "Si" : "No") << endl;
        cout << "-------------------------------" << endl;
    }
}

void MovimientoManager::mostrarTodos() {
    clear();
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();

    if(cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        return;
    }

    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);
        if(reg.getEstado()) {
            mostrar(reg);
        }
    }
    pausa();
}

void MovimientoManager::eliminarTodos() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();

    if(cantidad == 0) {
        cout << "No hay movimientos para eliminar." << endl;
        pausa();
        return;
    }

    char confirmar;
    cout << "Esta seguro que desea eliminar TODOS los movimientos? (S/N): ";
    cin >> confirmar;

    if(toupper(confirmar) != 'S') {
        cout << "Operacion cancelada." << endl;
        pausa();
        return;
    }

    bool archivosEliminados = archivoMovimiento.vaciarArchivo();

    if(archivosEliminados) cout << "Todos los movimientos fueron eliminados exitosamente." << endl;
    else  cout << "Hubo un error al intentar eliminar los movimientos." << endl;

    pausa();
}

void MovimientoManager::menu() {
    int opcion;

    while(true) {
        clear();
        cout << "--- MOVIMIENTOS ---" << endl;
        cout << "----------------------" << endl;
        cout << "1 - CARGAR MOVIMIENTOS" << endl;
        cout << "2 - MOSTRAR TODOS" << endl;
        cout << "3 - ELIMINAR TODOS" << endl;
        cout << "0 - VOLVER" << endl;
        cout << "----------------------" << endl;

        cout << "INGRESE OPCION: ";
        cin >> opcion;

        clear();

        switch(opcion) {
            case 1:
                cargar();
                break;
            case 2:
                mostrarTodos();
                break;
            case 3:
                eliminarTodos();
                break;
            case 0:
                return;
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
        }

        clear();
    }
}

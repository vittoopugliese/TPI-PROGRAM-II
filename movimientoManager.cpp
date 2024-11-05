#include "movimientoManager.h"
#include "movimiento.h"
#include "fecha.h"
#include "funcionesGlobales.h"
#include <iostream>
#include "movimientoArchivo.h"
#include "categoriaManager.h"
using namespace std;

void MovimientoManager::cargar() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento aux;
    CategoriaManager categoriaManager;

    int mes;
    int anio;
    int cantidadDeDiasEnElMes = 30;

    float subtotalDia = 0;
    float subtotalMes = 0;

    cout << "Ingrese el anio de los movimientos a cargar (0 - Salir): ";
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
        cout << "Anio " << anio << " - Mes " << mes << " - Dia: " << dia << endl;
        cout << "------------------------------------" << endl;

        subtotalDia = 0;
        char seguirCargandoMovimientos = 'S';

        while(toupper(seguirCargandoMovimientos) == 'S') {
            categoriaManager.mostrarTodasInline();
            cout << endl << "Ingrese el ID de categoria (0 - No registrar movimientos): ";
            int idCategoria = ingresoEntero();
            if(idCategoria == 0) break;

            clear();
            int tipoMovimiento = categoriaManager.getTipoDeMovimientoFromIdCategoria(idCategoria);
            cout << "Anio " << anio << " - Mes " << mes << " - Dia: " << dia << endl;
            cout << "------------------------------------" << endl;
            cout << "Categoria Seleccionada: " << idCategoria << " - " << categoriaManager.getNombreCategoria(idCategoria) << " - " << (tipoMovimiento == 0 ? "Credito" : "Debito") << endl;

            int idMovimiento = aux.generarIdDeMovimiento(mes, dia);
            aux.setIdMovimiento(idMovimiento);

            aux.setIdTipo(tipoMovimiento);
            aux.setIdCategoria(idCategoria);

            float importe;
            cout << "Ingrese el importe del movimiento: $";
            cin >> importe;

            while(importe < 0) {
                cout << "Si el importe suma o resta, lo decide el tipo de movimiento que esta includido en la categoria. Ingrese nuevamente: $";
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

            while(toupper(recurrente) != 'S' && toupper(recurrente) != 'N') {
                cout << "Opcion invalida. Ingrese S para SI o N para NO: ";
                cin >> recurrente;
            }

            aux.setRecurrencia(toupper(recurrente) == 'S');

            cout << "Ingrese el tipo de recurrencia (0-Mensual, 1-Bimestral, 2-Anual): ";
            int tipoDeRecurrencia = ingresoEntero();

            while(tipoDeRecurrencia < 0 || tipoDeRecurrencia > 2) {
                cout << "Tipo de recurrencia invalido. Ingrese 0 para Mensual, 1 para Bimestral o 2 para Anual: ";
                int tipoDeRecurrencia = ingresoEntero();
            }

            aux.setTipoDeRecurrencia(tipoDeRecurrencia);

            char descripcion[100];
            cout << "Ingrese descripcion: ";
            cin.ignore();
            cin.getline(descripcion, 100);
            aux.setDescripcion(descripcion);

            aux.setEstado(true);

            // Guardo el movimiento en el archivo
            if(archivoMovimiento.guardarArchivo(aux)) {
                cout << endl << "Movimiento guardado exitosamente!" << endl << endl;
            } else {
                cout << endl << "Error al guardar el movimiento." << endl << endl;
            }

            cout << "Subtotal del dia: $" << subtotalDia << endl;
            cout << "------------------------------------" << endl;

            cout << "Cargar otro movimiento para este dia? (S/N): ";
            cin >> seguirCargandoMovimientos;

            while(toupper(seguirCargandoMovimientos) != 'S' && toupper(seguirCargandoMovimientos) != 'N') {
                cout << "Opcion invalida. Ingrese S para cargar otro movimiento o N para finalizar: ";
                cin >> seguirCargandoMovimientos;
            }

            clear();
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
    CategoriaManager categoriaManager;

    if(reg.getEstado()) {
        cout << "ID Movimiento: " << reg.getIdMovimiento() << endl;
        cout << "Fecha: " << reg.getFecha().toString() << endl;
        cout << "Categoria: " << reg.getIdCategoria() << " - " << categoriaManager.getNombreCategoria(reg.getIdCategoria()) << endl;
        cout << "Tipo: " << (reg.getIdTipo() == 0 ? "Credito" : "Debito") << endl;
        cout << "Importe: $" << reg.getImporte() << endl;
        cout << "Descripcion: " << reg.getDescripcion() << endl;
        cout << "Recurrente: " << (reg.getRecurrencia() ? "Si" : "No") << endl;
        cout << "Tipo de Recurrencia: " << reg.getTipoDeRecurrencia() << " - " << reg.getNombreDeRecurrencia() << endl;
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
        cout << "----- MOVIMIENTOS -----" << endl;
        cout << "1 - CARGAR MOVIMIENTOS" << endl;
        cout << "2 - MOSTRAR TODOS" << endl;
        cout << "3 - ELIMINAR TODOS" << endl;
        cout << "0 - SALIR" << endl;
        cout << "-----------------------" << endl;

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

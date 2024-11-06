#include "movimientoManager.h"
#include "movimiento.h"
#include "fecha.h"
#include "funcionesGlobales.h"
#include <iostream>
#include "movimientoArchivo.h"
#include "categoriaManager.h"
using namespace std;

void MovimientoManager::cargarMovimiento() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento aux;
    CategoriaManager categoriaManager;

    int mes;
    int anio;
    int cantidadDeDiasEnElMes = 30;

    float subtotalDia = 0;
    float subtotalMes = 0;

    cout << "Anio de los movimientos (0-Salir): ";
    anio = ingresoEntero();

    if(anio == 0) return;

    cout << "Mes de los movimientos (1-12): ";
    mes = ingresoEntero();

    while(mes < 1 || mes > 12) {
        cout << "Mes incorrecto. Por favor entre 1-12: ";
        mes = ingresoEntero();
    }

    /*
    if(mes == 2) {
        if(anio % 4 == 0) cantidadDeDiasEnElMes = 29;
        else cantidadDeDiasEnElMes = 28;
    } else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        cantidadDeDiasEnElMes = 30;
    } else {
        cantidadDeDiasEnElMes = 31;
    }
    */

    for(int dia = 1; dia <= cantidadDeDiasEnElMes; dia++) {
        clear();
        cout << "Anio " << anio << " - Mes " << mes << " - Dia: " << dia << endl;
        cout << "---------------------------------------" << endl;

        subtotalDia = 0;
        char seguirCargandoMovimientos = 'S';

        while(toupper(seguirCargandoMovimientos) == 'S') {
            categoriaManager.mostrarTodasInline();
            cout << endl << "Ingrese el ID de categoria (0-No registrar movimientos, 1-Salir): ";
            int idCategoria = ingresoEntero();

            if(idCategoria == 0) break;
            if(idCategoria == 1) return;

            clear();
            int tipoMovimiento = categoriaManager.getTipoDeMovimientoFromIdCategoria(idCategoria);
            cout << "Anio " << anio << " - Mes " << mes << " - Dia: " << dia << endl;
            cout << "------------------------------------" << endl;
            cout << "Categoria Seleccionada: " << idCategoria << " - " << categoriaManager.getNombreCategoria(idCategoria) << " - de tipo " << (tipoMovimiento == 0 ? "Credito" : "Debito") << endl;

            int idMovimiento = aux.generarIdDeMovimiento(mes, dia);
            aux.setIdMovimiento(idMovimiento);

            aux.setIdTipo(tipoMovimiento);
            aux.setIdCategoria(idCategoria);

            float importe;
            cout << "Ingrese el importe del movimiento: $";
            cin >> importe;

            while(importe < 0) {
                cout << "No se admiten montos negativos, ya que esto se infiere por la categoria. Ingrese nuevamente: $";
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
            int tipoDeRecurrencia = 0;

            if(toupper(recurrente) == 'S') {
                cout << "Ingrese el tipo de recurrencia:\n0-Unico\n1-Mensual\n2-Bimestral\n3-Anual\n";
                int tipoDeRecurrencia = ingresoEntero();

                while(tipoDeRecurrencia < 0 || tipoDeRecurrencia > 2) {
                    cout << "Tipo de recurrencia incorrecto. (0-Unico, 1-Mensual, 2-Bimestral, 3-Anual): ";
                    tipoDeRecurrencia = ingresoEntero();
                }

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

void MovimientoManager::mostrarMovimiento(Movimiento reg) {
    CategoriaManager categoriaManager;

    if(reg.getEstado()) {
        cout << "Importe $" << reg.getImporte() << endl;
        cout << "Movimiento " << reg.getIdMovimiento() << " - " << reg.getFecha().toString() << endl;
        cout << "Categoria " << reg.getIdCategoria() << " - " 
            << categoriaManager.getNombreCategoria(reg.getIdCategoria()) << (reg.getIdTipo() == 0 ? " - Credito" : " - Debito") << endl;
        cout << "Recurrente: " << (reg.getRecurrencia() ? "Si" : "No") 
            << " - Recurrencia: " << reg.getNombreDeRecurrencia() << endl;
        cout << "Descripcion: " << reg.getDescripcion() << endl;
        cout << "-------------------------------------" << endl;
    }
}

void MovimientoManager::mostrarTodosLosMovimientos() {
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
        if(reg.getEstado()) mostrarMovimiento(reg);
    }

    cout << endl << "Fin de la lista de movimientos." << endl;
    cout << "Que desea hacer (0-Salir, 1-Filtrar): " << endl;

    int opcion = ingresoEntero();

    while(opcion != 0 && opcion != 1) {
        cout << "Opcion incorrecta. (0-Salir, 1-Filtrar): ";
        opcion = ingresoEntero();
    }

    if(opcion == 0) {
        clear();
        return;
    } else {
        clear();
        abrirFiltrosDeMovimientos();
    }

    return;
}

void MovimientoManager::abrirFiltrosDeMovimientos() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    CategoriaManager categoriaManager;

    int opcion;
    bool seguirFiltrando = true;
    int cantidad = archivoMovimiento.contarRegistros();

    if(cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        clear();
        return;
    }

    while(seguirFiltrando) {
        int cantidadDeRegistrosFiltrados = 0;

        cout << "---- FILTRAR POR... ---" << endl;
        cout << "1 - TIPO DE MOVIMIENTO" << endl;
        cout << "2 - CATEGORIA" << endl;
        cout << "3 - FECHA" << endl;
        cout << "4 - MOSTRAR TODOS" << endl;
        cout << "0 - SALIR" << endl;
        cout << "------------------------" << endl;

        cout << "INGRESE OPCION: ";
        //cin >> opcion;
        opcion = ingresoEntero();

        clear();

        switch(opcion) {
            case 0:
                seguirFiltrando = false;
                return;
            case 1: {  
                    int tipoMovimiento;
                    cout << "Ingrese el tipo de movimiento:\n0-Credito\n1-Debito\n";
                    tipoMovimiento = ingresoEntero();
                    
                    clear();
                    
                    cout << "----------------------------------------" << endl;
                    bool hayRegistros = false;
                    for(int i = 0; i < cantidad; i++) {
                        Movimiento reg = archivoMovimiento.leer(i);

                        if(reg.getIdTipo() == tipoMovimiento && reg.getEstado()) {
                            hayRegistros = true;
                            mostrarMovimiento(reg);
                        }
                    }
                    if(!hayRegistros) {
                        cout << "No hay movimientos del tipo ";
                        (tipoMovimiento==0 ? cout << "Credito." : cout << "Debito.");
                    }
                    pausa();
                    clear();
                }
                break;
            case 2: {  
                    int idCategoria;
                    cout << "Ingrese el ID de la categoria:" << endl;
                    // TODO: Mostrar categorias existentes al usuario
                    idCategoria = ingresoEntero();
                    cout << "----------------------------------------" << endl;

                    bool hayRegistros = false;
                    for(int i = 0; i < cantidad; i++) {
                        Movimiento reg = archivoMovimiento.leer(i);

                        if(reg.getIdCategoria() == idCategoria && reg.getEstado()) {
                            hayRegistros = true;
                            mostrarMovimiento(reg);
                        }
                    }
                    if(!hayRegistros) {
                        cout << "No hay movimientos para el ID seleccionado." << endl;
                    }
                    pausa();
                    clear();
                }

                break;
            case 3: {  
                    cout << "Ingrese el anio: "; int anio = ingresoEntero();
                    cout << "Ingrese el mes: "; int mes = ingresoEntero();

                    clear();
                    cout << "Movimientos de la fecha " << mes << "/" << anio << endl;
                    cout << "----------------------------------------" << endl;

                    bool hayRegistros = false;
                    for(int i = 0; i < cantidad; i++) {
                        Movimiento reg = archivoMovimiento.leer(i);
                        
                        if(reg.getFecha().getMes() == mes && reg.getFecha().getAnio() == anio && reg.getEstado()) {
                            hayRegistros = true;
                            mostrarMovimiento(reg);
                        }
                    }
                    if(!hayRegistros) {
                        cout << "No hay movimientos para la fecha seleccionada." << endl;
                    }
                    pausa();
                    clear();
                }
                break;
            case 4:
                mostrarTodosLosMovimientos();
                break;
            default:
                cout << "OPCION INCORRECTA" << endl;
                pausa();
                break;
        }
    }
}

void MovimientoManager::eliminarMovimiento() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();

    if(cantidad == 0) {
        cout << "No hay movimientos para eliminar." << endl;
        pausa();
        return;
    }

    int opcion;
    cout << "Elija una opcion:\n1-Ingresar ID\n2-Listar Todos\n0-Salir\n";
    opcion = ingresoEntero();

    if(opcion == 0) return;

    bool existe= false;
    if(opcion == 1){
        clear();
        int id;
        cout << "Ingrese el ID:" << endl;
        id = ingresoEntero();

        for (int i = 0; i < cantidad; i++) {
            Movimiento reg = archivoMovimiento.leer(i);
            if(reg.getIdMovimiento()==id){
                existe = true;
                int confirmar;
                cout << "Esta seguro que desea eliminar el movimiento?\n1-Si\n2-No\n";
                confirmar = ingresoEntero();

                if(confirmar == 1) {
                    reg.setEstado(false);
                    if(archivoMovimiento.modificar(reg, id)){
                        cout << "Movimiento eliminado exitosamente." << endl;
                    } else {cout << "Hubo un error al intentar eliminar el movimiento." << endl;

                        pausa();
                        return;
                    }
                }
            }
        }
    }
    if(!existe) {
        cout << "No se encontro el movimiento con el ID ingresado." << endl;
        pausa();
        return;
    }

    if(opcion == 2) {
        cout << "----------------------------------------" << endl;
        mostrarTodosLosMovimientos();
        return;
    }
}

void MovimientoManager::eliminarTodosLosMovimientos() {
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

void MovimientoManager::mostrarMenuDeMovimientos() {
    int opcion;

    while(true) {
        clear();
        cout << "----- MOVIMIENTOS -----" << endl;
        cout << "1 - NUEVO MOVIMIENTO" << endl;
        cout << "2 - MOSTRAR TODOS" << endl;
        cout << "3 - FILTRAR" << endl;
        cout << "4 - ELIMINAR POR ID" << endl;
        cout << "5 - ELIMINAR TODOS" << endl;
        cout << "0 - SALIR" << endl;
        cout << "-----------------------" << endl;

        cout << "INGRESE OPCION: ";
        //cin >> opcion;
        opcion = ingresoEntero();

        clear();

        switch(opcion) {
            case 1:
                cargarMovimiento();
                break;
            case 2:
                mostrarTodosLosMovimientos();
                break;
            case 3:
                abrirFiltrosDeMovimientos();
                break;
            case 4:
                eliminarMovimiento();
                break;
            case 5:
                eliminarTodosLosMovimientos();
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

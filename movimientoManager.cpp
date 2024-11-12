#include <iostream>
using namespace std;
#include "usuarioManager.h"
#include "movimientoManager.h"
#include "categoriaManager.h"
#include "funcionesGlobales.h"
#include "fecha.h"

void MovimientoManager::cargar() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento aux;
    CategoriaManager categoriaManager;

    float subtotalDia = 0;
    float subtotalMes = 0;

    int anio;
    cout << "Anio de los movimientos: ";
    anio = ingresoEntero();

    int mes;
    cout << "Mes de los movimientos (1-12): ";
    mes = ingresoEntero();

    while(mes < 1 || mes > 12) {
        cout << "Mes incorrecto. Por favor entre 1-12: ";
        mes = ingresoEntero();
    }

    Fecha fecha(1, mes, anio);

    for(int dia = 1; dia <= fecha.getDiasMes(); dia++) {
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
            
            int esFijo;
            cout << "Es un monto fijo? \n 0-No \n 1-Si \n";
            esFijo = ingresoEntero();
            aux.setEsFijo(esFijo);

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

void MovimientoManager::mostrar(Movimiento reg) {
    CategoriaManager categoriaManager;

    if(reg.getEstado()) {
        cout << "Importe $" << reg.getImporte() << endl;
        cout << "ID " << reg.getIdMovimiento() << " - " << reg.getFecha().toString() << endl;
        cout << "Categoria " << reg.getIdCategoria() << " - "
            << categoriaManager.getNombreCategoria(reg.getIdCategoria()) << (reg.getIdTipo() == 0 ? " - Credito" : " - Debito") << endl;
        cout << "Recurrente: " << (reg.getRecurrencia() ? "Si" : "No")
            << " - Recurrencia: " << reg.getNombreDeRecurrencia() << endl;
        cout << "Descripcion: " << reg.getDescripcion() << endl;
        cout << "-------------------------------------" << endl;
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
        if(reg.getEstado()) mostrar(reg);
    }

    cout << "Fin de la lista de movimientos." << endl;
    cout << "-------------------------------------" << endl;
    pausa();
}

void MovimientoManager::menuFiltros() {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    CategoriaManager categoriaManager;

    int cantidad = archivoMovimiento.contarRegistros();

    if(cantidad == 0) {
        cout << "No hay movimientos registrados." << endl;
        pausa();
        clear();
        return;
    }

    int opcion;
    while(true) {
        cout << "---- FILTRAR POR... ---" << endl;
        cout << "1 - TIPO DE MOVIMIENTO" << endl;
        cout << "2 - CATEGORIA" << endl;
        cout << "3 - FECHA" << endl;
        cout << "4 - MOSTRAR TODOS" << endl << endl;

        cout << "0 - SALIR" << endl;
        cout << "------------------------" << endl;
        cout << "INGRESE OPCION: ";
        opcion = ingresoEntero();

        clear();

        switch(opcion) {
            case 1:
                {
                    porTipo();
                    break;
                }
            case 2:
                {
                    porCategoria();
                    break;
                }
            case 3:
                {
                    porFecha();
                    break;
                }
            case 4:
                {
                    mostrarTodos();
                    break;
                }
            case 0:
                {
                    return;
                }
            default:
                {
                    cout << "OPCION INCORRECTA" << endl;
                    pausa();
                    break;
                }
        }
    }
}
void MovimientoManager::porTipo(){
    int tipoMovimiento;
    cout << "Ingrese el tipo de movimiento:\n0-Credito\n1-Debito\n";
    tipoMovimiento = ingresoEntero();

    clear();

    cout << "----------------------------------------" << endl;
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    bool hayRegistros = false;
    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);

        if(reg.getIdTipo() == tipoMovimiento && reg.getEstado()) {
            hayRegistros = true;
            mostrar(reg);
        }
    }
    
    if(!hayRegistros) {
        cout << "No hay movimientos del tipo ";
        (tipoMovimiento==0 ? cout << "Credito." : cout << "Debito.");
    }

    pausa();
    clear();
}
void MovimientoManager::porCategoria(){
    int idCategoria;
    cout << "Ingrese el ID de la categoria:" << endl;
    // TODO: Mostrar categorias existentes al usuario
    idCategoria = ingresoEntero();
    cout << "----------------------------------------" << endl;

    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    bool hayRegistros = false;
    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);

        if(reg.getIdCategoria() == idCategoria && reg.getEstado()) {
            hayRegistros = true;
            mostrar(reg);
        }
    }

    if(!hayRegistros) {
        cout << "No hay movimientos para el ID seleccionado." << endl;
    }

    pausa();
    clear();
}
void MovimientoManager::porFecha(){
    cout << "Ingrese el anio: "; int anio = ingresoEntero();
    cout << "Ingrese el mes: "; int mes = ingresoEntero();

    clear();
    cout << "Movimientos de la fecha " << mes << "/" << anio << endl;
    cout << "----------------------------------------" << endl;

    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    bool hayRegistros = false;

    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);

        if(reg.getFecha().getMes() == mes && reg.getFecha().getAnio() == anio && reg.getEstado()) {
            hayRegistros = true;
            mostrar(reg);
        }
    }

    if(!hayRegistros) {
        cout << "No hay movimientos para la fecha seleccionada." << endl;
    }
    
    pausa();
    clear();
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
            if(reg.getIdMovimiento() == id){
                existe = true;
                int confirmar;
                cout << "Esta seguro que desea eliminar el movimiento?\n1-Si\n2-No\n";
                confirmar = ingresoEntero();

                if(confirmar == 1) {
                    reg.setEstado(false);
                    if(archivoMovimiento.modificar(reg, id)){
                        cout << "Movimiento eliminado exitosamente." << endl;
                    } else {
                        cout << "Hubo un error al intentar eliminar el movimiento." << endl;
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
        mostrarTodos();
        return;
    }
}


void MovimientoManager::menu(const Usuario &user) {
    int opcion;

    while(true) {
        clear();
        cout << "----- MOVIMIENTOS -----" << endl;
        cout << "1 - NUEVO MOVIMIENTO" << endl;
        cout << "2 - MOSTRAR TODOS" << endl;
        cout << "3 - FILTRAR" << endl;
        cout << "4 - ELIMINAR POR ID" << endl << endl;

        cout << "0 - SALIR" << endl;
        cout << "-----------------------" << endl;

        cout << "INGRESE OPCION: ";
        opcion = ingresoEntero();

        clear();

        switch(opcion) {
            case 1:
                {
                    cargar();
                    break;
                }
            case 2:
                {
                    mostrarTodos();
                    break;
                }
            case 3:
                {
                    menuFiltros();
                    break;
                }
            case 4:
                {
                    eliminarMovimiento();
                    break;
                }
            case 0:
                {
                    return;
                }
            default:
                {
                    cout << "OPCION INCORRECTA" << endl;
                }
        }
        clear();
    }
}

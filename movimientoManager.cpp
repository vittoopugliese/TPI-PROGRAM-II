#include <iostream>
using namespace std;
#include "usuarioManager.h"
#include "movimientoManager.h"
#include "categoriaManager.h"
#include "funcionesGlobales.h"
#include "fecha.h"

void MovimientoManager::cargar(const Usuario &user) {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento movimientoAuxiliar;
    CategoriaArchivo categoriaArchivo("categorias.dat");
    CategoriaManager categoriaManager;

    float subtotalDia[31] = {};
    float subtotalMes = 0;

    //Seteamos ID usuario en base al Usuario actual
    movimientoAuxiliar.setIdUsuario(user.getUsuarioID());

    int anio;
    cout << "Anio de los movimientos: ";
    anio = ingresoEntero();

    int mes;
    cout << "Mes de los movimientos (1-12): ";
    mes = ingresoEntero();

    while(mes < 1 || mes > 12) {
        cout << "Mes incorrecto. Por favor, entre 1-12: ";
        mes = ingresoEntero();
    }

    Fecha fecha(1, mes, anio);
    fecha.setMes(mes);
    fecha.setAnio(anio);

    for(int dia = 1; dia <= fecha.getDiasMes(); dia++) {
        clear();

        //subtotalDia = 0;

        int seguirCargando = 1;
        while(seguirCargando == 1){
            //Seteamos ID de movimiento
            movimientoAuxiliar.setIdMovimiento(archivoMovimiento.contarRegistros());

            //Al inicio del ciclo, seteamos fecha
            fecha.setDia(dia);
            movimientoAuxiliar.setFecha(fecha);

            cout << "Dia " << dia << " | Mes " << mes << " | Anio " << anio  << endl;
            cout << "---------------------------------------" << endl;
            categoriaManager.mostrarTodasInline();
            cout << endl << "Ingrese el ID de categoria: ";
            int idCategoria = ingresoEntero();

            int cantReg = categoriaArchivo.contarRegistros();
            Categoria categoriaAuxiliar;

            bool * categoriasActivas = new bool[cantReg];
            if (categoriasActivas == nullptr) exit(-1);

            //Verificamos que ingrese solo categorias activas
            for(int i = 0; i < cantReg; i++){
                categoriaAuxiliar = categoriaArchivo.leerRegistro(i);
                categoriasActivas[i] = categoriaAuxiliar.getEstado();
            }
            while (!categoriasActivas[idCategoria - 1]) {
                cout << "Esta categoria no existe." << endl;
                idCategoria = ingresoEntero();
            }

            delete []categoriasActivas;

            movimientoAuxiliar.setIdCategoria(idCategoria);
            int tipoMovimiento = categoriaManager.getTipoDeMovimientoFromIdCategoria(idCategoria);
            movimientoAuxiliar.setIdTipo(tipoMovimiento);
            clear();

            int esFijo;
            cout << "Es un monto fijo? \n 1-Si \n 2-No \n";
            esFijo = ingresoEntero();
            while(esFijo < 1 || esFijo > 2) {
                cout << "Opcion invalida.";
                idCategoria = ingresoEntero();
            }
            (esFijo==1 ? movimientoAuxiliar.setEsFijo(true) : movimientoAuxiliar.setEsFijo(false) );

            clear();

            cout << "Dia " << dia << " | Mes " << mes << " | Anio " << anio  << endl;
            cout << "------------------------------------" << endl;
            cout << "Categoria: " << categoriaManager.getNombreCategoria(idCategoria) << " | Tipo: " << (tipoMovimiento == 0 ? "Credito" : "Debito") << endl;

            float importe;
            cout << "Ingrese el importe: $";
            cin >> importe; // FALTA VERIFICACION

            bool primero = true;
            while(importe < 0) {
                if (primero) {
                    cout << "No se admiten montos negativos, ya que esto se infiere por la categoria." << endl;
                    primero = false;
                }
                cout << "Ingrese nuevamente: $";
                cin >> importe;
            }

            movimientoAuxiliar.setImporte(importe);

            if(tipoMovimiento == 0) {
                subtotalDia[dia-1] += importe;
                subtotalMes += importe;
            } else {
                subtotalDia[dia-1] -= importe;
                subtotalMes -= importe;
            }

            char descripcion[100];
            cout << "Ingrese descripcion: ";
            cin.ignore();
            cin.getline(descripcion, 100);
            movimientoAuxiliar.setDescripcion(descripcion);

            int respuesta;
            cout << "Es un movimiento recurrente? \n 1-Si \n 2-No \n";
            respuesta = ingresoEntero();
            (respuesta == 1 ? movimientoAuxiliar.setRecurrencia(true) : movimientoAuxiliar.setRecurrencia(false));
            int tipoDeRecurrencia = 0;
            if(respuesta == 1) {
                cout << "Ingrese el tipo de recurrencia:\n1-Unico\n2-Mensual\n3-Bimestral\n4-Anual\n";
                tipoDeRecurrencia = ingresoEntero();

                while(tipoDeRecurrencia < 1 || tipoDeRecurrencia > 4) {
                    cout << "Tipo de recurrencia invalido.";
                    tipoDeRecurrencia = ingresoEntero();
                }
                movimientoAuxiliar.setTipoDeRecurrencia(tipoDeRecurrencia-1);
            }

            movimientoAuxiliar.setEstado(true);

            // Guardo el movimiento en el archivo
            if(archivoMovimiento.guardarArchivo(movimientoAuxiliar)) {
                cout << "------------------------------------" << endl;
                cout << "Movimiento guardado exitosamente!" << endl;
                cout << "------------------------------------" << endl;
                mostrar(movimientoAuxiliar);
            } else {
                cout << endl << "Error al guardar el movimiento." << endl << endl;
            }

            cout << "Subtotal dia " << dia << ": $" << subtotalDia[dia-1] << endl;
            cout << "------------------------------------" << endl;

            cout << "Cargar otro movimiento para este dia? \n 1-Si \n 2-No \n";
            seguirCargando = ingresoEntero();
            while (!(seguirCargando == 1 || seguirCargando == 2)) {
                cout << "Opcion invalida.";
                seguirCargando == ingresoEntero();
            }

            if (seguirCargando == 2) {
                cout << "------------------------------------" << endl;
                cout << "Desea seguir cargando movimientos para este mes? \n 1-Si \n 2-No \n";
                seguirCargando = ingresoEntero();
                while (seguirCargando < 1 || seguirCargando > 2) {
                    cout << "Opcion invalida.";
                    seguirCargando = ingresoEntero();
                }
                if (seguirCargando == 2) {
                    clear();
                    for (int i = 0; i < 30; i++) {
                        if (subtotalDia[i]>0) {
                            cout << "Total dia " << i+1 << ": $" << subtotalDia[i] << endl;
                        }
                    }
                cout << "------------------------------------" << endl;
                cout << "Total mes " << fecha.getNombreDelMes(mes) << ": $" << subtotalMes << endl;
                pausa();
                return; // Detiene la ejecución de la funcion, y deja de cargar movimientos
                }
                break; // Rompe el while, y pasa al día siguiente
            }
            clear();
        }
        pausa();
    }
    clear();
    for (int i = 0; i < 30; i++) {
        if (subtotalDia[i]>0) {
            cout << "Total dia " << i+1 << ": $" << subtotalDia[i] << endl;
        }
    }
    cout << "Total del mes " << fecha.getNombreDelMes(mes) << ": $" << subtotalMes << endl;
    pausa();
}

void MovimientoManager::mostrar(Movimiento reg) {
    CategoriaManager categoriaManager;

    if(reg.getEstado()) {
        cout << "Importe $" << reg.getImporte() << endl;
        cout << "ID " << reg.getIdMovimiento() << " - " << reg.getFecha().toString() << endl;
        cout << "Categoria: " << categoriaManager.getNombreCategoria(reg.getIdCategoria()) << endl;
        cout << "Tipo " << (reg.getIdTipo() == 0 ? " - Credito" : " - Debito") << endl;
        cout << "Recurrente: ";
        if (reg.getRecurrencia()) {
            cout << "Si" << endl;
            cout << "Recurrencia: " << reg.getNombreDeRecurrencia() << endl;
        } else {
            cout << "No" << endl;
        }
        cout << "Descripcion: " << reg.getDescripcion() << endl;
        cout << "-------------------------------------" << endl;
    }
}

void MovimientoManager::mostrarTodos(const Usuario &user) {
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
        if (reg.getIdUsuario() == user.getUsuarioID()) {
            if(reg.getEstado()) mostrar(reg);
        }
    }

    cout << "Fin de la lista de movimientos." << endl;
    cout << "-------------------------------------" << endl;
    pausa();
}

void MovimientoManager::menuFiltros(const Usuario &user) {
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
                    porTipo(user);
                    break;
                }
            case 2:
                {
                    porCategoria(user);
                    break;
                }
            case 3:
                {
                    porFecha(user);
                    break;
                }
            case 4:
                {
                    mostrarTodos(user);
                    clear();
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
void MovimientoManager::porTipo(const Usuario &user){
    int tipoMovimiento;
    cout << "Ingrese el tipo de movimiento:\n1-Credito\n2-Debito\n";
    tipoMovimiento = ingresoEntero();
    while(tipoMovimiento < 1 || tipoMovimiento > 2) {
        cout << "Opcion invalida.";
        tipoMovimiento = ingresoEntero();
    }
    tipoMovimiento--; //Resto 1 asi el codigo es correcto

    clear();

    cout << "----------------------------------------" << endl;
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    int cantidad = archivoMovimiento.contarRegistros();
    bool hayRegistros = false;
    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);
        if (reg.getIdUsuario() == user.getUsuarioID()) {
            if(reg.getIdTipo() == tipoMovimiento && reg.getEstado()) {
                hayRegistros = true;
                mostrar(reg);
            }
        }
    }

    if(!hayRegistros) {
        cout << "No hay movimientos del tipo ";
        (tipoMovimiento==0 ? cout << "Credito." : cout << "Debito.");
        cout << endl;
    }

    pausa();
    clear();
}

void MovimientoManager::porCategoria(const Usuario &user){
    CategoriaManager categoriaManager;
    int idCategoria;
    cout << "Ingrese el ID de la categoria:" << endl;
    categoriaManager.mostrarTodasInline();
    idCategoria = ingresoEntero();
    clear();
    cout << "Filtrando por: " << categoriaManager.getNombreCategoria(idCategoria) << endl;
    cout << "----------------------------------------" << endl;

    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento reg;
    int cantidad = archivoMovimiento.contarRegistros();

    bool hayRegistros = false;
    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);
        if (reg.getIdUsuario() == user.getUsuarioID()) {
            if(reg.getIdCategoria() == idCategoria && reg.getEstado()) {
                hayRegistros = true;
                mostrar(reg);
            }
        }
    }

    if(!hayRegistros) {
        cout << "No hay movimientos de esta categoria." << endl;
    }

    pausa();
    clear();
}

void MovimientoManager::porFecha(const Usuario &user){
    cout << "Ingrese el anio: "; int anio = ingresoEntero();
    cout << "Ingrese el mes: "; int mes = ingresoEntero();

    clear();
    cout << "Movimientos de la fecha " << mes << "/" << anio << endl;
    cout << "----------------------------------------" << endl;

    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento reg;
    int cantidad = archivoMovimiento.contarRegistros();

    bool hayRegistros = false;

    for(int i = 0; i < cantidad; i++) {
        Movimiento reg = archivoMovimiento.leer(i);
        if (reg.getIdUsuario() == user.getUsuarioID()) {
            if(reg.getFecha().getMes() == mes && reg.getFecha().getAnio() == anio && reg.getEstado()) {
                hayRegistros = true;
                mostrar(reg);
            }
        }
    }

    if(!hayRegistros) {
        cout << "No hay movimientos para la fecha seleccionada." << endl;
    }

    pausa();
    clear();
}

void MovimientoManager::eliminarMovimiento(const Usuario &user) {
    MovimientoArchivo archivoMovimiento("movimientos.dat");
    Movimiento reg;
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

    bool existe = false;
    if(opcion == 1){
        clear();
        int id;
        cout << "Ingrese el ID:" << endl;
        id = ingresoEntero();

        for (int i = 0; i < cantidad; i++) {
            reg = archivoMovimiento.leer(i);
            //Si coincide ID de movimiento y usuario, eliminar
            if(reg.getIdMovimiento() == id && reg.getIdUsuario() == user.getUsuarioID()){
                reg = archivoMovimiento.leer(i);
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
        mostrarTodos(user);
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
                    cargar(user);
                    break;
                }
            case 2:
                {
                    mostrarTodos(user);
                    break;
                }
            case 3:
                {
                    menuFiltros(user);
                    break;
                }
            case 4:
                {
                    eliminarMovimiento(user);
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

#include <iostream>
using namespace std;
#include "categoriaManager.h"

void CategoriaManager::menu(const Usuario &user) {
    int opcion;
    while(true){
        clear();
        cout << "----- CATEGORIAS -----" << endl;
        cout << "[1] NUEVA CATEGORIA" << endl;
        cout << "[2] ELIMINAR EXISTENTE" << endl;
        cout << "[3] MOSTRAR TODAS" << endl;
        cout << "[4] EDITAR EXISTENTE" << endl;
        cout << endl;
        cout << "[0] SALIR" << endl;
        cout << "----------------------" << endl;
        cout << "INGRESE UNA OPCION: ";
        //cin >> opcion;
        opcion = ingresoEntero();
        clear();
        switch (opcion){
            case 1:
                {
                    Categoria aux = cargar();
                    _archivo.guardarArchivo(aux);
                    break;
                }
            case 2:
                baja();
                break;
            case 3:
                mostrarTodos();
                break;
            case 4:
                modificar();
                break;
            case 0:
                return;
            default:
                cout << "OPCION INCORRECTA" << endl;
        }
        clear();
    }
    return;
}

Categoria CategoriaManager::cargar() {
    Categoria aux;
    CategoriaArchivo archiCategorias("categorias.dat");
    int tipoMovimiento, idCategoria;
    char nombre[20];
    char descripcion[50];

    idCategoria = archiCategorias.contarRegistros()+1;
    aux.setIdCategoria(idCategoria);

    cout << "Tipo de movimiento:" << endl; // 0 o 1
    cout << "[0] Credito \n [1] Debito \n ";
    cin >> tipoMovimiento;
    //valdiarIngreso.entero(tipoMovimiento); -- Verificaria que se ingresen solo enteros, ademas de solo 0 o 1.
    aux.setTipoMovimiento(tipoMovimiento);

    cout << "Nombre: ";
    cargarCadena(nombre, 19, true);
    aux.setNombre(nombre);

    cout << "Descripcion: ";
    cargarCadena(descripcion, 49);
    aux.setDescripcion(descripcion);

    aux.setEstado(true);

    return aux;
}

void CategoriaManager::mostrar(Categoria categoria) {
    if (categoria.getEstado() == true){
        cout << "Tipo: ";
        cout << (categoria.getTipoMovimiento()==0 ? "Credito (+)" : "Debito (-)") << endl;
        cout << "ID: " << categoria.getIdCategoria() << endl;
        cout << "Nombre: " << categoria.getNombre() << endl;
        cout << "Descripcion: " << categoria.getDescripcion() << endl;
        cout << endl;
        cout << "-------------------------------" << endl;
    }

}

int CategoriaManager::contarCategoriasActivas() {
    int cantReg = _archivo.contarRegistros();
    Categoria aux;
    int cantidadActivos = 0;

    for(int i = 0; i< cantReg; i++){
        if (aux.getEstado() == true) {
            cantidadActivos++;
        }
    }
    return cantidadActivos;
}

void CategoriaManager::mostrarTodos() {
    int cantReg = _archivo.contarRegistros();
    Categoria aux;

    for(int i = 0; i<cantReg; i++){
        mostrar(_archivo.leerRegistro(i));
    }
    pausa();
}

void CategoriaManager::buscarPorIdCategoria(){
    Categoria aux;
    int id;

    cout << "Ingrese el ID (0 para salir): ";
    id = ingresoEntero();
    cout << endl;

    if (id==0) return;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0){
        aux = _archivo.leerRegistro(posicion);
        if (aux.getIdCategoria() == 0){
            cout << "El registro no pudo ser listado" << endl;
            return;
        }
        mostrar(aux);
    }else{
        cout << "No existe el ID ingresado" << endl;
    }
}

void CategoriaManager::baja() {
    Categoria categoria;
    int id;
    cout << "Ingrese el ID: ";
    cin >> id;
    cout << endl;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0 && categoria.getIdCategoria() != 0){
        Categoria aux = _archivo.leerRegistro(posicion);
        mostrar(aux);
    }else{
        cout << "No existe el ID ingresado." << endl;
        return;
    }

    int respuesta;
    cout << "Estas seguro que deseas eliminar la categoria?" << endl;
    respuesta = ingresoEntero();
    while (respuesta < 1 || respuesta > 2) {
        cout << "Opcion invalida.";
        respuesta = ingresoEntero();
    }

    if (respuesta == 1){
        categoria.setEstado(false);
        if (_archivo.modificar(categoria, posicion)){
            cout << "Categoria eliminada con exito!" << endl;
            pausa();
        } else {
            cout << "No se pudo borrar la categoria!" << endl;
            pausa();
        }
    }
}

void CategoriaManager::modificar() {
    Categoria aux;
    int id;
    cout << "Ingrese el ID: ";
    cin >> id;
    cout << endl;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0){
        Categoria aux = _archivo.leerRegistro(posicion);
        mostrar(aux);
    }else{
        cout << "No existe el ID ingresado" << endl;
        return;
    }
    int respuesta;
    cout << "Esta seguro que quiere modificar el registro?" << endl;
    cout << "[1] Si \n [2] No\n" << endl;
    cin >> respuesta;
    cout << endl;

    int tipoMovimiento;
    char nombre[20], descripcion[50];

    if (respuesta == 1){
        cout << "Ingrese nuevamente los campos a modificar..." << endl;

        cout << "Tipo de moviminento:" << endl; // 0 o 1
        cout << "[0] Credito \n [1] Debito \n ";
        cin >> tipoMovimiento;
        aux.setTipoMovimiento(tipoMovimiento);

        cout << "Nombre: ";
        cargarCadena(nombre, 19); // Salta directamente a descripcion???
        aux.setNombre(nombre);

        cout << "Descripcion: ";
        cargarCadena(descripcion, 49);
        aux.setDescripcion(descripcion);

        if (_archivo.modificar(aux, posicion)){
            cout << "Registro modificado con exito!" << endl;
        }else{
            cout << "No se pudo modificar el registro!" << endl;
        }
    }
}

int CategoriaManager::getTipoDeMovimientoFromIdCategoria(int idCategoria) {
    Categoria aux;
    int posicion = _archivo.buscar(idCategoria);

    if (posicion >= 0){
        aux = _archivo.leerRegistro(posicion);
        return aux.getTipoMovimiento();
    }

    return -1;
}

void CategoriaManager::mostrarTodasInline() {
    int cantReg = _archivo.contarRegistros();
    Categoria aux;

    cout << "Lista de categorias disponibles:" << endl << endl;

    for(int i = 0; i < cantReg; i++){
        aux = _archivo.leerRegistro(i);
        if(aux.getEstado()) cout << aux.getIdCategoria() << " - " << aux.getNombre() << endl;
    }
}

string CategoriaManager::getNombreCategoria(int idCategoria) {
    Categoria aux;
    int posicion = _archivo.buscar(idCategoria);

    if (posicion >= 0){
        aux = _archivo.leerRegistro(posicion);
        return aux.getNombre();
    }

    return "No se encontro la categoria";
}

#include <iostream>
using namespace std;
#include "categoriaManager.h"
#include "funcionesGlobales.h"

Categoria CategoriaManager::Cargar(){
    Categoria aux;
    CategoriaArchivo archiCategorias("categorias.dat");
    int tipoMovimiento, idCategoria;
    char nombre[20];
    char descripcion[50];

    idCategoria = archiCategorias.contarRegistros()+1;
    aux.setIdCategoria(idCategoria);

    cout << "Tipo de movimiento:" << endl; // 0 o 1
    cout << "(0-Credito | 1-Debito) ";
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

void CategoriaManager::Mostrar(Categoria categoria){
    if (categoria.getEstado() || true){
        cout << "Tipo: ";
        cout << (categoria.getTipoMovimiento()==0 ? "Credito (+)" : "Debito (-)") << endl;
        cout << "ID: " << categoria.getIdCategoria() << endl;
        cout << "Nombre: " << categoria.getNombre() << endl;
        cout << "Descripcion: " << categoria.getDescripcion() << endl;
        cout << endl;
        cout << "-------------------------------" << endl;
    }

}


void CategoriaManager::mostrarTodos(){
    int cantReg = _archivo.contarRegistros();
    Categoria aux;

    for(int i = 0; i<cantReg; i++){
        Mostrar(_archivo.leerRegistro(i));
    }
    pausa();
}

void CategoriaManager::buscarPorIdCategoria(){
    Categoria aux;
    int id;

    cout << "Ingrese el ID: ";
    cin >> id;
    cout << endl;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0){
        aux = _archivo.leerRegistro(posicion);
        if (aux.getIdCategoria() == 0){
            cout << "ESTE REGISTRO NO PUEDE SER LISTADO" << endl;
            return;
        }
        Mostrar(aux);
    }else{
        cout << "NO EXISTE EL NUMERO DE DNI INGRESADO" << endl;
    }
}

void CategoriaManager::baja(){
    Categoria categoria;
    int id;
    cout << "Ingrese el ID: ";
    cin >> id;
    cout << endl;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0 && categoria.getIdCategoria() != 0){
        Categoria aux = _archivo.leerRegistro(posicion);
        Mostrar(aux);
        pausa();
    }else{
        cout << "NO EXISTE EL ID INGRESADO" << endl;
        return;
    }

    int respuesta;
    cout << "ESTA SEGURO QUE QUIERE ELIMINAR EL REGISTRO?" << endl;
    cout << "(1 - SI | 0 - NO)" << endl;
    cin >> respuesta;
    cout << endl;

    if (respuesta == 1){
        categoria.setEstado(false);
        if (_archivo.modificar(categoria, posicion)){
            cout << "REGISTRO ELIMINADO CON EXITO!" << endl;
            pausa();
        }else{
            cout << "NO SE PUDO ELIMINAR EL REGISTRO!" << endl;
            pausa();
        }
    }
}

void CategoriaManager::modificar(){
    Categoria aux;
    int id;
    cout << "INGRESE EL ID: ";
    cin >> id;
    cout << endl;

    int posicion = _archivo.buscar(id);
    if (posicion >= 0){
        Categoria aux = _archivo.leerRegistro(posicion);
        Mostrar(aux);
    }else{
        cout << "NO EXISTE EL ID INGRESADO" << endl;
        return;
    }
    int respuesta;
    cout << "ESTA SEGURO QUE QUIERE MODIFICAR EL REGISTRO?" << endl;
    cout << "(1 - SI | 0 - NO)" << endl;
    cin >> respuesta;
    cout << endl;

    int tipoMovimiento;
    char nombre[20], descripcion[50];

    if (respuesta == 1){
        cout << "INGRESE NUEVAMENTE LOS CAMPOS A MODIFICAR..." << endl;

        cout << "Tipo de moviminento:" << endl; // 0 o 1
        cout << "(0-Credito | 1-Debito) ";
        cin >> tipoMovimiento;
        aux.setTipoMovimiento(tipoMovimiento);

        cout << "Nombre: ";
        cargarCadena(nombre, 19); // Salta directamente a descripcion???
        aux.setNombre(nombre);

        cout << "Descripcion: ";
        cargarCadena(descripcion, 49);
        aux.setDescripcion(descripcion);

        if (_archivo.modificar(aux, posicion)){
            cout << "REGISTRO MODIFICADO CON EXITO!" << endl;
        }else{
            cout << "NO SE PUDO MODIFICAR EL REGISTRO!" << endl;
        }
    }
}

int CategoriaManager::getTipoDeMovimientoFromIdCategoria(int idCategoria){
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

string CategoriaManager::getNombreCategoria(int idCategoria){
    Categoria aux;
    int posicion = _archivo.buscar(idCategoria);

    if (posicion >= 0){
        aux = _archivo.leerRegistro(posicion);
        return aux.getNombre();
    }

    return "NO SE ENCONTRO LA CATEGORIA";
}

void CategoriaManager::menu(const Usuario &user)
 {
  int opcion;
    while(true){
        clear();
        cout << "----- CATEGORIAS -----" << endl;
        cout << "1 - CREAR NUEVA" << endl;
        cout << "2 - ELIMINAR EXISTENTE" << endl;
        cout << "3 - MOSTRAR TODAS" << endl;
        cout << "4 - EDITAR EXISTENTE" << endl << endl;
        cout << "0 - SALIR" << endl;
        cout << "----------------------" << endl;
        cout << "INGRESE UNA OPCION: ";
        //cin >> opcion;
        opcion = ingresoEntero();
        clear();
        switch (opcion){
            case 1:
                {
                    Categoria aux = Cargar();
                    _archivo.guardarArchivo(aux);
                    break;
                }
            case 2:
                {
                    baja();
                    break;
                }
            case 3:
                {
                    mostrarTodos();
                    break;
                }
            case 4:
                {
                    modificar();
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
    return;
}

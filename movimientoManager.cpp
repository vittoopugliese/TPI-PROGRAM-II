#include "movimientoManager.h"
#include <iostream>
using namespace std;
class MovimientoManager {
private:
    MovimientoArchivo archivo;
    
public:
    MovimientoManager(): archivo("movimientos.dat") {}
    
    void cargar() {
        int mes;
        RegistroDiario registrosMes[30];
        
        do {
            cout << "INGRESE EL MES (1-12): ";
            cin >> mes;
        } while (mes < 1 || mes > 12);
        
        if (archivo.leerRegistros(mes, registrosMes)) {
            // EVALUAR SI YA EXISTEN
            // cout << "YA EXISTEN REGISTROS DE ESTE MES. ";
        }
        
        cout << "INGRESE LOS GASTOS DEL MES " << mes << "";
        for (int dia = 0; dia < 30; dia++) {
            cout << "DIA " << (dia + 1) << ":";
            
            cout << "CATEGORIA: ";
            cin >> registrosMes[dia].categoria;

            string cat = toupper(registrosMes[dia].categoria);
            bool condition = cat != "GASTOS VARIOS" && cat != "PAGO ALQUILER" && cat != "SUPERMERCADO" && cat != "TRANSPORTE" && cat != "SERVICIOS" && cat != "INGRESOS VARIOS" && cat != "SALARIO";
            
            while (condition) {
                cout << "CATEGORIA INVALIDA. INGRESE NUEVAMENTE: ";
                cin >> registrosMes[dia].categoria;
            }
            
            cout << "MONTO: $";
            cin >> registrosMes[dia].monto;
            
            while (registrosMes[dia].monto < 0) {
                cout << "MONTO INVALIDO. DEBE SER MAYOR O IGUAL A 0: $";
                cin >> registrosMes[dia].monto;
            }
        }
        
        if (archivo.guardarRegistros(mes, registrosMes)) {
            cout << "REGISTROS GUARDADOS EXITOSAMENTE!";
        } else {
            cout << "ERROR AL GUARDAR REGISTROS.";
        }
    }
};
void MovimientoManager::mostrar(){
    cout << "MOSTRANDO MOVIMIENTO" << endl;
}

void MovimientoManager::mostrarTodos(){
    cout << "MOSTRANDO TODOS LOS MOVIMIENTOS" << endl;
}

void MovimientoManager::menuEmpleado(){
    int opcionSeleccionada;
    bool continuar = true;

    while (continuar){
        system("cls");

        cout << "=== MENU DE EMPLEADO ===" << endl;
        cout << "1 - CARGAR MOVIMIENTO" << endl;
        cout << "2 - MOSTRAR MOVIMIENTO" << endl;
        cout << "3 - MOSTRAR TODOS" << endl;
        cout << "0 - VOLVER" << endl;
        cout << "======================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcionSeleccionada;

        switch (opcionSeleccionada){
        case 1:
            cargar();
            break;
        case 2:
            mostrar();
            break;
        case 3:
            mostrarTodos();
            break;
        case 0:
            continuar = false;
            cout << "VOLVIENDO AL MENU PRINCIPAL" << endl;
            break;
        default:
            cout << "OPCION NO VALIDA, INTENTE NUEVAMENTE." << endl;
            break;
        }

        if (continuar){
            cout << endl << "PRESIONE ENTER PARA CONTINUAR...";
            system("pause");
        }
    }
}
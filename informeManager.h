#ifndef INFORME_MANAGER_H
#define INFORME_MANAGER_H
using namespace std;

class InformeManager{
public:
    void menu(const Usuario &user);
    void mostrarBalanceMensual();
    void mostrarIngresosPorCategoria();
    void mostrarEgresosPorCategoria();
};

#endif

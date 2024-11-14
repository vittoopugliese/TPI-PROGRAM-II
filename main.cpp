#include <iostream>
#include <iomanip>
#include "usuarioManager.h"
using namespace std;

#include "app.h"

int main() {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    App menu;
    menu.menuLogin();
    return 0;
}

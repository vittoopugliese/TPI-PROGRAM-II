#include <iostream>
#include <string>
#include "menu.h"
#include "rlutil.h"

Menu::Menu(const std::string tittle) {
    _tittle = tittle;
    _itemsCount = 0;
    _items = nullptr;
    _selectedItem = 0;
}

bool Menu::addItem(const std::string itemName) {
    std::string * newItems = new std::string[_itemsCount + 1];

    if (newItems == nullptr) {
        exit(-1);
    }

    if (_itemsCount > 0) {
        for (int i = 0; i < _itemsCount; i++) {
            newItems[i] = _items[i];
        }
    }

    newItems[_itemsCount] = itemName;

    delete[] _items;

    _items = newItems;

    _itemsCount++;
}

std::string * Menu::getMenuItems() const {
    return _items;
}

int Menu::getItemsCount() const {
    return _itemsCount;
}

std::string Menu::getTitle() const {
    return _tittle;
}

int Menu::getMaxCharsOfOptions() const {
    int maxChars = getTitle().size();
    int actualChars = 0;
    for (int i = 0; i < getItemsCount(); i++) {
        actualChars = getMenuItems()[i].size();
        if (actualChars > maxChars) {
            maxChars = actualChars;
        }
    }

    return maxChars;
}

void Menu::showMenu() {
    rlutil::hidecursor();
    int maxChars = getMaxCharsOfOptions();
    int InicioEjeDeSimetriaX = (rlutil::tcols() / 2) - (maxChars / 2);
    rlutil::locate(InicioEjeDeSimetriaX - 1, 1);
    for (int i = 0; i < maxChars + 2; i++) {
        std::cout << char(254);
    }
    rlutil::locate((rlutil::tcols() / 2) - (getTitle().size() / 2), 2);
    std::cout << getTitle() << std::endl;
    rlutil::locate(InicioEjeDeSimetriaX - 1, 3);
    for (int i = 0; i < maxChars + 2; i++) {
        std::cout << char(254);
    }
    rlutil::locate(InicioEjeDeSimetriaX - 2, 2);
    std::cout << char(219);
    rlutil::locate(InicioEjeDeSimetriaX + maxChars + 1, 2);
    std::cout << char(219);

    int aux = 1;
    int icon = 220;

    for (int i = 0; i < 2; i++) {
        rlutil::locate(InicioEjeDeSimetriaX - 2, aux);
        std::cout << char(icon);
        rlutil::locate(InicioEjeDeSimetriaX + maxChars + 1, aux);
        std::cout << char(icon);
        aux = 3;
        icon = 223;
    }

    for (int i = 0; i < getItemsCount(); i++) {
        rlutil::locate((rlutil::tcols() / 2) - (getMenuItems()[i].size() / 2), 6 + i);
        if (i == _selectedItem) {
            rlutil::saveDefaultColor();
            //rlutil::setColor(rlutil::MAGENTA);
            rlutil::setBackgroundColor(rlutil::BLUE);
        }
        std::cout << getMenuItems()[i] << std::endl;
        rlutil::resetColor();
    }
}

int Menu::getSelectedItem() const {
    return _selectedItem;
}

void Menu::traverseMenu(int key) {
    if (key == rlutil::KEY_UP) {
        if (_selectedItem - 1 < 0) {
            return;
        }
        _selectedItem--;
    } else if (key == rlutil::KEY_DOWN) {
        if (_selectedItem + 1 >= _itemsCount) {
            return;
        }
        _selectedItem++;
    }
}

int Menu::getSelection() {
    int key = rlutil::getkey();
    while (key != rlutil::KEY_ENTER) {
        traverseMenu(key);

        system("cls");
        Menu::showMenu();

        key = rlutil::getkey();
    }
    return _selectedItem + 1;
}

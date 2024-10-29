#pragma once

class Menu {
    public:
        // Constructor:
        Menu(const std::string tittle);

        // Métodos:
        bool addItem(const std::string itemName);
        void showMenu();
        int getSelection();

        // Destructor:
        ~Menu() {
            delete[] _items;
        }
    private:
        // Atributos:
        std::string _tittle;
        std::string * _items = nullptr;
        int _itemsCount;
        int _selectedItem;

        // Métodos:
        int getMaxCharsOfOptions() const;
        std::string * getMenuItems() const;
        int getItemsCount() const;
        std::string getTitle() const;
        int getSelectedItem() const;
        void traverseMenu(int key);
};

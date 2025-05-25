#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <optional>
#include <cmath>
using namespace std;

struct Entry {
    int key;
    string value;
    bool isDeleted;

    Entry(int k, string v) : key(k), value(v), isDeleted(false) {}
};

class HashTable {
private:
    vector<optional<Entry>> table;
    int size;
    int collisions;
    const int c1 = 1; 
    const int c2 = 1; 

    int hPrime(int key) const {
        return key % size;
    }

    int hash(int key, int i) const {
        return (hPrime(key) + c1 * i + c2 * i * i) % size;
    }

    int findSlot(int key, bool forInsert = false) {
        int index;
        for (int i = 0; i < size; ++i) {
            index = hash(key, i);
            if (!table[index].has_value()) {
                return forInsert ? index : -1;
            }

            if (!table[index]->isDeleted && table[index]->key == key) {
                return index;
            }

            if (forInsert && table[index].has_value() && !table[index]->isDeleted) {
                collisions++;
            }
        }
        return -1;
    }

    double loadFactor() const {
        int count = 0;
        for (const auto& entry : table) {
            if (entry.has_value() && !entry->isDeleted) {
                count++;
            }
        }
        return static_cast<double>(count) / size;
    }

    void resize() {
        int oldSize = size;
        size *= 2;
        vector<optional<Entry>> oldTable = table;
        table.clear();
        table.resize(size);
        collisions = 0;

        for (const auto& entry : oldTable) {
            if (entry.has_value() && !entry->isDeleted) {
                int newIndex = findSlot(entry->key, true);
                table[newIndex] = Entry(entry->key, entry->value);
            }
        }

        cout << "Таблица увеличена вдвое. Новый размер: " << size << endl;
    }

public:
    HashTable(int tableSize = 16)
        : size(tableSize), collisions(0) {
        table.resize(size);
    }

    void insert(int key, const string& value) {
        if (loadFactor() >= 0.75) {
            resize();
        }

        int index = findSlot(key);
        if (index != -1) {
            table[index]->value = value;
            return;
        }

        int insertIndex = findSlot(key, true);
        table[insertIndex] = Entry(key, value);
    }

    optional<string> find(int key) {
        int index = findSlot(key);
        if (index != -1) {
            return table[index]->value;
        }
        return nullopt;
    }

    void remove(int key) {
        int index = findSlot(key);
        if (index != -1) {
            table[index]->isDeleted = true;
        }
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << "[ " << i << " ] ";
            if (!table[i].has_value()) {
                cout << "empty";
            }
            else if (table[i]->isDeleted) {
                cout << "deleted";
            }
            else {
                cout << table[i]->key << " => " << table[i]->value;
            }
            cout << endl;
        }
    }

    int getCollisions() const {
        return collisions;
    }

    void resetCollisions() {
        collisions = 0;
    }
};

void menu() {
    cout << "\n===== МЕНЮ =====\n";
    cout << "(1) Добавить\n";
    cout << "(2) Поиск по ключу\n";
    cout << "(3) Удалить по ключу\n";
    cout << "(4) Вывести таблицу\n";
    cout << "(5) Выход\n";
    cout << "Выбор: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    HashTable ht(16);

    while (true) {
        menu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int key;
            string value;
            cout << "Введите целочисленный ключ: ";
            cin >> key;
            cout << "Введите значение: ";
            cin.ignore();
            getline(cin, value);
            ht.insert(key, value);
            cout << "Успешно добавлено. Коллизий: " << ht.getCollisions() << endl;
            break;
        }
        case 2: {
            int key;
            cout << "Введите ключ: ";
            cin >> key;
            auto result = ht.find(key);
            if (result) {
                cout << "Найдено: " << *result << endl;
            }
            else {
                cout << "Ключ не найден.\n";
            }
            break;
        }
        case 3: {
            int key;
            cout << "Введите ключ: ";
            cin >> key;
            ht.remove(key);
            cout << "Удалено.\n";
            break;
        }
        case 4: {
            ht.print();
            cout << "Всего коллизий: " << ht.getCollisions() << endl;
            break;
        }
        case 5: {
            cout << "Выход.\n";
            return 0;
        }
        default:
            cout << "Некорректный выбор. Попробуйте снова.\n";
            break;
        }

        system("pause");
        system("cls");
    }
}
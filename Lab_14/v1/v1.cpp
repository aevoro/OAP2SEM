#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <chrono>

using namespace std;

const int TABLE_SIZE = 16;
const int PRIME = 1000003; 

class HashNode {
public:
    int year;
    string product;
    HashNode* next;

    HashNode(int y, const string& p) : year(y), product(p), next(nullptr) {}
};

class HashTable {
private:
    vector<HashNode*> table;
    int a, b, p, size;

    int hashFunc(int key) {
        return ((a * key + b) % p) % size;
    }

public:
    HashTable(int s = TABLE_SIZE, int prime = PRIME) : size(s), p(prime) {
        table.resize(size, nullptr);
        srand(time(0));
        a = 1 + rand() % (p - 1); 
        b = rand() % p;           
    }

    ~HashTable() {
        for (auto& head : table) {
            while (head) {
                HashNode* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }

    void insert(int year, const string& product) {
        int index = hashFunc(year);
        HashNode* newNode = new HashNode(year, product);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int search(int year, const string& product) {
        int index = hashFunc(year);
        HashNode* cur = table[index];
        while (cur) {
            if (cur->year == year)
            cur = cur->next;
        }
        return 1;
    }

    bool remove(int year, const string& product) {
        int index = hashFunc(year);
        HashNode* cur = table[index];
        HashNode* prev = nullptr;

        while (cur) {
            if (cur->year == year) {
                if (prev) prev->next = cur->next;
                else table[index] = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void print() {
        cout << "\nХеш-таблица:\n";
        for (int i = 0; i < size; ++i) {
            HashNode* cur = table[i];
            if (cur) {
                cout << "[" << i << "]: ";
                while (cur) {
                    cout << "(" << cur->product << ", " << cur->year << ")";
                    cur = cur->next;
                }
                cout << endl;
            }
        }
    }
};

void menu() {
    cout << "\n(1) Добавить товар\n"
        << "(2) Показать таблицу\n"
        << "(3) Удалить товар\n"
        << "(4) Поиск товара\n"
        << "(5) Выход\n"
        << "> Выбор: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");

    HashTable ht;
    int choice;

    while (true) {
        menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name;
            int year;
            cout << "Введите название товара: ";
            getline(cin, name);
            cout << "Введите год выпуска: ";
            cin >> year;
            ht.insert(year, name);
            cout << "Товар добавлен.\n";
            break;
        }
        case 2:
            ht.print();
            break;
        case 3: {
            string name;
            int year;
           
            cout << "Введите год выпуска: ";
            cin >> year;
            if (ht.remove(year, name))
                cout << "Товар удалён.\n";
            else
                cout << "Товар не найден.\n";
            break;
        }
        case 4: {
            string name;
            int year;
            cout << "Введите год выпуска: ";
            cin >> year;

            auto start = chrono::high_resolution_clock::now();
            int result = ht.search(year, name);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> time = end - start;

            if (result)
                cout << "Найден товар: " << result << "\n";
            else
                cout << "Товар не найден.\n";

            cout << "Время поиска: " << time.count() << " мс\n";
            break;
        }
        case 5:
            cout << "Выход...\n";
            return 0;
        default:
            cout << "Некорректный ввод. Повторите.\n";
            break;
        }

        system("pause");
        system("cls");
    }

    return 0;
}

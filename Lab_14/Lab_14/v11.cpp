#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

const int MAXSIZE = 16;

class hashNode {
public:
    int key;          
    string city;      
    hashNode* next;

    hashNode(int k, const string& c) : key(k), city(c), next(nullptr) {}
};

class hashTable {
private:
    vector<hashNode*> table;
    int size;

    
    int hashFunc(const string& city) {
        int hashVal = 0;
        for (char ch : city) {
            hashVal ^= static_cast<unsigned char>(ch);
        }
        return hashVal % size;
    }

public:
    hashTable(int sz = MAXSIZE) : size(sz) {
        table.resize(size, nullptr);
    }

    ~hashTable() {
        for (int i = 0; i < size; ++i) {
            hashNode* cur = table[i];
            while (cur != nullptr) {
                hashNode* tmp = cur;
                cur = cur->next;
                delete tmp;
            }
        }
    }

    void insert(int key, const string& city) {
        int index = hashFunc(city);
        hashNode* cur = table[index];

        while (cur != nullptr) {
            if (cur->key == key && cur->city == city) {
                cur->city = city; 
                return;
            }
            cur = cur->next;
        }

        hashNode* newNode = new hashNode(key, city);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int search(int key, const string& city) {
        int index = hashFunc(city);
        hashNode* cur = table[index];
        while (cur != nullptr) {
            if (cur->key == key) {
                break;
            }
            cur = cur->next;
        }
        return 1;
    }

    bool remove(int key, const string& city) {
        int index = hashFunc(city);
        hashNode* cur = table[index];
        hashNode* prev = nullptr;

        while (cur) {
            if (cur->key == key) {
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
        cout << "\n���-�������:\n";
        for (int i = 0; i < size; ++i) {
            hashNode* cur = table[i];
            if (cur) {
                cout << "[" << i << "]: ";
                while (cur != nullptr) {
                    cout << "(" << cur->city << ", " << cur->key << ")";
                    cur = cur->next;
                }
                cout << endl;
            }
        }
        cout << endl;
    }
};

void menu() {
    cout << "\n(1) ���� ������\n"
        << "(2) ����� ���� �������\n"
        << "(3) ������� �����\n"
        << "(4) ����� ������\n"
        << "(5) �����\n"
        << "> �����: ";
}


int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    hashTable ht;
    int sw;

    while (true) {
        menu();
        cin >> sw;
        cin.ignore();

        switch (sw) {
        case 1: {
            string city;
            int population;
            cout << "������� �������� ������: ";
            getline(cin, city);
            cout << "������� ����������� ���������: ";
            cin >> population;
            ht.insert(population, city);
            cout << "����� ��������.\n";
            break;
        }
        case 2:
            ht.print();
            break;
        case 3: {
            string city;
            int population;
            cout << "������� ����������� ���������: ";
            cin >> population;
            if (ht.remove(population, city)) {
                cout << "����� �����.\n";
            }
            else {
                cout << "����� �� ������.\n";
            }
            break;
        }
        case 4: {
            string city;
            int population;
            
            cout << "������� ����������� ���������: ";
            cin >> population;

            auto start = chrono::high_resolution_clock::now();
            bool result = ht.search(population, city);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> duration = end - start;

            if (!result) {
                cout << "������ �����: " << result << "\n";
            }
            else {
                cout << "����� �� ������.\n";
            }
            cout << "����� ������: " << duration.count() << " ��\n";
            break;
        }
        case 5:
            cout << "�����...\n";
            return 0;
        default:
            cout << "�������� ����. ���������� �����.\n";
            break;
        }
        system("pause");
        system("cls");
    }

    return 0;
}

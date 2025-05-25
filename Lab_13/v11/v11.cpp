#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <optional>

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

    int hash(int key) const {
        return key % size;
    }

    int findSlot(int key, bool forInsert = false) const {
        int index = hash(key);
        int startIndex = index;

        while (true) {
            if (!table[index].has_value()) {
                return forInsert ? index : -1;
            }

            if (!table[index]->isDeleted && table[index]->key == key) {
                return index;
            }

            index = (index + 1) % size;
            if (index == startIndex) break;
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

        for (const auto& entry : oldTable) {
            if (entry.has_value() && !entry->isDeleted) {
                int newIndex = findSlot(entry->key, true);
                table[newIndex] = Entry(entry->key, entry->value);
            }
        }

        cout << "������� ��������� �����. ����� ������: " << size << endl;
    }

public:
    HashTable(int tableSize = 16) : size(tableSize) {
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

    optional<string> find(int key) const {
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
};

void menu() {
    cout << "\n===== ���� =====\n";
    cout << "(1) ��������\n";
    cout << "(2) ����� �� �����\n";
    cout << "(3) ������� �� �����\n";
    cout << "(4) ������� �������\n";
    cout << "(5) ��������������\n";
    cout << "(6) �����\n";
    cout << "�����: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    HashTable ht;

    while (true) {
        menu();
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int key;
            string value;
            cout << "������� ������������� ����: ";
            cin >> key;
            cout << "������� ��������: ";
            cin.ignore();
            getline(cin, value);
            ht.insert(key, value);
            cout << "������� ���������.\n";
            break;
        }
        case 2: {
            int key;
            cout << "������� ����: ";
            cin >> key;
            auto result = ht.find(key);
            if (result) {
                cout << "�������: " << *result << endl;
            }
            else {
                cout << "���� �� ������.\n";
            }
            break;
        }
        case 3: {
            int key;
            cout << "������� ����: ";
            cin >> key;
            ht.remove(key);
            cout << "������� (���� �������).\n";
            break;
        }
        case 4: {
            ht.print();
            break;
        }
        case 5: {
            for (int i = 1; i <= 13; i++) {
                ht.insert(i, " " + to_string(i));
            }
            break;
        }
        case 6: {
            cout << "�����.\n";
            return 0;
        }
        default:
            cout << "������������ �����. ���������� �����.\n";
            break;
        }

        system("pause");
        system("cls");
    }
}

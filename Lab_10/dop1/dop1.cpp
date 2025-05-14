#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

void generateNumbers(int A, int pos, int* arr, ofstream& file) {

    if (pos == A) {
        if (arr[0] != 0 || A == 1) {
            for (int i = 0; i < A; ++i)
                file << arr[i];
            file << endl;
        }
        return;
    }

    for (int digit = 0; digit <= A; ++digit) {
        arr[pos] = digit;
        generateNumbers(A, pos + 1, arr, file);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int A;
    cout << "Введите цифру A (от 1 до 9): ";
    cin >> A;

    if (A < 1 || A > 9) {
        cout << "Некорректный ввод. A должно быть от 1 до 9." << endl;
        return 1;
    }

    int* arr = new int[A]; 
    ofstream file("file.txt");

    generateNumbers(A, 0, arr, file);

    file.close();
    delete[] arr;

    cout << "Числа записаны в файл" << endl;
    return 0;
}

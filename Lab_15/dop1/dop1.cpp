#include <iostream>
#include <random>

using namespace std;

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "RU");
    int size = 0;
    cout << "Введите размер массива: ";
    cin >> size;
    int* A = new int[size];
    int* B = new int[size];
    int* C = new int[size];
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 20;
        cout << A[i] << " ";
    }
    cout << endl;
    int max = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (A[i] > A[j]) {
                max++;
            }
        }
        B[i] = max;
        max = 0;
    }
    cout << "Счетчик: ";
    for (int i = 0; i < size; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == B[j]) {
                cout << A[j] << " ";
            }
        }
    }

    cout << endl;
    delete[] A;
    delete[] B;
    delete[] C;
}
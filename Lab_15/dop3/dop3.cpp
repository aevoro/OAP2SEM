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
    cout << "Массив: ";
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 20;
        cout << A[i] << " ";
    }
    cout << endl;
    for (int i = 1; i < size; i++) {
        int key = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }

    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    delete[] A;

}
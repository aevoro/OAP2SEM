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
    int index = 0;
    
    int minIndex = 0;
    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++) {
        int min = 9999;
        for (index; index < size; index++) {
            if (min > A[index]) {
                min = A[index];
                minIndex = index;
            }
        }
        swap(A[i], A[minIndex]);
        index=i+1;
        cout << A[i] << " ";
    }
    cout << endl;
    delete[] A;

}
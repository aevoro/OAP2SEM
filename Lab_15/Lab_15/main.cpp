#include <iostream>
#include <random>

using namespace std;

void menu() {
    cout << "(1) Сортировка слиянием\n"
        "(2) Сортировка Хоара\n"
        "(3) Массив А\n"
        "(4) Массив B\n"
        "(5) Массив C\n"
        "(6) Выход\n"
        "Выбор: ";
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void sortMerge(int arrC[], int sizeC) {
    if (sizeC <= 0) return;
    mergeSort(arrC, 0, sizeC - 1);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < sizeC; i++) {
        cout << arrC[i] << " ";
    }
    cout << endl;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void sortHoar(int arrC[], int sizeC) {
    if (sizeC <= 0) return;
    quickSort(arrC, 0, sizeC - 1);
    cout << "Отсортированный массив: ";
    for (int i = 0; i < sizeC; i++) {
        cout << arrC[i] << " ";
    }
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    int* arrA = nullptr;
    int* arrB = nullptr;
    int* arrC = nullptr;
    int sizeA = 0, sizeB = 0, sizeC = 0;
    int sw;
    while (true) {
        system("pause");
        system("cls");
        menu();
        cin >> sw;
        switch (sw) {
        case 1: {
            if (arrC == nullptr) {
                cout << "Сначала создайте массив C" << endl;
                break;
            }
            sortMerge(arrC, sizeC);
            cout << endl;
            break;
        }
        case 2: {
            if (arrC == nullptr) {
                cout << "Сначала создайте массив C" << endl;
                break;
            }
            sortHoar(arrC, sizeC);
            cout << endl;
            break;
        }
        case 3: {
            cout << "Введите размер массива A: ";
            cin >> sizeA;
            delete[] arrA;
            arrA = new int[sizeA];
            for (int i = 0; i < sizeA; i++) {
                arrA[i] = rand() % 10;
            }
            cout << "Массив А сгенерирован: ";
            for (int i = 0; i < sizeA; i++) {
                cout << arrA[i] << " ";
            }
            cout << endl;
            break;
        }
        case 4: {
            cout << "Введите размер массива B: ";
            cin >> sizeB;
            delete[] arrB;
            arrB = new int[sizeB];
            for (int i = 0; i < sizeB; i++) {
                arrB[i] = rand() % 10;
            }
            cout << "Массив B сгенерирован: ";
            for (int i = 0; i < sizeB; i++) {
                cout << arrB[i] << " ";
            }
            cout << endl;
            break;
        }
        case 5: {
            if (arrA == nullptr || arrB == nullptr) {
                cout << "Сначала создайте массивы А и B!" << endl;
                break;
            }

            int oddA = 0, evenB = 0;
            for (int i = 0; i < sizeA; i++) {
                if (arrA[i] % 2 != 0) oddA++;
            }
            for (int i = 0; i < sizeB; i++) {
                if (arrB[i] % 2 == 0) evenB++;
            }
            delete[] arrC;
            sizeC = oddA + evenB;
            arrC = new int[sizeC];

            int index = 0;

            for (int i = 0; i < sizeA; i++) {
                if (arrA[i] % 2 != 0) {
                    arrC[index++] = arrA[i];
                }
            }

            for (int i = 0; i < sizeB; i++) {
                if (arrB[i] % 2 == 0) {
                    arrC[index++] = arrB[i];
                }
            }
            cout << "Массив C создан: ";
            for (int i = 0; i < sizeC; i++) {
                cout << arrC[i] << " ";
            }
            cout << endl;
            break;
        }
        case 6: {
            delete[] arrA;
            delete[] arrB;
            delete[] arrC;
            return 0;

        }
        default: {
            cout << "Неверный выбор\n";
            break;
        }
        }
    }

}
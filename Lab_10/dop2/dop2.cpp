#include <iostream>
using namespace std;
const int MAX = 10;
int A[MAX][MAX];
int group[MAX];
int n;
int minCross = 1000000;

int countCrossEdges() {
    int count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (A[i][j] == 1 && group[i] != group[j])
                count++;
    return count;
}

void divide(int idx) {
    if (idx == n) {
        int c0 = 0;
        for (int i = 0; i < n; ++i)
            if (group[i] == 0)
                c0++;
        int c1 = n - c0;
        if (c0 == 0 || c1 == 0)
            return;
        int crosses = countCrossEdges();
        if (crosses < minCross)
            minCross = crosses;
        return;
    }
    group[idx] = 0;
    divide(idx + 1);
    group[idx] = 1;
    divide(idx + 1);
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Введите количество стран (не более " << MAX << "): ";
    cin >> n;
    if (n > MAX || n < 1) {
        cout << "Ошибка: число стран должно быть от 1 до " << MAX << endl;
        return 1;
    }
    cout << "Введите матрицу смежности " << n << "x" << n << ":\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    divide(0);
    cout << "Минимальное число границ между блоками: " << minCross << endl;
    return 0;
}

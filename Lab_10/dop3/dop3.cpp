#include <iostream>

using namespace std;

const int N = 5;
int a[N];

void perm(int idx) {
    if (idx == N) {
        for (int i = 0; i < N; ++i)
            cout << a[i] << (i + 1 < N ? ' ' : '\n');
        return;
    }
    for (int i = idx; i < N; ++i) {
        int tmp = a[idx]; a[idx] = a[i]; a[i] = tmp;
        perm(idx + 1);
        tmp = a[idx]; a[idx] = a[i]; a[i] = tmp;
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    cout << "¬ведите 5 чисел: ";
    for (int i = 0; i < N; ++i)
        cin >> a[i];
    perm(0);
    return 0;
}

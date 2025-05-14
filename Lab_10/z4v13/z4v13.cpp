#include <iostream>

using namespace std;

int dnx(int n, int x) {
    if (x == 1) {
        return 1; 
    }
    else {
        return dnx(n, x - 1) + ((n % x == 0) ? 1 : 0);
    }
}

int dn(int n) {
    return dnx(n, n);
}

int main() {
    setlocale(LC_ALL, "RU");
    int number;
    cout << "������� �����: ";
    cin >> number;

    if (number <= 0) {
        cout << "����� ������ ���� ����������� (������������� �����)." << std::endl;
        return 1;
    }

    int divisorsCount = dn(number);
    cout << "���������� ������������� ��������� ����� " << number
        << " �����: " << divisorsCount << endl;

    return 0;
}
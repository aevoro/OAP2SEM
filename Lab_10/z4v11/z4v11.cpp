#include <iostream>
#include <Windows.h>

using namespace std;

double Sn(int n, int x) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 2 * x;
	}
	else {
		return (2.0 * n / (n - 1)) * Sn(n - 1, x) + ((n - 1.0) / (2.0 * n)) * Sn(n - 2, x);
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "¬ведите n: ";
	cin >> n;
	int x;
	cout << "¬ведите x: ";
	cin >> x;
	double result = Sn(n, x);
	cout << "S" << n << "(" << x << ") = " << result << endl;
	return 0;
}
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	ofstream File("File.txt");
	string line;

	File.is_open();
	cout << "Введите строку: ";
	getline(cin, line);
	File << line;
	cout << "Данные записаны в файл." << endl;
	File.close();

	ifstream checkFile("File.txt");
	string checkLine;
	int i = 0;
	string num = { "0123456789" };

	getline(checkFile, checkLine);
	cout << "Нечетные числа строки: ";
	for (int i = 0; i < size(checkLine); i++) {
		for (int j = 0; j < size(num); j++) {
			if (checkLine[i] == num[j]) {
				if (num[j] % 2 != 0) {
					cout << num[j] << ", ";
				}
			}
		}
	}
}
#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct sanatorium{
	string nameSanatorium;
	string locate;
	string treatment;
	int quantityPack;
};

bool compareSanatorium(const sanatorium& a, const sanatorium& b) {
	if (a.treatment == b.treatment) {
		return a.nameSanatorium < b.nameSanatorium;
	}
	else {
		return a.treatment < b.treatment;
	}
}

void printInfo(sanatorium data[], int size) {
	sort(data, data + size, compareSanatorium);
	int a = 1;
	string currentTreatment = "";
	for (int i = 0; i < size; i++) {
		a++;
		currentTreatment = data[i].treatment;
		for (int j = 0; j < size; j++) {
			
			if (currentTreatment == data[j].treatment && a!=3) {
					cout << data[j].nameSanatorium << "\t" << data[j].locate << "\t" << data[j].quantityPack << endl;
			}
		}
		if (a != 3) {
			cout << data[i].treatment << endl;
			cout << "------------------------------------" << endl;
		}
	}
}

int checkInfo(sanatorium data[], int size) {
	int sw;

	while (true) {
		cout << "1 - свободные путевки, 2 - расположение, 3 - лечебный профиль, 4 - выход: ";
		cin >> sw;
		bool yessn = false;
		switch (sw) {
		case 1: {
			for (int i = 0; i < size; i++) {
				if (data[i].quantityPack > 1) {
					cout << data[i].nameSanatorium << "\t" << data[i].locate << "\t" << data[i].quantityPack <<"\t" << data[i].treatment << endl;
					yessn = true;
				}
			}
			if (!yessn) {
				cout << "Нет санаториев по подходящим параметрам" << endl;
			}
			break;
		}

		case 2: {
			string curLocate;
			bool yessn = false;
			cout << "Введите предпочитаемое место расположения санатория(Минск, Гомель, Гродно, Могилев): ";
			cin >> curLocate;
			for (int i = 0; i < size; i++) {
				if (curLocate == data[i].locate) {
					cout << data[i].nameSanatorium << "\t" << data[i].locate << "\t" << data[i].quantityPack << "\t" << data[i].treatment << endl;
					yessn = true;
				}
			}
			if (!yessn) {
				cout << "Нет санаториев по подходящим параметрам" << endl;
			}
			break;
		}

		case 3: {
			string curTreatment;
			bool yessn = false;
			cout << "Введите лечебный профиль(Сердечный, Кожный, Пищеварение): ";
			cin >> curTreatment;
			for (int i = 0; i < size; i++) {
				if (curTreatment == data[i].treatment) {
					cout << data[i].nameSanatorium << "\t" << data[i].locate << "\t" << data[i].quantityPack << "\t" << data[i].treatment << endl;
					yessn = true;
				}
			}
			if (!yessn) {
				cout << "Нет санаториев по подходящим параметрам" << endl;
			}
			break;
		}

		case 4: {
			return 0;
		}

		}
	}
}

int main() {
 	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int sw;
	sanatorium info[4] = {
		{"Сан1", "Минск", "Сердечный", 0},
		{"Сан2", "Гродно", "Кожный", 10},
		{"Сан4", "Могилев", "Кожный", 32},
		{"Сан3", "Гомель", "Пищеварение", 14},
	};
	while (true) {
		cout << "1 - информация о всех санаториях, 2 - поиск информации по параметрам, 3 - выход: ";
		cin >> sw;
		switch (sw) {
		case 1: {
			printInfo(info, 4);
			break;
		}

		case 2: {
			checkInfo(info, 4);
			break;
		}

		case 3: {
			return 0;
		}
		}
	}
	
}
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void write(string&line) {
	ofstream File("File.txt");
	File << line << endl;
	File.close();
	cout << "Данные успешно записаны в файл." << endl;
}
string read(string&line, string &content) {
	ifstream File("File.txt");
	File.is_open();
	File.close();
	return content;
	cout << "Данные успешно прочитаны из файла" << endl;
}	
int main() {
	setlocale(LC_ALL, "Ru");
	string line;
	int krsk = 0, kvsk = 0, fgsk = 0;
	cout << "Введите строку символов состоящую из цифр и скобок" << endl;
	getline(cin, line);
	write(line);
	string content = read(line, content);
	int roundBrack = 0; 
	int squareBrack = 0; 
	int curlyBrack = 0; 

	for (char ch : line) {
		if (ch == '(' || ch == ')') {
			roundBrack++;
		}
		else if (ch == '[' || ch == ']') {
			squareBrack++;
		}
		else if (ch == '{' || ch == '}') {
			curlyBrack++;
		}
	}
	cout << "Количество круглых скобок (): " << roundBrack << endl;
	cout << "Количество квадратных скобок []: " << squareBrack << endl;
	cout << "Количество фигурных скобок {}: " << curlyBrack << endl;
}
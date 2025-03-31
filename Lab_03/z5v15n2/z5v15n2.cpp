
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    
    string str;
    cout << "Введите строку: ";
    getline(cin, str);

    ofstream outFile("File.txt");
    if (!outFile.is_open()) {
        cout << "Не удалось открыть файл для записи." << endl;
        return 1;
    }
    outFile << str;
    outFile.close();

    ifstream inFile("File.txt");
    if (!inFile.is_open()) {
        cout << "Не удалось открыть файл для чтения." << endl;
        return 1;
    }

    string fileContent;
    getline(inFile, fileContent);
    inFile.close();

    istringstream iss(fileContent);
    string word;

    cout << "Слова, содержащие букву 'х':" << endl;
    while (iss >> word) {
        if (word.find('x') != string::npos || word.find('X') != string::npos) {
            cout << word << endl;
        }
    }

    return 0;
}
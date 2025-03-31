#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
void writeToFile(const string& filename, const string& firstline, const string& secondline) {
    ofstream file(filename);
    file.is_open();
        file << firstline << endl << secondline;
        file.close();
        cout << "Данные успешно записаны в файл" << endl;
}
void readFromFile(const string& filename, string& firstline, string& secondline) {
    ifstream file(filename);
    file.is_open();
        getline(file, firstline);
        getline(file, secondline);
        file.close();
        cout << "Данные успешно прочитаны из файла"<< endl;
}
string findShortestWord(const string& line) {
    stringstream ss(line);
    string word, shortestWord;
    size_t minLength = SIZE_MAX;
    while (ss >> word) {
        if (word.length() < minLength) {
            minLength = word.length();
            shortestWord = word;
        }
    }
    return shortestWord;
}
string findLongestWord(const string& line) {
    stringstream ss(line);
    string word, longestWord;
    size_t maxLength = 0;

    while (ss >> word) {
        if (word.length() > maxLength) {
            maxLength = word.length();
            longestWord = word;
        }
    }
    return longestWord;
}
int countVowels(const string& word) {
    const string vowels = "aouieyAOUIEY";
    int count = 0;
    for (char ch : word) {
        if (vowels.find(ch) != string::npos) {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "RU");
    string firstline, secondline;
    cout << "Введите первую строку: ";
    getline(cin, firstline);
    cout << "Введите вторую строку: ";
    getline(cin, secondline);
    writeToFile("File.txt", firstline, secondline);
    string fileFirstline, fileSecondline;
    readFromFile("File.txt", fileFirstline, fileSecondline);
    string shortestWord = findShortestWord(fileFirstline);
    cout << "Самое короткое слово в первой строке: " << shortestWord << endl;
    string longestWord = findLongestWord(fileSecondline);
    cout << "Самое длинное слово во второй строке: " << longestWord << endl;
    int vowelsInShortest = countVowels(shortestWord);
    cout << "Количество гласных букв в самом коротком слове первой строки: " << vowelsInShortest << endl;
    int vowelsInLongest = countVowels(longestWord);
    cout << "Количество гласных букв в самом длинном слове второй строки: " << vowelsInLongest << endl;
    ofstream file("File.txt");
    if (file.is_open()) {
        file << endl << "Самое короткое слово первой строки: " << shortestWord << endl;
        file << "Самое длинное слово второй строки: " << longestWord << endl;
        file << "Количество гласных букв в самом коротком слове первой строки: " << vowelsInShortest << endl;
        file << "Количество гласных букв в самом длинном слове второй строки: " << vowelsInLongest << endl;
        file.close();
        cout << "Результаты успешно записаны в файл." << endl;
    }
    else {
        cout << "Ошибка открытия файла для записи результатов." << endl;
    }

    return 0;
}
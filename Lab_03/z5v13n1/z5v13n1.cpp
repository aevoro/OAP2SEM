#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int countVowels(const string& word) {
    int count = 0;
    for (char ch : word) {
        if (tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' ||
            tolower(ch) == 'o' || tolower(ch) == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    setlocale(LC_ALL, "RU");
    ifstream FileA("FileA.txt");
    ofstream FileB("FileB.txt");
    string line;
    while (getline(FileA, line)) {
        string word;
        int wordCount = 0;
        int maxVowels = 0;
        int wordIndex = -1;
        int currentIndex = 0;

        for (size_t i = 0; i <= line.length(); ++i) {
            if (line[i] == ' ' || line[i] == '\0') {
                wordCount++;
                if (!word.empty()) {
                    int vowels = countVowels(word);
                    if (vowels > maxVowels) {
                        maxVowels = vowels;
                        wordIndex = currentIndex;
                    }
                    currentIndex++;
                    word.clear();
                }
            }
            else {
                word += line[i];
            }
        }
        if (wordCount > 2) {
            FileB << line << endl;
            if (wordIndex != -1) {
                int currentWord = 0;
                string resultWord;
                for (size_t i = 0; i <= line.length(); ++i) {
                    if (line[i] == ' ' || line[i] == '\0') {
                        if (currentWord == wordIndex) {
                            break;
                        }
                        currentWord++;
                        resultWord.clear();
                    }
                    else {
                        resultWord += line[i];
                    }
                }
                cout << "Слово с наибольшим количеством гласных: " << resultWord  << " Номер слова: " << wordIndex + 1 << endl;
            }
        }
    }

    FileA.close();
    FileB.close();

    return 0;
}
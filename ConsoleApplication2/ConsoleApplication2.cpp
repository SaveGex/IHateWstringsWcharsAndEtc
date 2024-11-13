#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <map>
#include <sstream>
#include <ctype.h>
#include <locale>
#include <unicode/unistr.h>

using namespace std;
namespace fs = filesystem;


std::wstring string_to_wstring(const std::string& str) {
	// Конвертуємо std::string в ICU UnicodeString (UTF-8)
	icu::UnicodeString unicode_str = icu::UnicodeString::fromUTF8(str);

	// Створюємо std::wstring, в яку будемо записувати символи
	std::wstring wstr;

	// Пройдемо по кожному символу в unicode_str і додамо його до wstr
	for (int i = 0; i < unicode_str.length(); i++) {
		// Перетворюємо кожен символ в wchar_t
		UChar c = unicode_str.charAt(i);
		wstr.push_back(static_cast<wchar_t>(c)); // Конвертуємо UChar в wchar_t
	}

	return wstr;
}
int main(){
	SetConsoleOutputCP(1251);
	vector<string> array_of_words;//keys_for_dict

	map<string, int> word_count;
	
	fs::path path_to_essay = "essay of reflection.txt";

	stringstream ssfile;
	ifstream file_read(path_to_essay);

	string word;

	if (!file_read.is_open()) {
		return 1;
	}

	ssfile << file_read.rdbuf();
	file_read.close();

	while (ssfile >> word) {

		int index{ 0 };
		wstring Wword = string_to_wstring(word);

		while(index < word.size()) {

			if (!isalpha(Wword[index], locale("uk_UA.UTF-8"))) {
				word.erase(index);
			}
			else {
				index++;
			}

		}
		array_of_words.push_back(word); 
		cout << word + ' ';
	}
	ssfile.clear();
	ssfile.seekg(0);

	while (ssfile >> word) {
		word_count[word]++;
	}

	for (const auto& pair : word_count) {
		cout << "Word: " << pair.first << " : " << pair.second << endl;
	}



	return 0;
}
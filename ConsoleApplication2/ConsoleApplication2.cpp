#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <map>
#include <sstream>
#include <ctype.h>

using namespace std;
namespace fs = filesystem;

bool checking_symbol_of_punctual(char sym) {
	if (sym == ' ' || sym == ',' || sym == '.' || sym == ';' || sym == ':' || sym == '[' || sym == ']' || sym == '{' || sym == '}' || sym == '`' || sym == '~' || sym == '@' || sym == '#' || sym == '#' || sym == '#' || sym == '$' || sym == '%' || sym == '^' || sym == '&' || sym == '*' || sym == '(' || sym == ')' || sym == '\\' || sym == '|' || sym == '/' || sym == '=' || sym == '-' || sym == '+' || sym == '<' || sym == '>' || sym == '!' || sym == '?') {
		return true;
	}
	return false;
}

void prepearing_word(string& word) {
	int index{ 0 };
	for (int i = 0; i < word.size(); i++) {
		if (checking_symbol_of_punctual(word[i])) {
			word.erase(index);
			continue;
		}
		index++;
	}
}

int main(){
	SetConsoleOutputCP(1251);

	ofstream for_write("datas.txt");

	string choice{ 0 };
	cout << "You want write youself text? 1(yes) 2(no): \n";
	cin >> choice;
	map<string, int> datas;

	if (choice != "1") {
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
			cout << word + ' ';
		}
		ssfile.clear();
		ssfile.seekg(0);

		while (ssfile >> word) {
			prepearing_word(word);
			word_count[word]++;
		}

		string most_used;
		int count_of_used{ 0 };

		for (const auto& pair : word_count) {
			if (count_of_used <= pair.second) {
				count_of_used = pair.second;
				most_used = pair.first;
			}
			cout << "Word: " << pair.first << " : " << pair.second << endl;
		}
		cout << "Most used word is: " << most_used << " times: " << count_of_used;
		datas[most_used] = count_of_used;
	}
	else {
		stringstream ssfile;
		map<string, int> word_count;
		string sentence;

		cout << "Write your sentence here: \n";
		cin.ignore();
		getline(cin, sentence);
		
		cout << endl;

		string buffer{};
		for (int i = 0; i < sentence.size(); i++) {
			if (checking_symbol_of_punctual(tolower(sentence[i])) && !buffer.empty()) {
				for (int j = 0; j < buffer.size(); j++) {
					buffer[j] = tolower(buffer[j]);
				}
				word_count[buffer]++;
				buffer.clear();
				continue;
			}
			if (checking_symbol_of_punctual(sentence[i])) {
				continue;
			}
			buffer += sentence[i];
		}
		if (!buffer.empty()) {
			word_count[buffer]++;
		}


		string most_used;
		int count_of_used{ 0 };

		cout << endl;

		for (const auto& pair : word_count) {
			if (count_of_used <= pair.second) {
				count_of_used = pair.second;
				most_used = pair.first;
			}
			cout << "Word: " << pair.first << " : " << pair.second << endl;
		}
		cout << "Most used word is: " << most_used << " times: " << count_of_used;

		datas[most_used] = count_of_used;

	}

	for (const auto& pair : datas) {
		for_write << "Key: " + pair.first + " Value: " + to_string(pair.second) + '\n';
	}



	return 0;
}
#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <map>
#include <sstream>
#include <ctype.h>


using namespace std;
namespace fs = filesystem;



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
		//DOESN'T WORKING WITH UKRAINIAN LANGUAGE :(
		//while(index < word.size()) {

		//	if (!isalpha(word[index], locale("uk_UA.UTF-8"))) {
		//		word.erase(index);
		//	}
		//	else {
		//		index++;
		//	}

		//}
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
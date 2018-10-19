/*
Author: Travis Banken

Hangman

This program allows the user to play a game of hangman against the computer AI. The AI is developed from the stats found in the Stats directory of the project, specifically the results.txt file.
*/

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>

using namespace std;

unordered_map<char, char[26]> buildModel();
vector<string> split(string);

int main(int argc, char *argv[]) {
    cout << "=======================" << endl;
    cout << "  Welcome to Hangman! " << endl;
    cout << "=======================" << endl << endl;

    string word;
    cout << "Enter word to be guessed (no longer than 10 letters): ";
    cin >> word;

    cout << "Word: " << word << endl;
    cout << "Length: " << word.length() << endl;

    buildModel();
} 

/*
Builds the model to be used for the computer AI in the game of Hangman. It will read from the results.txt file in the Stats directory and map the a letter to an array organized by likelyhood of directly following that letter.

Params: None
Return: unordered_map which maps a letter to an array of all letters, organized         by the likelyhood of that letter directly following the key.
*/
unordered_map<char, char[26]> buildModel() {
    ifstream infile;
    string filename ("./Stats/results.txt");
    infile.open(filename);

    // check for file not found error
    if (!infile.good()) {
        cerr << "ERROR: Can not find " << filename << endl;
        exit(1);
    }

    // read the file
    unordered_map<char, char[26]>  modelMap;
    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }

    infile.close();

    return modelMap;
}

/*
Splits a string on spaces.

Params: str - String to split
Return: vector containing words created from spliting on space
*/
vector<string> split(string str) {
    vector<string> splitStr;
    string buffer;
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == ' ') {
            splitStr.push_back(buffer);
            buffer = "";
        }
        else {
            string c(1, str.at(i));
            buffer = buffer + c;
        }
    }
    return splitStr;
}
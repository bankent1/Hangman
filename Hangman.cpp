/*
Author: Travis Banken

Hangman

This program allows the user to play a game of hangman against the computer AI. 
The AI is developed from the stats found in the Stats directory of the project, 
specifically the results.txt file.
*/

#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>

using namespace std;

unordered_map<char, vector<char>> buildModel();
vector<string> split(string);
vector<char> getLettFreq();
vector<char> initGuessState(int);
char getNextLett(vector<char>);
vector<char> processGuess(string, vector<char>, char, int*);
void printGuessState(vector<char>);
bool wordGuessed(vector<char>, string);

int main(int argc, char *argv[]) {
    cout << "=======================" << endl;
    cout << "  Welcome to Hangman! " << endl;
    cout << "=======================" << endl << endl;

    string word;
    cout << "Enter word to be guessed (no longer than 10 letters): ";
    cin >> word;

    cout << "Word: " << word << endl;
    cout << "Length: " << word.length() << endl;

    unordered_map<char, vector<char>> modelMap = buildModel();
    vector<char> lettFreq;
    lettFreq = getLettFreq();

    vector<char> guessState = initGuessState(word.length());
    int lives = 10;
    char guess;
    while (lives > 0) {
        cout << "Lives = " << lives << endl;
        
        char c = getNextLett(guessState);
        if (c == '_') {
            guess = lettFreq.at(0);
            cout << "Guessing " << lettFreq.at(0) << endl;
            lettFreq.erase(lettFreq.begin() + 0);
        }
        else {
            guess = modelMap[c].at(0);
            cout << "Guessing " << modelMap[c].at(0) << endl;
            modelMap[c].erase(modelMap[c].begin() + 0);
        }
        printGuessState(guessState);
        guessState = processGuess(word, guessState, guess, &lives);
        if (wordGuessed(guessState, word)) {
            cout << "WORD GUESSED, YOU LOSE!" << endl;
            return 0;
        }
        cout << endl;
    }

    // return -1 if computer lost
    cout << "WORD NOT GUESSED, YOU WIN!" << endl;
    return -1;

    // for (auto it = modelMap.begin(); it != modelMap.end(); it++) {
    //     cout << it->first << ": [";
    //     for (int i = 0; i < it->second.size(); i++) {
    //         cout << it->second.at(i) << ", ";
    //     }
    //     cout << "]" << endl;
    // }
} 

/*
Builds the model to be used for the computer AI in the game of Hangman. It will 
read from the results.txt file in the Stats directory and map the a letter to an
array organized by likelyhood of directly following that letter.

Params: None
Return: unordered_map which maps a letter to an array of all letters, organized 
        by the likelyhood of that letter directly following the key.
*/
unordered_map<char, vector<char>> buildModel() {
    ifstream infile;
    string filename ("./Stats/results.txt");
    infile.open(filename);

    // check for file not found error
    if (!infile.good()) {
        cerr << "ERROR: Can not find " << filename << endl;
        exit(1);
    }

    // read the file
    unordered_map<char, vector<char>>  modelMap;
    string line;
    char key;
    while (getline(infile, line)) {
        vector<string> vline = split(line);
        if (vline.size() == 0) {
            continue;
        }
        if (vline.at(0) == "==") {
            vector<char> v;
            key = vline.at(1).at(0);
            modelMap[key] = v;
        }
        else {
            modelMap.at(key).push_back(vline[0].at(0));
        }
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

/*
Returns a vector of letters of the alphabet organized by the frequency of 
occurance in the english language.

Params: None
Return: vector with letters sorted by frequency used
*/
vector<char> getLettFreq() {
    char lettFreq[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'r', 'h', 'd', 'l', 
                        'u', 'c', 'm', 'f', 'y', 'w', 'g', 'p', 'b', 'v', 'k',
                        'x', 'q', 'j', 'z'};
    vector<char> v;

    for (int i = 0; i < 26; i++) {
        v.push_back(lettFreq[i]);
    }

    return v;
}

/*
Initializes the array for keeing track of the current guess state for the 
computer.

Params:
*/
vector<char> initGuessState(int size) {
    vector<char> v;
    for (int i = 0; i < size; i++) {
        v.push_back('_');
    }
    return v;
}

/*
Gets the left most letter in the guessed word to be used for processing the 
next guess.

Params: wordState - the current state of the guess known to the guessing ai
Return: the left most char in the known word state, returns '_' if none found.
*/
char getNextLett(vector<char> wordState) {
    bool found = false;
    char lett;
    for (int i = 0; i < wordState.size(); i++) {
        //cout << "Char = " << wordState.at(i);
        if (wordState.at(i) != '_') {
            //cout << "Returned!";
            found = true;
            lett = wordState.at(i);
        }
        else if (found) {
            return lett;
        }
    }
    //cout << endl;
    return '_';
}

/*
Checks if the ai has successfuly guessed a char in the word. 

Params: word - the word the ai is trying to guess
		wordState - the current computer guess
		guess - the last char the computer guessed.
		lives - the amount of chances that the computer has left to guess the 
		the word correctly
Return: the modified state of the guessed word.
*/
vector<char> processGuess(string word, vector<char> wordState, char guess, 
                            int *lives) {
    bool found = false;
    for (int i = 0; i < word.size(); i++) {
        if (guess == word.at(i)) {
            wordState.at(i) = guess;
            found = true;
        }
    }
    if (!found) {
        *lives -= 1;
    }
    return wordState;
}

/*
Prints out the current state of the computer guess.

Params: guessState - the current state of the computer guess
*/
void printGuessState(vector<char> guessState) {
    for (int i = 0; i < guessState.size(); i++) {
        cout << guessState.at(i);
    }
    cout << endl;
}

/*
Checks if the computer has successfuly guessed the word

Params: guessedState - the current state of the compute's guess
		word - the word the computer is trying to guess
*/
bool wordGuessed(vector<char> guessState, string word) {
    for (int i = 0; i < word.size(); i++) {
        if (guessState.at(i) != word.at(i)) {
            return false;
        }
    }

    return true;
}

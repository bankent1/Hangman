/*
LetterPairFreq.cpp [file1.txt] [file2.txt] ...

This program will find the letter pair frequency within given files.
It will write the results to another file called "results.txt"

*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct Letters {
    // holds the count for each letter in the alphabet
    int count[26];
};

unordered_map<char, Letters> initLettMap();
unordered_map<char, Letters> readFile(FILE*, unordered_map<char, Letters>);
void printFreq(unordered_map<char, Letters>);
void sort(int[], int[], int);


int main(int argc, char *args[]) {		
    if (argc == 1) {
	    cout << "Missing Arguments!\n";
	    cout << "Usage: LetterPairFreq.cpp [file1.txt] [file2.txt] . . . \n";
	    exit(1);
    }
    // initialize map
    unordered_map<char, Letters> lettMap;
    lettMap = initLettMap();

    // read all files
    for (int i = 1; i < argc; i++) {
        FILE *infile = fopen(args[i], "r");
        if (infile == NULL) {
            cout << "ERROR: " << args[i] << " not found!\n";
            continue;
        }
        cout << "Reading " << args[i] << " . . . ";
        lettMap = readFile(infile, lettMap);
        cout << "DONE" << endl;
        fclose(infile);
    }

    printFreq(lettMap);
    
}

/*
Initializes a map with lowercase letters as the key and Letters struct as 
the value. The Letters struct will hold an array of integers representing 
count of each letter found in the file. Overall the map is meant to map 
pairs of letters to total times found in the file.

Params: None
Returns: unordered_map with char as key and Letters struct as value.
*/
unordered_map<char, Letters> initLettMap() {
    unordered_map<char, Letters> lettMap;
    
    for (int i = 0; i < 26; i++) {
	    char lett = i + 'a';
        Letters l;
        for (int j = 0; j < 26; j++) {
            l.count[j] = 0;
        }
        lettMap[lett] = l;
    }
    return lettMap;

}

/*
Counts the frequeny of letter pairs in the given file. This is done using a intitialized
map and increasing the count every time the pair of letters is found in the file.

Params: infile - file to read
        lettMap - initialized map of letter pairs to count
Return: Updated map of letter to Letters struct found in file
*/
unordered_map<char, Letters> readFile(FILE *infile, unordered_map<char, Letters> lettMap) {
    int c;
    char prev;
    char curr;
    
    // Read first character from file
    if ((c = getc(infile)) != EOF) {
        prev = tolower(c);
    }

    while ((c = getc(infile)) != EOF) {
        curr = tolower(c);
        // check that both characters are letters
        if (prev >= 'a' && prev <= 'z' && curr >= 'a' && curr <= 'z') {
            lettMap.at(prev).count[curr-'a'] += 1;
        }
        prev = curr;
    }

    return lettMap;
}

/*
Prints out the letter pair count to a file. The data is organized by letter 
and then the number of times each letter in the alphabet follows the letter.

Params: lettMap - the map storing the mapping between letter pair and num times
                  found in files.
Return: None
*/
void printFreq(unordered_map<char, Letters> lettMap) {
    ofstream outfile;
    outfile.open("results.txt");

    for (auto iter = lettMap.begin(); iter != lettMap.end(); ++iter) {
        outfile << "== " << iter->first << " ==" << endl;
        int pos[26];
        sort(iter->second.count, pos, 26);
        for (int i = 0; i < 26; i++) {
            outfile << (char)(pos[i]+'a') << " -- " << iter->second.count[i] << endl;
        }
        outfile << endl;
    }
    outfile.close();
}

/*
Sorts the given array using insertion sort algorithm.

Params: arr - int array to be sorted
Returns: int array contianing the sorted letter values (i.e. A, B, ...)
*/
void sort(int arr[], int pos[], int size) {
	// int pos[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	// 		 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
    for (int i = 0; i < 26; i++) {
        pos[i] = i;
    }
	for (int i = 1; i < size; i++) {
		int j = i;
		while (j != 0 && arr[j] > arr[j-1]) {
			// swap values
			int temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
			// swap position
			temp = pos[j];
			pos[j] = pos[j-1];
			pos[j-1] = temp;
			j--;
		}	
	} // end for	
	//return pos;
}
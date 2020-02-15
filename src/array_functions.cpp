/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

#include "array_functions.h"
#include "constants.h"
#include <array>
#include <iostream>
#include <fstream>
#include <algorithm>

struct counter {
	int occurences = -1;
	std::string word = "";
};

bool compareOccurences(counter lhs, counter rhs) {
	return lhs.occurences > rhs.occurences;
}

bool compareAscending(counter lhs, counter rhs) {
	return lhs.word < rhs.word;
}

bool compareDescending(counter lhs, counter rhs) {
	return lhs.word > rhs.word;
}

std::array<counter, 100> wordArray;

int nextEmpty = 0;

void clearArray(){

	int i = 0;

	while(true) {

		if (i > wordArray.size() - 1) {
			break;
		}

		if (i == nextEmpty) {
			break;
		}

		wordArray[i].occurences = -1;
		wordArray[i].word = "";

		i++;
	}

	nextEmpty = 0;

}

int getArraySize(){

	return nextEmpty;

}

std::string getArrayWordAt(int i){
	if (i > getArraySize() - 1) {
		return "out of bounds";
	} else {
		return wordArray[i].word;
	}

}
int getArrayWord_NumbOccur_At(int i) {
	if (i > getArraySize() - 1) {
			return 0;
		} else {
			return wordArray[i].occurences;
		}
}

bool processFile(std::fstream &myfstream) {
	if (myfstream.is_open()) {
		std::string line;

		while (!myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}

		return true;

	} else {
		return false;
	}
}

void processLine(std::string &myString) {

	int i = 0;
	std::string subString = "";

	while (i < myString.size()) {

		if (myString[i] == ' ') {
			processToken(subString);
			subString = "";
		} else {
			subString += myString[i];
		}
		i++;
	}

	processToken(subString);
}

void processToken(std::string &token) {

	token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
	token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
	token.erase(std::remove(token.begin(), token.end(), '.'), token.end());
	token.erase(std::remove(token.begin(), token.end(), ','), token.end());

	int i = 0;
	bool found = false;

	while (i < nextEmpty) {
		std::string tempA = token;
		std::string tempB = wordArray[i].word;

		transform(tempA.begin(), tempA.end(), tempA.begin(), ::tolower);
		transform(tempB.begin(), tempB.end(), tempB.begin(), ::tolower);

		if (tempA == tempB) {
			wordArray[i].occurences++;
			found = true;
		}

		i++;
	}

	if (token.empty()) {
		found = true;
	}

	if (!found) {
		wordArray[nextEmpty].word = token;
		wordArray[nextEmpty].occurences = 1;
		nextEmpty++;
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode) {
	myfile.open(myFileName, mode);
	if (myfile.is_open()) {
		return true;
	} else {
		return false;
	}
}

void closeFile(std::fstream& myfile) {
	myfile.close();
}

int writeArraytoFile(const std::string &outputfilename) {

	if (getArraySize() == 0) {
		return -3;
	}

	std::ofstream myfile("./output/testdata_full.out");

	//myfile.open (outputfilename);

	for(counter token : wordArray) {
		myfile << token.word;
		myfile << " ";
		myfile << token.occurences;
		myfile << "\n";
	}

	myfile.close();
	return 0;
}

void sortArray(constants::sortOrder so) {
	switch(so) {
	case 0:
		break;
	case 1:
		for (int i = 0; i < wordArray.size(); i = i + 1) {
			if (wordArray[i].word == "") {
				wordArray[i].word = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
			}
		}

		std::sort(wordArray.begin(), wordArray.end(), compareAscending);

		for (int i = 0; i < wordArray.size(); i = i + 1) {
			if (wordArray[i].word == "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") {
				wordArray[i].word = "";
			}
		}
		break;
	case 2:
		std::sort(wordArray.begin(), wordArray.end(), compareDescending);
		break;
	case 3:
		std::sort(wordArray.begin(), wordArray.end(), compareOccurences);
		break;
	}
}


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
#include <array>

struct counter {
	int occurences = 0;
	std::string word = "";
};

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

		wordArray[i].occurences = 0;
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
	;
}

void processToken(std::string &token) {

	int i = 0;
	bool found = false;

	while (i < nextEmpty) {
		if (token == wordArray[i].word) {
			wordArray[i].occurences++;
			found = true;
		}

		i++;
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
	return 0;
}

void sortArray(constants::sortOrder so) {
	;
}


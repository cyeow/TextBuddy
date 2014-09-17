#pragma once
// CE1TextBuddy.cpp:
// TextBuddy is used to store, retrieve and delete lines in a textfile. 
// The command format is given by the example interaction below:
//
// Welcome to TextBuddy. <filename>.txt is ready for use
// command: add a quick brown fox
// added to <filename>.txt: "a quick brown fox"
// command: add jumped over a lazy dog
// added to <filename>.txt: "jumped over a lazy dog"
// command: display
// 1. a quick brown fox
// 2. jumped over a lazy dog
// command: delete 1
// deleted from <textfile>.txt: "a quick brown fox"
// command: display
// 1. jumped over a lazy dog
// command: clear
// all content deleted from <textfile>.txt
// command: exit
// 
// author: Yeow Li Teng Cheryl 

#ifndef TEXTBUDDY_H
#define TEXTBUDDY_H

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_ARGUMENTS = 2;
const int MAX_BUFFER_CHARACTERS = 255;
const int TEXTFILE_NAME = 1;
const int FILE_IS_EMPTY = 1;

class TextBuddy {

public:
	enum CommandType {
		ADD_LINE, DISPLAY_ALL, DELETE_LINE, CLEAR_ALL, SORT, SEARCH, EXIT, INVALID
	};

	static void main(int argc, char* argv[]);

	static void inputCommand(string filename);
	static string executeCommand(string filename, string userCommand);

	static string addLine(string filename, string content);
	static string displayAll(string filename);
	static string deleteLine(string filename, string content);
	static string clearAll(string filename);
	static string sortAlphabetical(string filename);
	static string searchFile(string filename, string content);

	static vector<string>::iterator getLineIter(string filename, string content);

	static CommandType determineCommandType(string command);

	static string removeFirstWord(string command);
	static string getFirstWord(string command);

	static void writeToFile(string filename);
	static void printLine(int i, string line);
	static void showToUser(string text);

	static string checkCommandType(TextBuddy::CommandType command);
	static bool checkInvalidInput(string content);
	static void checkCLI(int argc);

	static void initStore(string filename);


private:
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_CLEARED;
	static const string MESSAGE_SORTED;
	static const string MESSAGE_SEARCH_FOUND;
	static const string MESSAGE_LINE_NOT_FOUND;
	static const string MESSAGE_INVALID_FORMAT;
	static const string MESSAGE_PROGRAM_TERMINATION;
	static const string MESSAGE_WELCOME;
	static const string ERROR_UNRECOGNISED_COMMAND_TYPE;
	static const string ERROR_USAGE;
	static const string PROMPT_COMMAND;

	static char buffer[MAX_BUFFER_CHARACTERS];
	static vector<string> store;

};

#endif

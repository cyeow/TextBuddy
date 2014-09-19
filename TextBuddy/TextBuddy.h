#pragma once

// TextBuddy.h:
// TextBuddy is used to store, retrieve and delete lines in a textfile. 
// The command format is given by the example interaction below:
//
// Welcome to TextBuddy. <filename>.txt is ready for use
// command: add Lorem ipsum dolor sit amet
// added to <filename>.txt: "Lorem ipsum dolor sit amet"
// command: add consectetuer adipiscing elit
// added to <filename>.txt: "consectetuer adipiscing elit"
// command: display
// 1. Lorem ipsum dolor sit amet
// 2. consectetuer adipiscing elit
// command: delete 1
// deleted from <textfile>.txt: "Lorem ipsum dolor sit amet"
// command: display
// 1. consectetuer adipiscing elit
// command: add dolor
// added to <filename>.txt: "dolor"
// command: add eget dolor
// added to <filename>.txt: "eget dolor"
// command: add Aenean commodo ligula eget dolor
// added to <filename>.txt: "Aenean commodo ligula eget dolor"
// command: display
// 1. consectetuer adipiscing elit
// 2. dolor
// 3. eget dolor
// 4. Aenean commodo ligula eget dolor
// command: search dolor
// 1. dolor
// 2. eget dolor
// 3. Aenean commodo ligula eget dolor
// found 3 result(s) in <filename>.txt
// command: sort
// all content in <filename>.txt sorted alphabetically
// command: display
// 1. Aenean commodo ligula eget dolor
// 2. consectetuer adipiscing elit
// 3. dolor
// 4. eget dolor
// command: search eget
// 1. Aenean commodo ligula eget dolor
// 2. eget dolor
// found 2 result(s) in <filename>.txt
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

	static vector<string> store;

	static void main(int argc, char* argv[]);

	static void inputCommand(string filename);
	static string executeCommand(string filename, string userCommand);

	static string addLine(string filename, string content);
	static string displayAll(string filename);
	static string deleteLine(string filename, string content);
	static string clearAll(string filename);
	static string sortAlphabetical(string filename);
	static string searchFile(string filename, string content);

	static string searchLine(string filename, string content, string lineNo);
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


};

#endif

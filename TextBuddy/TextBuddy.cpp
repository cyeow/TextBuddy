#include "stdafx.h"
#include "TextBuddy.h"


// TextBuddy.cpp:
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

#include "stdafx.h"
#include "TextBuddy.h"

using namespace std;

const string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const string TextBuddy::MESSAGE_ADDED = "added to %s: \"%s\"";
const string TextBuddy::MESSAGE_DELETED = "deleted from %s: \"%s\"";
const string TextBuddy::MESSAGE_CLEARED = "all content deleted from %s";
const string TextBuddy::MESSAGE_LINE_NOT_FOUND = "line not found in %s";
const string TextBuddy::MESSAGE_INVALID_FORMAT = "invalid command format: %s\n1. add <text>\n2. delete <line number>\n3. clear\n4. display\n5. sort\n6. search <word(s)>\n7. exit\n";
const string TextBuddy::MESSAGE_PROGRAM_TERMINATION = "Enter any key to exit: ";
const string TextBuddy::MESSAGE_WELCOME = "Welcome to TextBuddy. %s is ready for use";
const string TextBuddy::ERROR_UNRECOGNISED_COMMAND_TYPE = "ERROR: Unrecognised command type.\n1. add <text>\n2. delete <line number>\n3. clear\n4. display\n5. sort\n6. search <word(s)>\n7. exit";
const string TextBuddy::ERROR_USAGE = "ERROR: Usage: textbuddy.exe <filename>.txt";
const string TextBuddy::PROMPT_COMMAND = "command:";

char TextBuddy::buffer[MAX_BUFFER_CHARACTERS] = "";
vector<string> TextBuddy::store;

void TextBuddy::main(int argc, char* argv[]) {
	string filename;

	checkCLI(argc);

	initStore(argv[TEXTFILE_NAME]);

	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[TEXTFILE_NAME]);
	showToUser(buffer);

	inputCommand(argv[TEXTFILE_NAME]);

	return;
}

// receives user input and passes to executeCommand
void TextBuddy::inputCommand(string filename){

	while (true) {
		cout << PROMPT_COMMAND;

		string userCommand;
		getline(cin, userCommand);

		string feedback = executeCommand(filename, userCommand);
		writeToFile(filename);
		showToUser(feedback);
	}

	return;
}

// parses the command and passes it to the appropriate operation
string TextBuddy::executeCommand(string filename, string userCommand) {
	CommandType command;
	string content;

	command = determineCommandType(getFirstWord(userCommand));
	content = removeFirstWord(userCommand);


	switch (command) {
	case ADD_LINE:
		if (checkInvalidInput(content)) {
			sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), getFirstWord(userCommand).c_str());
			return buffer;
		}
		return addLine(filename, content);

	case DISPLAY_ALL:
		return displayAll(filename);

	case DELETE_LINE:
		if (checkInvalidInput(content)) {
			sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), command);
			return buffer;
		}
		return deleteLine(filename, content);

	case CLEAR_ALL:
		return clearAll(filename);

	case EXIT:
		exit(0);

	case INVALID:
		sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str(), userCommand.c_str());
		return buffer;

	default:
		showToUser(ERROR_UNRECOGNISED_COMMAND_TYPE);
		showToUser(MESSAGE_PROGRAM_TERMINATION);

		getchar();
		exit(EXIT_FAILURE);
	}

}

// adds a line to the text file
string TextBuddy::addLine(string filename, string content) {

	store.push_back(content);

	sprintf_s(buffer, MESSAGE_ADDED.c_str(), filename.c_str(), content.c_str());

	return buffer;
}

// displays all content in the text file
string TextBuddy::displayAll(string filename) {

	int lineCount = 1; 

	if (store.begin() == store.end()) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), filename.c_str());
		return buffer;
	}

	for (vector<string>::iterator i = store.begin(); i != store.end(); i++) {
		printLine(lineCount, *i);
		lineCount++;
	}

	return "";
}

// deletes a line (stated) in the text file
string TextBuddy::deleteLine(string filename, string content) {

	vector<string>::iterator i = getLineIter(filename, content);

	sprintf_s(buffer, MESSAGE_DELETED.c_str(), filename.c_str(), i->c_str());

	store.erase(i);

	return buffer;
}

// deletes all content in the text file
string TextBuddy::clearAll(string filename) {

	store.clear();

	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), filename.c_str());

	return buffer;
}

// returns iterator of line number requested (0 <= line number < n)
vector<string>::iterator TextBuddy::getLineIter(string filename, string content) {
	int iter = 1;

	for (vector<string>::iterator i = store.begin(); i != store.end(); i++) {
		if (iter == stoi(content)) {
			return i;
		}
		else
			iter++;
	}

	sprintf_s(buffer, MESSAGE_LINE_NOT_FOUND.c_str(), filename.c_str());

	showToUser(buffer);

	return store.end();
}

// determines the command type of input given
TextBuddy::CommandType TextBuddy::determineCommandType(string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);

	if (command == "add"){
		return CommandType::ADD_LINE;
	}
	else if (command == "display") {
		return CommandType::DISPLAY_ALL;
	}
	else if (command == "delete") {
		return CommandType::DELETE_LINE;
	}
	else if (command == "clear") {
		return CommandType::CLEAR_ALL;
	}
	else if (command == "exit") {
		return CommandType::EXIT;
	}
	else
		return CommandType::INVALID;
}

// returns the string with the first word removed
string TextBuddy::removeFirstWord(string command){
	if (command.find_first_of(" ") == string::npos) {
		return "";
	}
	return command.substr(command.find_first_of(" ") + 1);
}

// returns the first word in a string
string TextBuddy::getFirstWord(string command){
	return command.substr(0, command.find(' '));
}

// transfers strings in vector to file
void TextBuddy::writeToFile(string filename) {
	ofstream file;

	file.open(filename);
	file.close();

	if (store.begin() != store.end()) {
		for (vector<string>::iterator i = store.begin(); i != store.end(); i++) {
			file.open(filename, ios::app);
			file << *i << endl;
			file.close();
		}
	}

	return;
}

// outputs string with line number
void TextBuddy::printLine(int i, string line) {
	cout << i << ". " << line << endl;
}

// outputs message in buffer[] to user
void TextBuddy::showToUser(string text) {
	cout << text << endl;
}

// checks if commandtype output from determineCommandType() is correct. for testing only.
string TextBuddy::checkCommandType(TextBuddy::CommandType command) {

	switch (command){
		case ADD_LINE:
			return "add";
		case DISPLAY_ALL:
			return "display";
		case DELETE_LINE:
			return "delete";
		case CLEAR_ALL:
			return "clear";
		case EXIT:
			return "exit";
		case INVALID:
			return "invalid";
		default:
			return "error";
	}

}

// checks if input is invalid
bool TextBuddy::checkInvalidInput(string content) {
	if (content == "" || content == " ") {
		return true;
	}
	return false;
}

// checks if command line input is correct
void TextBuddy::checkCLI(int argc) {
	if (argc != MAX_ARGUMENTS) {
		// if the command line input is wrong, generates an error message and terminates the program.
		showToUser(ERROR_USAGE);
		showToUser(MESSAGE_PROGRAM_TERMINATION);

		getchar();
		exit(0);
	}
}

// initialises the vector and *.txt 
void TextBuddy::initStore(string filename) {
	ifstream inFile;
	string line;

	inFile.open(filename);

	while (getline(inFile, line)) {
		store.push_back(line);
	}

	inFile.close();

	return;
}

int main(int argc, char* argv[]) {
	TextBuddy::main(argc, argv);
}

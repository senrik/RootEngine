#include "Console.hpp"

Console* Console::instance = nullptr;

std::map<std::string, FunctionPointer>* Console::consoleFunctions = new std::map<std::string, FunctionPointer>();


Console* Console::GetInstance() {
	if (instance == nullptr) {
		instance = new Console();
	}

	return instance;
}

void Console::AddFunction(const std::string &label, const int& paramNum, const ptr_consoleFunction func) {
	
	FunctionPointer _funcCard;
	_funcCard.paramNum = paramNum;
	_funcCard.ptr_func = func;

	consoleFunctions->insert(std::pair<std::string, FunctionPointer>(label, _funcCard));

}

void Console::CallFunction(const std::string& label, const int params[]) {
	
	
	return;
}

void Console::Input(std::istream& in) {
	std::string _input;
	std::getline(in, _input);
	// we need to parse the string to determine if the format is correct
	// Expected format for commands:
	// COMMAND_NAME # # # ....
	// The first part in the space separated string should be the command name
	// Grab that and determine if it is a valid console function
	
}
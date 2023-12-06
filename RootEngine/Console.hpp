#pragma once
#include <map>
#include <iostream>
#include <string>

typedef void(*ptr_consoleFunction)(const int[]);

typedef struct FunctionPointer {
	int paramNum;
	ptr_consoleFunction ptr_func;
};
/// <summary>
/// Designed as a singlton object.
/// </summary>
class Console {
private:
	Console() {};
	static std::map<std::string, FunctionPointer>* consoleFunctions;
	static Console* instance;
public:
	static Console* GetInstance();
	static void AddFunction(const std::string&, const int&, const ptr_consoleFunction);
	static void CallFunction(const std::string&, const int[]);
	static void Input(std::istream&);
};
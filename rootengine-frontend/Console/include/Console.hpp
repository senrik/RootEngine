#ifndef CONSOLE_H
#define CONSOLE_H
#include <map>
#include <iostream>
#include <string>


/// <summary>
/// Designed as a singlton object.
/// </summary>
template<typename FuncType>
class Console {
private:
	Console() {};
	~Console();
	std::map<std::string, FuncType>* consoleFunctions;
	static Console* instance;
public:
	static Console* GetInstance();
	void AddFunction(const std::string&, const int&, FuncType);
	void CallFunction(const std::string&, const int[]);
	void Input(std::istream&);
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;
};

#endif
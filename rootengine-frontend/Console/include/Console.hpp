#ifndef CONSOLE_H
#define CONSOLE_H
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <typeinfo>

template<typename FuncType>
struct FuncCard{
	FuncType* _func;
	int argCount;
};

class ConsoleFunction {
	protected:
		std::string description;
	public:
		ConsoleFunction(std::string _s="") {description = _s;};
		virtual void operator() (void) {};
		virtual void operator() (int arg) {};
		virtual void operator() (std::string _s) {};
		inline std::string GetDescription() const { return description; }
};

class HelpFunction : public ConsoleFunction{
	public:
		HelpFunction(std::string h="") {
			description = h;
			message = "This is a list of supported command-line functions:\n";
			functions = nullptr;
		}
		void operator() (void) {
			std::cout << message << std::endl;
		}

		void UpdateHelpMessage(const std::string&);
		void SetFunctionReference(std::map<std::string, FuncCard<ConsoleFunction>>*);

	private:
	std::string message;
	std::map<std::string, FuncCard<ConsoleFunction>>* functions;
};

class ExitFunction : public ConsoleFunction {
	private:
		int* code;
	public:
		ExitFunction(int* _code = nullptr, std::string desc = "") { 
			code = _code;
			description = desc;
		}
		void operator() (void) {
			*this->code = 0;
		}
};


/// <summary>
/// Designed as a singlton object.
/// </summary>
template<typename FuncType>
class Console {
private:
	Console() {};
	~Console();
	std::map<std::string, FuncCard<FuncType>>* consoleFunctions;
	static Console* instance;
	
public:
	static Console* GetInstance();
	void AddFunction(const std::string&, const int&, FuncType*);
	void CallFunction(const std::string&, const std::string&);
	void Input(std::istream&);
	Console(const Console&) = delete;
	Console& operator=(const Console&) = delete;
};

template<typename FuncType>
Console<FuncType>* Console<FuncType>::instance = nullptr;

template<typename FuncType>
Console<FuncType>* Console<FuncType>::GetInstance() {
	if (instance == nullptr) {
		instance = new Console<FuncType>();
		instance->consoleFunctions = new std::map<std::string, FuncCard<FuncType>>();
		// Default functions
		//instance->AddFunction("help", 0, HelpFunction("List of supported functions:\n\t \'help\'"));
	}

	return instance;
}

template <typename FuncType>
void Console<FuncType>::AddFunction(const std::string& _key, const int& _argNum, FuncType* _func)
{
	if(!consoleFunctions->contains(_key)) {
		// update help function
		if(consoleFunctions->contains("help")){
			auto _helpCard = (*consoleFunctions)["help"];

			HelpFunction* _help = dynamic_cast<HelpFunction*>(_helpCard._func);
			auto functionList = dynamic_cast<std::map<std::string, FuncCard<ConsoleFunction>>*>(consoleFunctions);
			_help->SetFunctionReference(functionList);
			auto function = dynamic_cast<ConsoleFunction*>(_func);
			_help->UpdateHelpMessage("|\t" +_key + ":\t" + function->GetDescription() +"\n");
		}
		//add key and functor
		FuncCard<FuncType> _card;
		_card._func = _func;
		_card.argCount = _argNum;
		(*consoleFunctions)[_key] = _card;

	}
	else {
		std::cerr << "Functional Label \'" << _key <<"\' already exists." <<std::endl;
	}
}

template <typename FuncType>
void Console<FuncType>::CallFunction(const std::string & _key, const std::string& _arg)
{
	try {
		//std::cout << "CallFunction called with key: "<< _key << " and arg: " << _arg << std::endl;
		if(consoleFunctions->contains(_key)) {
		FuncCard _func = consoleFunctions->at(_key);
		if(_func.argCount == 0){
			//std::cout << "Calling function: " << _key << " " <<typeid(*_func._func).name()<< std::endl;
			(*_func._func)();
			
		} else {
			//std::cout << "Calling function: " << _key << " with arg: " << _arg <<std::endl;
			(*_func._func)(_arg);
			
		}
		
	}
	else {
		std::cout<< "Function Label \'" << _key << "\' not found. type \'help\' for a list of supported functions."<< std::endl;
	}
	} catch (std::exception e) {
		std::cout<< "Exception "<< e.what() <<" encountered while calling function \'" << _key << "\'" << std::endl;
	}
	
}

template <typename FuncType>
inline void Console<FuncType>::Input(std::istream & _input)
{
	// TODO Add input verification for commands
	// Should be CONSOLE_COMMAND #
	std::string _rawText, _text, _key, _arg;
	// Get the line of input
	std::getline(_input, _rawText);
	std::stringstream s_stream(_rawText);

	std::getline(s_stream, _key, ' ');

	if(std::getline(s_stream, _arg, ' ')){

		
	}
	


	CallFunction(_key, _arg);
	
	
}


#endif
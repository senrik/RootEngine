#include "Console.hpp"
template<typename FuncType>
Console<FuncType>* Console<FuncType>::instance = nullptr;

template<typename FuncType>
Console<FuncType>* Console<FuncType>::GetInstance() {
	if (instance == nullptr) {
		instance = new Console<FuncType>();
		instance->consoleFunctions = new std::map<std::string, FuncType>();
	}

	return instance;
}

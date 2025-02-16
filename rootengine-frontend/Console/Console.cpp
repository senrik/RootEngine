#include "Console.hpp"



void HelpFunction::UpdateHelpMessage(const std::string & _m)
{
	// reset the help message
	if(_m.length() <=0){
		message = "This is a list of supported command-line functions:\n";
		std::map<std::string, FuncCard<ConsoleFunction>>::iterator it;
		for(it = functions->begin(); it != functions->end(); it++){
			std::string funcListing = "|\t" +it->first + ":\t" + it->second._func->GetDescription() +"\n";
			message += funcListing;
		}
	}
	else {
		message += _m;
	}
	
}

void HelpFunction::SetFunctionReference(std::map<std::string, FuncCard<ConsoleFunction>>* funcList){
	this->functions = funcList;
}
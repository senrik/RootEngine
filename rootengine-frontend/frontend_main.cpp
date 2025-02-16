#include <iostream>
#include <Console.hpp>
#include <GameWorld.hpp>
using namespace std;

/*
* Raspberry Pi 5 has:
* 4 core 2.4GHz 512KB per-core L2 cache and one 2MB shared L3 cache CPU
* 4GB SDRAM
* Limit program to reserving 2GB of memory 2x10^9 (2048 MB) 2048x10^8 (204800000000)
* Char is a byte (8 bits) so the memory pool will be
*/

// Uses the exponential function y = (1/2)^(x-7.32) to determine the chances of how much loot will be dropped

#pragma region GameWorld CL Functions
class GameWorldFunction : public ConsoleFunction {
	public:
		GameWorldFunction(GameWorld* gw, string _desc="") : ConsoleFunction(_desc)
		{
			this->_gw = gw;
		}
	protected:
		GameWorld* _gw;
};
class DescribeWorldFunction : public GameWorldFunction {
	public:
		DescribeWorldFunction(GameWorld* gw, string _desc="") : GameWorldFunction(gw,_desc) {this->_gw = gw;}
		void operator() (void) {
			cout << _gw->ToString() << endl;
		}
};

class MoveFunction : public GameWorldFunction {
	public:
		MoveFunction(GameWorld* gw, string _desc=""): GameWorldFunction(gw,_desc){  };

		void operator() (string _s) {
			auto currentArea = _gw->GetCurrentArea();
			if(_s == "east") {
				if(currentArea.GetNeighbor(CompassEnum::East) != nullptr){
					_gw->SetCurrentArea(*currentArea.GetNeighbor(CompassEnum::East));
					
				} else {
					cout << "The direction " << _s << " is blocked."<<endl;
				}
			}
			else if(_s == "west") {
				if(currentArea.GetNeighbor(CompassEnum::West) != nullptr){
					_gw->SetCurrentArea(*currentArea.GetNeighbor(CompassEnum::West));

				} else {
					cout << "The direction " << _s << " is blocked."<<endl;
				}
			}
			else if(_s == "south") {
				if(currentArea.GetNeighbor(CompassEnum::South) != nullptr){
					_gw->SetCurrentArea(*currentArea.GetNeighbor(CompassEnum::South));

				} else {
					cout << "The direction " << _s << " is blocked."<<endl;
				}
			}
			else if(_s == "north") {
				if(currentArea.GetNeighbor(CompassEnum::North) != nullptr){
					//cout << *currentArea.GetNeighbor(CompassEnum::North)<<endl;
					_gw->SetCurrentArea(*currentArea.GetNeighbor(CompassEnum::North));

				} else {
					cout << "The direction " << _s << " is blocked."<<endl;
				}
			}
			else {
				cout << format("Error, \'{}\' is not a valid direction to move. ",_s);
			}
			
		}
};

class LookFunction : public GameWorldFunction {
	public:
		LookFunction(GameWorld* gw, string _s) : GameWorldFunction(gw, _s) {
			
		}
	void operator() (void) {
		cout << _gw->GetCurrentArea().DescribeArea();
	}
};
#pragma endregion

int main(int argc, char* argv[]) {
	int exitCode = -1;
	Console<ConsoleFunction>* console;
	console = Console<ConsoleFunction>::GetInstance();
	// Default CL Arguments
	console->AddFunction("help", 0, new HelpFunction("Displays this list."));
	
	auto _exit = new ExitFunction(&exitCode, "Exits the application");
	console->AddFunction("exit", 0, _exit);
	
	// GameWorld CL Arguments
	GameWorld* gameWorld = new GameWorld();
	gameWorld->PopulateGameWorld();
	auto _describeWorld = new DescribeWorldFunction(gameWorld, "Prints out all information about the game's world.");
	console->AddFunction("describe_world", 0, _describeWorld);

	auto _move = new MoveFunction(gameWorld, "Attempts to move the indicated direction.");
	console->AddFunction("move", 1, _move);

	auto _look = new LookFunction(gameWorld, "Describes the current area.");
	console->AddFunction("look", 0, _look);

	while(exitCode < 0) {
		// Display (Start of Update Loop)
		cout << gameWorld->GetCurrentArea() << endl;
		console->Input(cin);

		//Set post update loop for arguments to be updated.
		
	}
	return 0;
}
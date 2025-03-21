#include <iostream>
#include <filesystem>
#include <sstream>
#include <Console.hpp>
#include <GameWorld.hpp>
#include <Player.hpp>
using namespace std;

/*
* Raspberry Pi 5 has:
* 4 core 2.4GHz 512KB per-core L2 cache and one 2MB shared L3 cache CPU
* 4GB SDRAM
* Limit program to reserving 2GB of memory 2x10^9 (2048 MB) 2048x10^8 (204800000000)
* Char is a byte (8 bits)
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

class SaveFunction : public GameWorldFunction {
public:
	SaveFunction(GameWorld* gw, const string& desc) : GameWorldFunction(gw,desc){ };

	void operator() (string name) {
		string saveName;
		if(name.length() <= 0 || name == " ") {
			cout << "Input name of save file: ";
			cin >> saveName;
		} else {
			saveName = name;
		}
		cout << "Saving world..." << endl;
		// Call to serialize the world
		_gw->SaveWorld(saveName);
	};
};

class LoadFunction : public GameWorldFunction{
public:
	LoadFunction(GameWorld* gw,const string& desc) : GameWorldFunction(gw,desc) { };
	void operator() (string name) {
		string loadName;
		cout << "Saved Worlds:" << endl;
		for(const auto& entry : filesystem::directory_iterator(".\\saves")) {

			cout << "|\t" << entry.path().stem() << endl;
			
		}
		if(name.length() <= 0 || name == " ") {
			// Show list of saved worlds
			cout << "Type selected world's name: ";
			cin >> loadName;
		}
		while(!filesystem::exists(".\\saves\\" +loadName +".dat")) {
			cout << "Invalid world name, input one of the following: " <<endl;
			for(const auto& entry : filesystem::directory_iterator(".\\saves")) {

				cout << "|\t" << entry.path().stem() << endl;
				
			}
			cin >> loadName;
		}

		_gw->LoadWorld(loadName);
		
		
	}
};

class NewFunction: public GameWorldFunction {
public:
	NewFunction(GameWorld* gw, const string& desc) : GameWorldFunction(gw, desc) { }

	void operator() (void) {
		cout << "Creating new world..." <<endl;
		_gw->PopulateGameWorld();
	}

};

#pragma endregion

#pragma region Player CL Functions
class PlayerFunction : public GameWorldFunction{
	public:
		PlayerFunction(Player* p, GameWorld* gw=nullptr, string desc=""): GameWorldFunction(gw, desc){
			this->_p = p;
		}
	protected:
		Player* _p;
		
};

class LookFunction : public PlayerFunction {
	public:
		LookFunction(Player* p, GameWorld* gw, string _s) : PlayerFunction(p, gw, _s) {
			
		}
	void operator() (string s) {
		if(s.length() <= 0) {
			cout << _gw->GetCurrentArea().DescribeArea();
		}
		else {
			// We have a max of two arguments to account for
			if(s == "self") {
				cout << _p->ToString();
				return;
			}
			stringstream parse;
			parse << s;
			string buf;
			getline(parse, buf, ' ');
			if(buf == "items") {
				cout << _gw->GetCurrentArea().ListItems();
			}else if(buf == "item") {
				getline(parse, buf, ' ');

				cout << _gw->GetCurrentArea().PeekItem(buf);
				
			}

			// while (getline(parse, buf, ' '))
			// {
			// 	cout << buf << endl;
			// }
			
			
		} 
		
	}
};

class PickupFunction : public PlayerFunction{
	public:
		PickupFunction(Player* p =nullptr, GameWorld* gw=nullptr, string desc="") : PlayerFunction(p,gw,desc) {	}
	void operator() (string itemLabel){
		auto _area = _gw->GetCurrentArea();

		// get item from _area and add it to the player's inventory
	}
};
#pragma endregion

/// @brief Creates NPC and Item Databases if they don't exist.
void InitializeDatabase(const string& itemDBName, const string& npcDBName) {
	
	// if item database does not exist, create it
	fstream itemDatabase(itemDBName, ios::in);
	if(!itemDatabase.good()) {
		if(itemDatabase.is_open()) {
			itemDatabase.close();
		}

		itemDatabase.open(itemDBName, ios::out);
		itemDatabase.close();
	}

	// if npc database does not exist, create it
	fstream npcDatabase(npcDBName, ios::in);
	if(!npcDatabase.good()) {
		if(npcDatabase.is_open()) {
			npcDatabase.close();
		}

		npcDatabase.open(npcDBName, ios::out);
		npcDatabase.close();
	}
	
}

void InitializeConsole(int& exitCode){
	Console<ConsoleFunction>* console;
	console = Console<ConsoleFunction>::GetInstance();
	// Default CL Arguments
	console->AddFunction("help", 0, new HelpFunction("Displays this list."));
	
	auto _exit = new ExitFunction(&exitCode, "Exits the application");
	console->AddFunction("exit", 1, _exit);
}

void InitializeFileStructure(){
	// If data folder does not exist, create it
	if(!filesystem::exists("./data")) {
		filesystem::create_directory("./data");
	}
	// If save folder does not exist, create it
	if(!filesystem::exists("./saves")) {
		filesystem::create_directory("./saves");
	}
}

default_random_engine gen;

// Populates the databases with some initial data
void SeedDatabase(const string& itemDBName, const string& npcDBName){
	// 10 NPCs and 10 Items
	fstream itemDatabase(itemDBName, ios::out | ios::binary);
	for(int i = 0; i < 10; i++){
		Item* _temp = new Item();
		_temp->GenerateEntity();
		//cout << "Serializing Item @ "<< i << ": " << endl << _temp->ToString();
		_temp->SerializeEntity(itemDatabase);
		
		delete _temp;
	}
	itemDatabase.close();

	fstream npcDatabase(npcDBName, ios::out | ios::binary);
	for(int i = 0; i < 10; i++){
		NPC* _temp = new NPC();
		_temp->GenerateEntity();
		_temp->GenerateLootTable(itemDatabase, itemDBName);
		//cout << "Serializing NPC @ "<< i << ": " << endl << _temp->ToString();
		_temp->SerializeEntity(npcDatabase);

		delete _temp;
	}
	npcDatabase.close();

}

int main(int argc, char* argv[]) {
	int exitCode = -1;
	InitializeFileStructure();
	InitializeConsole(exitCode);
	InitializeDatabase("./data/itemDB.dat","./data/npcDB.dat");
	SeedDatabase("./data/itemDB.dat","./data/npcDB.dat");
	Console<ConsoleFunction>* console = Console<ConsoleFunction>::GetInstance();
	// GameWorld CL Arguments
	GameWorld* gameWorld = new GameWorld("./data/itemDB.dat","./data/npcDB.dat");
	gameWorld->SetDBReferences("./data/itemDB.dat","./data/npcDB.dat");
	//gameWorld->PopulateGameWorld("./data/itemDB.dat","./data/npcDB.dat");
	Player* player = new Player();

	auto _saveWorld = new SaveFunction(gameWorld, "Saves the current state of the world to a file.");
	console->AddFunction("save", 1, _saveWorld);

	auto _loadWorld = new LoadFunction(gameWorld, "Loads a game world from the specified file.");
	console->AddFunction("load", 1, _loadWorld);

	auto _newWorld = new NewFunction(gameWorld, "Generates a new GameWorld.");
	console->AddFunction("new", 0, _newWorld);

	auto _describeWorld = new DescribeWorldFunction(gameWorld, "Prints out all information about the game's world.");
	console->AddFunction("describe_world", 0, _describeWorld);

	auto _move = new MoveFunction(gameWorld, "Attempts to move the indicated direction.");
	console->AddFunction("move", 1, _move);

	// Player CL Arguments
	auto _look = new LookFunction(player, gameWorld, "Describes the inidicated entity, if valid.");
	console->AddFunction("look", 2, _look);

	
	cout<< GameWorld::GAME_TITLE << endl;
	while(exitCode < 0) {
		// Display (Start of Update Loop)
		//cout << gameWorld->GetCurrentArea() << endl;
		if(gameWorld->IsInitialized()) {
			cout << gameWorld->GetCurrentArea() <<endl;
		}
		console->Input(cin);

		//Set post update loop for arguments to be updated.
		
	}
	return 0;
}
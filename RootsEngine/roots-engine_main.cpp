#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <random>
#include <cmath>
using namespace std;

/*
* Raspberry Pi 5 has:
* 4 core 2.4GHz 512KB per-core L2 cache and one 2MB shared L3 cache CPU
* 4GB SDRAM
* Limit program to reserving 2GB of memory 2x10^9 (2048 MB) 2048x10^8 (204800000000)
* Char is a byte (8 bits) so the memory pool will be
*/


#pragma region Itemization
enum ItemType {
	None = 0,
	Weapon = 1,
	Armor = 2,
	Consumable = 3
};

enum Statistics {
	Health = 0,
	Attack = 1,
	Defense = 2,
	Speed = 3
};

struct StatModifiers {
	size_t modifiers[4];
};

class Item {
public:
	Item();
	Item(const ItemType&, const StatModifiers&);
	ItemType GetType();
	StatModifiers Use();
	string ToString();
private:
	string label;
	ItemType itemType;
	size_t healthMod;
	size_t attackMod;
	size_t defenseMod;
	size_t speedMod;
};

struct Loot {
	Item items[4];
	string ToString();
};
#pragma endregion

#pragma region NPC
class NPC {
public:
	NPC();
	bool IsHostile();
	string Response();
	Loot GetLoot();
	string ToString();
private:
	bool hostile;
	size_t health;
	size_t attack;
	size_t defense;
	size_t speed;
	string responseDialogue;
	string label;
	Loot npcLoot;
};
#pragma endregion

#pragma region GameWorld
constexpr int ITEMS_PER_AREA = 3;
constexpr int NPCS_PER_AREA = 3;
constexpr int MAX_REGIONS = 5;
constexpr int MIN_REGIONS = 1;
constexpr int MAX_AREAS_IN_REGION = 15;
constexpr int MIN_AREAS_IN_REGION = 3;

enum CompassEnum {

	North = 0,
	South = 1,
	East = 2,
	West = 3,
};

ostream& operator <<(ostream& strm, CompassEnum compass);


class Area {
public:
	Area();
	Area(const string&);
	Area(const string&, const string&);
	string DescribeArea();
	void SetDescription(const string&);
	void SetNeighbor(const size_t&, Area*);
	Area* GetNeighbor(const size_t&);
	void AddItem(const Item&);
	void AddNPC(const NPC&);
private:
	string description;
	string label;
	vector<Item> items;
	vector<NPC> npcs;
	Area* neighbors[4]; // N, S, E, W
	friend ostream& operator<<(ostream&, const Area&);
};

class Region {
public:
	Region();
	Region(const string&);
	string ListAreas();
	size_t AreaNum();
	void AddArea(const Area&);
	string DescribeRegion();
protected:
	vector<Area> areas;
	string label;
	Area* neighbors[4]; // N, S, E, W
};

class World {
public:
	World();
	World(const string&);
	//World(const size_t&, const size_t&, const size_t&);
	void AddRegion(const Region&);
	string DescribeWorld();
protected:
	vector<Region> regions;
	string label;
};

class GameWorld {
public:
	GameWorld();
	void PopulateGameWorld();
	string ToString();
private:
	World* world;
};

struct AreaLink {
	Area* parent, * area;
	CompassEnum parentDirection;

	friend ostream& operator<<(ostream&, const AreaLink&);
};

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

void PopulateArea(Area&);

#pragma endregion

// Uses the exponential function y = (1/2)^(x-7.32) to determine the chances of how much loot will be dropped
Loot GenerateLootTable();

Item GenerateItem();



int main(int argc, char* argv[]) {
	int exitCode = -1;
	GameWorld gameWorld = GameWorld();
	gameWorld.PopulateGameWorld();
	while (exitCode < 0) {
		char* input = new char[10];
		cin.getline(input, 10);
		cout << gameWorld.ToString();

		gameWorld.PopulateGameWorld();
	}
	
	
	return 0;
}
#pragma region Itemization Implementation
Item::Item() {
	this->itemType = ItemType::None;
	this->healthMod = 0;
	this->attackMod = 0;
	this->defenseMod = 0;
	this->speedMod = 0;
	this->label = "Item";
}


Item::Item(const ItemType& _type, const StatModifiers& _mods) {
	this->label = "Item";
	this->itemType = _type;
	this->healthMod = _mods.modifiers[Statistics::Health];
	this->attackMod = _mods.modifiers[Statistics::Attack];
	this->defenseMod = _mods.modifiers[Statistics::Defense];
	this->speedMod = _mods.modifiers[Statistics::Speed];
}

StatModifiers Item::Use() {
	StatModifiers _stats;
	_stats.modifiers[Statistics::Health] = this->healthMod;
	_stats.modifiers[Statistics::Attack] = this->attackMod;
	_stats.modifiers[Statistics::Defense] = this->defenseMod;
	_stats.modifiers[Statistics::Speed] = this->speedMod;

	return _stats;
}

ItemType Item::GetType() {
	return itemType;
}

string Item::ToString() {
	string _output = "";
	_output+= "Name: " +this->label + "\n";
	switch (this->itemType) {
	case 0:
		_output += "|\tType: None\n";
		break;
	case 1:
		_output += "|\tType: Weapon\n";
		break;
	case 2:
		_output += "|\tType: Armor\n";
		break;
	case 3:
		_output += "|\tType: Consumable\n";
		break;
	}
	_output += "|\tHealth Modifier: " + to_string(this->healthMod) + "\n";
	_output += "|\tAttack Modifier: " + to_string(this->attackMod) + "\n";
	_output += "|\tDefense Modifier: " + to_string(this->defenseMod) + "\n";
	_output += "|\tSpeed Modifier: " + to_string(this->speedMod) + "\n";
	
	return _output;
}
Item GenerateItem() {
	int _type = (rand() % (3)) + 1;
	StatModifiers _stats;
	_stats.modifiers[Statistics::Health] = rand() % 20 + 20;
	_stats.modifiers[Statistics::Attack] = rand() % 5 + 5;
	_stats.modifiers[Statistics::Defense] = rand() % 5 + 5;
	_stats.modifiers[Statistics::Speed] = rand() % 5 + 5;

	return Item((ItemType)_type, _stats);
}

Loot GenerateLootTable() {
	Loot _lootTable;
	for (int i = 0; i < 4; i++)
	{
		// Roll has to be less than the population chance
		float _lootRoll = rand() % 100;
		//
		float _chance = pow(0.5, (i + 1) - 7.32);
		if (_lootRoll < _chance)
		{
			_lootTable.items[i] = GenerateItem();
		}
		else {
			break;
		}
	}

	return _lootTable;
}

string Loot::ToString() {
	string _output = "";
	_output += "LootTable:\n";
	for (int i = 0; i < 4; i++)
	{
		if (this->items[i].GetType() == ItemType::None) {
			break;
		}
		_output += this->items[i].ToString();
	}

	return _output;
}
#pragma endregion

#pragma region NPC Implementation
NPC::NPC() {
	this->hostile = false;
	this->health = 100;
	this->attack = 10;
	this->defense = 10;
	this->speed = 10;
	this->label = "NPC";
	this->responseDialogue = "Hello!";

	// Populate Loot Table
	// The chances of items being in the loot table should decrease with every item added
	// 1 - 80%: rand() % 100 > 20 = 100 - 80/i+1 @ 0
	// 2 - 40%: rand() % 100 > 60 = 100 - 80/i+1 @ 1 
	// 3 - 20%: rand() % 100 > 80 = 100 - 80/i+1 @ 2
	// 4 - 10%: rand() % 100 > 90 = 100 - 80/i+1 @ 3
	this->npcLoot = GenerateLootTable();
}

bool NPC::IsHostile() {
	return hostile;
}

string NPC::Response() {
	return responseDialogue;
}

Loot NPC::GetLoot() {
	return npcLoot;
}

string NPC::ToString() {
	return "I am an NPC, this is a placeholder, doot doot.";
}

#pragma endregion

#pragma region GameWorld Implementation

ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

#pragma region Area Implementation
Area::Area() {
	description = "This an Area.";
	label = "Area";
	for (int i = 0; i < 4; i++) {
		neighbors[i] = nullptr;
	}
}

Area::Area(const string& desc) {
	this->description = desc;
	label = "Area";
	for (int i = 0; i < 4; i++) {
		neighbors[i] = nullptr;
	}
}

Area::Area(const string& desc, const string& label) {
	this->description = desc;
	this->label = label;
	for (int i = 0; i < 4; i++) {
		neighbors[i] = nullptr;
	}
}

string Area::DescribeArea() {
	string _output = format("{} {}\n", this->label, this->description);
	_output += format("Has {} items:\n", this->items.size());
	for (int i = 0; i < this->items.size(); i++)
	{
		_output += this->items[i].ToString();
	}
	_output += format("Has {} NPCs: \n", this->npcs.size());
	for (int i = 0; i < this->npcs.size(); i++)
	{
		_output += this->npcs[i].ToString();
	}
	return _output;
}

void Area::SetDescription(const string& desc) {
	this->description;
}

void Area::SetNeighbor(const size_t& _index, Area* _area) {
	this->neighbors[_index] = _area;
}

Area* Area::GetNeighbor(const size_t& index) {
	return this->neighbors[index];
}

void Area::AddItem(const Item& _item) {
	this->items.push_back(_item);
}
void Area::AddNPC(const NPC& _npc) {
	this->npcs.push_back(_npc);
}

ostream& operator<<(ostream& out, const Area& _area) {
	/*       [0]
	*         ^
	*         |
	* [3] < - O - > [2]
	*         |
	*         v
	*        [1]
	*
	*/
	out << format("       {}       \n       ^\n       |\n{} < - {} - > {}\n       |\n       v\n       {}\n",
		(_area.neighbors[0] != nullptr) ? _area.neighbors[0]->label : "None",
		(_area.neighbors[3] != nullptr) ? _area.neighbors[3]->label : "None",
		_area.label,
		(_area.neighbors[2] != nullptr) ? _area.neighbors[2]->label : "None",
		(_area.neighbors[1] != nullptr) ? _area.neighbors[1]->label : "None");
	return out;
}
#pragma endregion

#pragma region Region Implementation
Region::Region() {
	areas = vector<Area>();
	label = "Region";
	for (int i = 0; i < 4; i++) {
		neighbors[i] = nullptr;
	}
}

Region::Region(const string& _label) {
	areas = vector<Area>();
	label = _label;
	for (int i = 0; i < 4; i++) {
		neighbors[i] = nullptr;
	}
}

void Region::AddArea(const Area& _area) {
	areas.push_back(_area);
}

string Region::ListAreas() {
	string _output = "This region's areas: ";

	for (int i = 0; i < areas.size(); i++)
	{
		_output += "\t" + areas[i].DescribeArea() + "\n";
	}
	return _output;
}

size_t Region::AreaNum() {
	return areas.size();
}

string Region::DescribeRegion() {
	string _output = "";
	_output = format("The region: {} has {} number of areas.\n", label, AreaNum());
	for (int i = 0; i < AreaNum(); i++)
	{
		_output += "|\t"+areas[i].DescribeArea() + "\n";
	}
	return _output;
}
#pragma endregion

#pragma region World Implementation
World::World() {
	regions = vector<Region>();
}

World::World(const string& label) {
	this->label = label;
}

void World::AddRegion(const Region& _region) {
	regions.push_back(_region);
}
//World::World(const size_t& num_regions, const size_t& minAreas, const size_t& maxAreas) {
//	size_t areaNum = rand() % (maxAreas - minAreas) + minAreas;
//	while (regions.size() < num_regions) {
//		Region _region = Region("Region " + to_string(regions.size()));
//		while (_region.AreaNum() < areaNum) {
//			_region.AddArea(Area("This an Area.", "Area " + to_string(_region.AreaNum())));
//		}
//
//		areaNum = rand() % (maxAreas - minAreas) + minAreas;
//		regions.push_back(_region);
//	}
//}

string World::DescribeWorld() {
	string _output = "This world as " + to_string(regions.size()) + " regions.\n";
	for (int i = 0; i < regions.size(); i++)
	{
		_output += regions[i].DescribeRegion();
	}
	return _output;
}
#pragma endregion

#pragma region GameWorld
GameWorld::GameWorld() {
	world = new World("World");
}
// An area can only have four connections, these are pointers to the different areas
// Area* neighbors[];
// Have an enum that acts as the compass directions.
// enum CardinalDirections {...} N, S, E, W
// We use a random chance to determine if we are breadth-first or depth first
// We want the chance to change as more areas are added
// Initially the chance for depth-first is higher, but as more areas are added it weights breadth-first higher
// Initial split is 70-30 and final split will be 40-60 DFS: y=-5/2x+155/2 BFS: y=5/2x+45/2
// Stack is Depth-first, Queue is breadth-first
// maintain one vector
// Pop members off the top of the vector for DFS and pop members off the bottom for BFS
void GameWorld::PopulateGameWorld() {
	delete world;
	world = new World("World");
	vector<Area*> fringe;
	size_t regionNum = rand() % (MAX_REGIONS - MIN_REGIONS) + MIN_REGIONS;
	for (int i = 0; i < regionNum; i++) {
		// Steps for populating a region
		// create the region
		Region _newRegion = Region("Region " + to_string(i));
		// determine the number of areas
		size_t areaNum = rand() % (MAX_AREAS_IN_REGION - MIN_AREAS_IN_REGION) + MIN_AREAS_IN_REGION;
		// create an area
		Area* _newArea = new Area("This is an area.", "Area 0");
		// Populate the Area
		PopulateArea(*_newArea);
		// Add the area's neighbors to our vector
		/*for (int j = 0; j < 4; j++) {
			fringe.push_back(_newArea->GetNeighbor(j));
		}*/
	}

	// Original world generation, no neighbors
	/*size_t regionNum = rand() % (MAX_REGIONS - MIN_REGIONS) + MIN_REGIONS;
	for (int i = 0; i < regionNum; i++) {
		size_t areaNum = rand() % (MAX_AREAS_IN_REGION - MIN_AREAS_IN_REGION) + MIN_AREAS_IN_REGION;
		// Populate Region
		Region _newRegion = Region("Region " + to_string(i));
		for (int j = 0; j < areaNum; j++) {
			// Populate Area
			Area _newArea = Area("This is an area.", "Area " + to_string(j));

			size_t npcInArea = rand() % NPCS_PER_AREA;
			for (int k = 0; k < npcInArea; k++) {
				_newArea.AddNPC(NPC());
			}

			size_t itemInArea = rand() % ITEMS_PER_AREA;
			for (int l = 0; l < itemInArea; l++) {
				_newArea.AddItem(GenerateItem());
			}
			_newRegion.AddArea(_newArea);
		}
		world->AddRegion(_newRegion);
	}*/
}

string GameWorld::ToString() {
	return world->DescribeWorld();
}

void PopulateArea(Area& _area) {
	size_t npcInArea = rand() % NPCS_PER_AREA;
	for (int k = 0; k < npcInArea; k++) {
		_area.AddNPC(NPC());
	}

	size_t itemInArea = rand() % ITEMS_PER_AREA;
	for (int l = 0; l < itemInArea; l++) {
		_area.AddItem(GenerateItem());
	}
}
#pragma endregion

#pragma endregion
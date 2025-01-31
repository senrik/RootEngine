#include "GameWorld.hpp"

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
		
		_output += this->items.at(i)->ToString();
	}
	_output += format("Has {} NPCs: \n", this->npcs.size());
	for (int i = 0; i < this->npcs.size(); i++)
	{
		_output += this->npcs.at(i)->ToString();
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

void Area::AddItem(Entity* _item) {
	this->items.push_back(_item);
}
void Area::AddNPC(Entity* _npc) {
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
        
		_area.AddNPC(new NPC());
	}

	size_t itemInArea = rand() % ITEMS_PER_AREA;
	for (int l = 0; l < itemInArea; l++) {
		_area.AddItem(new Item());
	}
}
#pragma endregion

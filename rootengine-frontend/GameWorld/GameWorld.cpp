#include "GameWorld.hpp"

string GameWorld::GAME_TITLE = R"(+=========================================================================================================================================================+
|        //////////////   /////////////   ////////////   ////////////   ||||||||||||   \\\\\\\\\\\\\\   \\\\\\\\\\\\   \\\\\\\\\\\\   \\\\\\\\\\\\        |
|       //          //   //         //   //             //                   ||         \\          \\        \\        \\             \\                 |
|      //          //   //         //   //             //                    ||          \\          \\        \\        \\             \\                |
|     //////////////   /////////////   ///////        //                     ||           \\\\\\\\\\\\\\        \\        \\             \\\\\\\          |
|    //               //    \\        //             //                      ||            \\                    \\        \\             \\              |
|   //               //      \\      //             //                       ||             \\                    \\        \\             \\             |
|  //               //        \\    //             //                        ||              \\                    \\        \\             \\            |
| //               //          \\  ////////////   ////////////          ||||||||||||          \\               \\\\\\\\\\\\   \\\\\\\\\\\\   \\\\\\\\\\\\ |
+=========================================================================================================================================================+)";

ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

AreaLink Pop(vector<AreaLink>& v) {
	AreaLink _tempLink;

	_tempLink = v.back();
	v.pop_back();

	return _tempLink;

}

AreaLink Dequeue(vector<AreaLink>& v) {
	AreaLink _tempLink;

	vector<AreaLink>::const_iterator _iter = v.begin();
	_tempLink = v.front();
	v.erase(_iter);

	return _tempLink;
}

AreaLink& LinkParentAndArea(AreaLink& link, const size_t& areaCount) {
	link.area = new Area();
	link.area->SetNumber(areaCount);
	link.area->SetPosition(link.parent->GetLat(), link.parent->GetLong());
	
	// link area to parent

	link.area->SetNeighbor(link.parentDirection, link.parent);
	// link parent and set position
	switch (link.parentDirection) {
	case CompassEnum::North:
		link.parent->SetNeighbor(CompassEnum::South, link.area);
		link.area->SetPosition(link.area->GetLat(), link.area->GetLong() - 1);
		break;
	case CompassEnum::South:
		link.parent->SetNeighbor(CompassEnum::North, link.area);
		link.area->SetPosition(link.area->GetLat(), link.area->GetLong() + 1);
		break;
	case CompassEnum::East:
		link.parent->SetNeighbor(CompassEnum::West, link.area);
		link.area->SetPosition(link.area->GetLat() - 1, link.area->GetLong());
		break;
	case CompassEnum::West:
		link.parent->SetNeighbor(CompassEnum::East, link.area);
		link.area->SetPosition(link.area->GetLat() +1, link.area->GetLong());
		break;
	}

	return link;
}

vector<AreaLink>& AddAreaLinks(vector<AreaLink>& f, const AreaLink& prev) {
	for (int i = 0; i < 4; i++) {
		AreaLink _newTemp;
		if (prev.area->GetNeighbor(i) == nullptr) {
			_newTemp.parent = prev.area;
			if (i % 2 == 0) {
				if (i > 0) {
					_newTemp.parentDirection = CompassEnum::West;
				}
				else {
					_newTemp.parentDirection = CompassEnum::South;
				}
			}
			else {
				if (i > 1) {
					_newTemp.parentDirection = CompassEnum::East;
				}
				else {
					_newTemp.parentDirection = CompassEnum::North;
				}
			}
			_newTemp.area = prev.area->GetNeighbor(i);

			// add to collection
			f.push_back(_newTemp);
		}
	}

	return f;
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
	string _output = format("{}[{}] {}\n", this->label, this->number, this->description);
	if(items.size() <= 0 ){
		_output += "You look around, but find nothing of use.\n";
	}
	else {
		_output += format("Has {} items:\n", this->items.size());
		for (int i = 0; i < this->items.size(); i++)
		{
			_output += this->items.at(i)->ToString();
		}	
	}
	if(items.size() <= 0) {
		_output += "A stillness fills the room, there is no one here.";
	}
	else{
		_output += format("Has {} NPCs: \n", this->npcs.size());
		for (int i = 0; i < this->npcs.size(); i++)
		{
			_output += this->npcs.at(i)->ToString();
		}
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

int Area::GetNumber() const {
	return number;
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
	/* New format:
		Area: [ Label ]
	 *----------[ ]----------*
	 |						 |
	 |						 |
	[ ]						[ ]
	 |						 |
	 |						 |
	 *----------[ ]----------*


	*/
	// out << format("       {}       \n       ^\n       |\n{} < - {} - > {}\n       |\n       v\n       {}\n",
	// 	(_area.neighbors[0] != nullptr) ? _area.neighbors[0]->label : "None",
	// 	(_area.neighbors[3] != nullptr) ? _area.neighbors[3]->label : "None",
	// 	_area.label,
	// 	(_area.neighbors[2] != nullptr) ? _area.neighbors[2]->label : "None",
	// 	(_area.neighbors[1] != nullptr) ? _area.neighbors[1]->label : "None");
	out << format("\n\tArea: [ {} ]\n *----------[{}]----------*\n",
			_area.number, _area.neighbors[0] != nullptr ? "O" : "0");
	out << " |                       |\n |                       |\n";
	out << format("[{}]                     [{}]\n",_area.neighbors[3] != nullptr ? "O" : "0",
				_area.neighbors[2] != nullptr ?  "O" : "0");
	out << " |                       |\n |                       |\n";
	out << format(" *----------[{}]----------*",_area.neighbors[1] != nullptr ?  "O" : "0");
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
// Adds a new area to the region.
// Placement is determined by random chance on
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
	
	//std::cout << "Init roll: " << dist(gen)%100; 
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
	size_t regionNum = rand() % (MAX_REGIONS - MIN_REGIONS) + MIN_REGIONS;
	//cout << "[GameWorld] RegionNum: "<< regionNum << endl;
	for (int i = 0; i < regionNum; i++) {
		// Steps for populating a region
		// create the region
		Region* _newRegion = new Region("Region " + to_string(i));
		// determine the number of areas
		size_t areaNum = rand() % (MAX_AREAS_IN_REGION - MIN_AREAS_IN_REGION) + MIN_AREAS_IN_REGION;
		// create an area
		//cout << "[GameWorld] Region " << i << " has "  << areaNum << " areas."<<  endl;
		
		this->PopulateRegion(*_newRegion, areaNum);

		world->AddRegion(*_newRegion);
		// Populate the Area
		
		// Add the area's neighbors to our vector
		/*for (int j = 0; j < 4; j++) {
			fringe.push_back(_newArea->GetNeighbor(j));
		}*/
	}

	this->currentArea = world->GetStartingArea();
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


void GameWorld::PopulateArea(Area& _area) {
	size_t npcInArea = rand() % NPCS_PER_AREA;
	for (int k = 0; k < npcInArea; k++) {
        
		_area.AddNPC(new NPC());
	}

	size_t itemInArea = rand() % ITEMS_PER_AREA;
	for (int l = 0; l < itemInArea; l++) {
		_area.AddItem(new Item());
	}
}

void GameWorld::PopulateRegion(Region& _region, const size_t& _areaNum){
	vector<AreaLink> fringe;
	// create root
	Area* root = new Area();
	root->SetNumber(0);
	root->SetPosition(0,0);
	for( int i = 0; i < _areaNum; i++) {
		// Create
		if(i == 0) {
			// Root Already created, initialize the AreaLinks
			for(int i = 0; i < 4; i++) {
				AreaLink _temp;
				if (root->GetNeighbor(i) == nullptr) {
					_temp.parent = root;
					if (i % 2 == 0) {
						if (i > 0) {
							_temp.parentDirection = CompassEnum::West;
						}
						else {
							_temp.parentDirection = CompassEnum::South;
						}
					}
					else {
						if (i > 1) {
							_temp.parentDirection = CompassEnum::East;
						}
						else {
							_temp.parentDirection = CompassEnum::North;
						}
					}
					_temp.area = root->GetNeighbor(i);

					fringe.push_back(_temp);
				}
			}

			_region.SetRoot(*root);
			_region.AddArea(*root);
		}else {
			AreaLink _tempLink;
			// rand to determine if DF or BF
			auto roll = dist(gen)%100;
			// If roll is less, depth first, if roll is more, breadth first
			float _df = -5/2*(i)+155/2;
			float _ratio = (float)i/(float)_areaNum;
			//std::cout << std::format("Ratio: {}, Ratio*Limit: {}", _ratio, _ratio*31) << std::endl;
			//std::cout << std::format("Raw Threshold: {}, Ratio Threshold: {}", _df, -5/2*(_ratio*31)+155/2) << std::endl;
			//std::cout << std::format("Roll: {} vs Threshold: {}", roll, _df) << std::endl;
			if(roll < _df) {
				//std::cout << "Popping area off fringe." << std::endl;
				_tempLink = Pop(fringe);
			} else {
				//std::cout << "Dequeuing area off fringe." << std::endl;
				_tempLink = Dequeue(fringe);
			}
			_tempLink = LinkParentAndArea(_tempLink, i);

			PopulateArea(*_tempLink.area);
			_region.AddArea(*_tempLink.area);

			fringe = AddAreaLinks(fringe, _tempLink);
		}
	}
}
#pragma endregion

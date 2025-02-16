#include "GameWorld.hpp"


ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

ostream& operator <<(ostream& out, const Area& _area) {
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
		(_area.neighbors[0] != nullptr) ? _area.neighbors[0]->number : -1,
		(_area.neighbors[3] != nullptr) ? _area.neighbors[3]->number : -1,
		_area.number,
		(_area.neighbors[2] != nullptr) ? _area.neighbors[2]->number : -1,
		(_area.neighbors[1] != nullptr) ? _area.neighbors[1]->number : -1);
	out << format("Position: ({}, {})\n", _area.posLat, _area.posLong);
	return out;
}

ostream& operator <<(ostream& out, const AreaLink& _link) {

	out << ((_link.area == nullptr) ? "nullptr" : to_string(_link.area->number));
	out << format(" connects to {}", _link.parent->number);
	out << " " << _link.parentDirection << "ward" << endl;
	return out;

}

ostream& operator<<(ostream& out, const Region& _region) {

	out << format("Region {} has {} areas", _region.number, _region.areaCount) << endl;

	return out;
}




vector<AreaLink>& AddAreaLinks(vector<AreaLink>& f, const AreaLink& prev) {
	// TO-DO: find a way to randomize this seleciton
	for (int i = 0; i < 4; i++) {
		AreaLink _newTemp;
		if (prev.area->neighbors[i] == nullptr) {
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
			_newTemp.area = prev.area->neighbors[i];

			// add to collection
			f.push_back(_newTemp);
		}
	}

	return f;
}

void Region::InitializeRegion() {
	vector<AreaLink> frontier;
	// Initialize the root area for the region
	this->root = new Area();
	this->root->number = 0;
	this->root->posLat = 0;
	this->root->posLong = 0;
	this->areas[0] = this->root;
	int areaCount = 1;
	// Create AreaLinks for all neighboring areas
	for (int i = 0; i < 4; i++) {
		AreaLink _temp;
		if (this->root->neighbors[i] == nullptr) {
			_temp.parent = this->root;
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
			_temp.area = this->root->neighbors[i];

			frontier.push_back(_temp);
		}
	}

	// keep adding areas to the region until we are done.
	while (areaCount <= REGION_AREA_NUM) {
		float threshold = (40 / -areaCount) + 70;

		AreaLink _tempLink;
		// depth first
		if (rand() % 100 > threshold) {
			//cout << "Popping with threshold: " << threshold << endl;
			_tempLink = Pop(frontier);

		}// breadth first
		else {
			//cout << "Dequeuing with threshold: " << threshold << endl;
			_tempLink = Dequeue(frontier);
		}

		// link parent to area and area to parent
		_tempLink = LinkParentAndArea(_tempLink, areaCount);

		this->areas[areaCount] = _tempLink.area;

		// add new possible areas to the collection
		frontier = AddAreaLinks(frontier, _tempLink);

		areaCount++;
	}
}

int TraverseWorld(Region* region) {
	int exitCode = -1;
	Area* currentArea = region->root;
	while (exitCode < 0) {
		string _input;
		cout << "You look aound and see a number on the wall: \"" << currentArea->number << "\"\n";
		cout << (*currentArea);
		cout << "Input command: ";
		cin >> _input;
		try {
			if (currentArea != nullptr) {
				if (_input == "look") {
					cout << "You look aound and see a number on the wall: \"" << currentArea->number << "\"\n";
					cout << (*currentArea);
				}
				else if (_input == "move") {
					int _areaNum = -1;
					cout << (*currentArea);
					cout << "Input area to move to: ";
					cin >> _areaNum;

					for (int i = 0; i < 4; i++) {
						if (currentArea->neighbors[i] != nullptr && currentArea->neighbors[i]->number == _areaNum) {
							currentArea = currentArea->neighbors[i];
							break;
						}
					}
				}
				else if (_input == "exit") {
					exitCode = 0;
				}
				else {
					cout << "Command: \"" << _input << "\" is not a recognized command." << endl;
				}
			}

		}
		catch (...) {
			// invalid command
		}

	}

	return exitCode;
}

#pragma region Best-first Map Generation
/*
* Map Creation
*/
/*int mapSize = -1;
cout << "Input size of the map: ";
cin >> mapSize;
Area* root = new Area();
root->number = 0;
for (int i = 0; i < 4; i++)
{
	root->neighbors[i] = nullptr;
}
vector<Area*> frontier;*/

//int count = 1;
//Area* _temp = root;
//int next = 0;
//bool resetNext = false;

//while (count <= mapSize) {
//	if (resetNext) {
//		next = 0;
//		resetNext = false;
//	}

//	if (_temp->neighbors[next] == nullptr) {
//		_temp->neighbors[next] = new Area();
//		_temp->neighbors[next]->number = count;
//		if (next % 2 == 0) {
//			_temp->neighbors[next]->neighbors[next + 1] = _temp;
//		}
//		else {
//			_temp->neighbors[next]->neighbors[next - 1] = _temp;
//		}

//		count++;
//	}


//	// Fifty fifty if it stays at the current area, or goes one level deeper
//	if (rand() % 10 > 4 || next >= 3)
//	{
//		_temp = _temp->neighbors[next];
//		resetNext = true;
//	}

//	next++;
//} // map created
#pragma endregion
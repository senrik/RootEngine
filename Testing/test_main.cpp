#include <vector>
#include <random>
#include <iostream>
#include <format>
#include <string>
using namespace std;

constexpr size_t REGION_AREA_NUM = 15;

enum CompassEnum {

	North = 0,
	South = 1,
	East = 2,
	West = 3,
};

ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

struct Area {
	int number;
	Area* neighbors[4];
	int posLat, posLong;
	friend ostream& operator<<(ostream&, const Area&);
};

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
	return out;
}

struct AreaLink {
	Area* parent, *area;
	CompassEnum parentDirection;
	

	friend ostream& operator<<(ostream&, const AreaLink&);
};

ostream& operator <<(ostream& out, const AreaLink& _link) {
	
	out << ((_link.area == nullptr) ? "nullptr" : to_string(_link.area->number));
	out << format(" connects to {}", _link.parent->number);
	out << " " << _link.parentDirection << "ward" << endl;
	return out;

}

struct Region {
	int number;
	int areaCount;
	Area* areas[REGION_AREA_NUM];
	Area* root, northernBorder, southernBorder, easternBorder, westernBorder;

	friend ostream& operator<<(ostream&, const Region&);
};

ostream& operator<<(ostream& out, const Region& _region) {

	out << format("Region {} has {} areas", _region.number, _region.areaCount) << endl;

	return out;
}

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

vector<AreaLink>& AddAreaLinks(vector<AreaLink>&, const AreaLink&);

int main(int argc, char* argv[]) {

#pragma region Vector Test
	vector<int> testVector;
	// The "back" is the end of the vector
	testVector.push_back(3);
	testVector.push_back(4);
	testVector.push_back(5);
	testVector.push_back(6);
	testVector.push_back(7);

	for (int i = 0; i < testVector.size(); i++)
	{
		cout << "Value at " << i << ": " << testVector[i] << endl;
	}
	cout << "Popping like a Stack" << endl;
	// this is used to treat the vector like a stack (popping)
	while(testVector.size() > 0)
	{
		cout << "Popping: " << testVector.back() <<endl;
		testVector.pop_back();
	}

	// Refill the vector
	testVector.push_back(3);
	testVector.push_back(4);
	testVector.push_back(5);
	testVector.push_back(6);
	testVector.push_back(7);
	// dequeuing
	vector<int>::const_iterator ptr = testVector.begin();
	cout << "Popping like a Queue" << endl;
	while (testVector.size() > 0) {
		cout << "Popping: " << testVector.front() << endl;
		testVector.erase(ptr);
		ptr = testVector.begin();
	}
#pragma endregion

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

#pragma region DFS/BFS Map Generation
	/*
	* ===================    Map Creation    ===================
	*/
	Region* test_region = new Region();
	// Holds possible areas we have not initialized yet.
	vector<AreaLink> frontier;
	// Initialize the root area for the region
	test_region->root = new Area();
	test_region->root->number = 0;
	test_region->root->posLat = 0;
	test_region->root->posLong = 0;
	int areaCount = 1;
	for (int i = 0; i < 4; i++) {
		AreaLink _temp;
		if (test_region->root->neighbors[i] == nullptr) {
			_temp.parent = test_region->root;
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
			_temp.area = test_region->root->neighbors[i];

			frontier.push_back(_temp);
		}
	}

	// keep adding areas to the region until we are done.
	while (areaCount <= REGION_AREA_NUM) {
		float threshold = (40 / -areaCount) + 70;

		AreaLink _tempLink;
		// depth first
		if (rand() % 100 > threshold) {
			cout << "Popping with threshold: " << threshold << endl;
			_tempLink = Pop(frontier);

		}// breadth first
		else {
			cout << "Dequeuing with threshold: " << threshold << endl;
			_tempLink = Dequeue(frontier);
		}
		
		// link parent to area and area to parent
		_tempLink = LinkParentAndArea(_tempLink, areaCount);

		// add new possible areas to the collection
		frontier = AddAreaLinks(frontier, _tempLink);

		areaCount++;
	}

#pragma endregion

	/*       [0]
	*         ^
	*         |
	* [3] < - O - > [2]
	*         |
	*         v
	*        [1]
	*
	*/

#pragma region Map Traversal
	/*
	* Create a way to "traverse" the map
	*/
	int exitCode = -1;
	Area* currentArea = test_region->root;
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
				else if(_input == "exit") {
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
#pragma endregion

	return exitCode;
}

AreaLink& LinkParentAndArea(AreaLink& link, const size_t& areaCount) {
	link.area = new Area();
	link.area->number = areaCount;
	// link area to parent
	link.area->neighbors[link.parentDirection] = link.parent;
	// link parent 
	switch (link.parentDirection) {
	case CompassEnum::North:
		link.parent->neighbors[CompassEnum::South] = link.area;
		break;
	case CompassEnum::South:
		link.parent->neighbors[CompassEnum::North] = link.area;
		break;
	case CompassEnum::East:
		link.parent->neighbors[CompassEnum::West] = link.area;
		break;
	case CompassEnum::West:
		link.parent->neighbors[CompassEnum::East] = link.area;
		break;
	}

	return link;
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
#include <vector>
#include <random>
#include <iostream>
#include <format>
using namespace std;

struct Area {
	int number;
	Area* neighbors[4];
};

enum CompassEnum {
	None = 0,
	North = 1,
	South = 2,
	East = 3,
	West = 4,
};

ostream& operator <<(ostream& out, Area _area) {
	/*      0
	*       ^
	*       |
	* -3 < - O - > -2
	*       |
	*       v
	*       1
	* 
	*/
	out << format("       {}       \n       ^\n       |\n{} < - {} - > {}\n       |\n       v\n       {}\n",
		(_area.neighbors[0] != nullptr) ? _area.neighbors[0]->number : -1,
		(_area.neighbors[1] != nullptr) ? _area.neighbors[1]->number : -1,
		_area.number,
		(_area.neighbors[2] != nullptr) ? _area.neighbors[2]->number : -1,
		(_area.neighbors[3] != nullptr) ? _area.neighbors[3]->number : -1);
	return out;
}

ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "None", "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

int main(int argc, char* argv[]) {

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
	// this is used to treat the vector like a stack
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
	
	vector<int>::const_iterator ptr = testVector.begin();
	cout << "Popping like a Queue" << endl;
	while (testVector.size() > 0) {
		cout << "Popping: " << testVector.front() << endl;
		testVector.erase(ptr);
		ptr = testVector.begin();
	}
	int mapSize = -1;
	cout << "Input size of the map: ";
	cin >> mapSize;
	Area* root = new Area();
	root->number = 0;
	cout << *root;
	for (int i = 0; i < 4; i++)
	{
		root->neighbors[i] = nullptr;
	}
	vector<Area*> frontier;
	int count = 1;
	Area* _temp = root;
	int next = 0;
	bool resetNext = false;
	while (count <= mapSize) {
		if (resetNext) {
			next = 0;
			resetNext = false;
		}
		/*      0
		*       ^
		*       |
		* 3 < - O - > 2
		*       |
		*       v
		*       1
		* North and East are + 1, South and West are -1
		*/
		if (_temp->neighbors[next] == nullptr) {
			cout << "Linking " << (CompassEnum)(next + 1) << endl;
			_temp->neighbors[next] = new Area();
			_temp->neighbors[next]->number = count;
			if (next % 2 == 0) {
				_temp->neighbors[next]->neighbors[next + 1] = _temp;
			}
			else {
				_temp->neighbors[next]->neighbors[next - 1] = _temp;
			}

			count++;
		}


		// Fifty fifty if it stays at the current area, or goes one level deeper
		if (rand() % 10 > 4)
		{
			_temp = _temp->neighbors[next];
			cout << "Moving " << (CompassEnum)(next + 1) << endl;
			resetNext = true;
		}
		next++;

		//while (_temp->neighbors[next] != nullptr) {
		//	// This has a tendency to get stuck here, find a better solution
		//	// Just have them be initialized sequencially, and have the random chance to move?
		//	int next = rand() % 4;
		//	
		//}
				/*switch (next)
		{
		case 0:
			_temp->neighbors[next]->neighbors[next + 1] = _temp;
			break;
		case 1:
			_temp->neighbors[next]->neighbors[next - 1] = _temp;
			break;
		case 2:
			_temp->neighbors[next]->neighbors[next + 1] = _temp;
			break;
		case 3:
			_temp->neighbors[next]->neighbors[next - 1] = _temp;
			break;
		}*/
		
		
		
	}
	return 0;
}
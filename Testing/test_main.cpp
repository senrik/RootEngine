#include <vector>
#include <random>
#include <iostream>
#include <format>
#include <string>
using namespace std;



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
	// Holds possible areas we have not initialized yet.
	

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
#pragma region Test Random
	cout << "Testing Random..." << endl;
	bool oneRolled = false, twoRolled = false, threeRolled = false, zeroRolled = false;
	int rollCount = 0;
	while (!oneRolled || !twoRolled || !threeRolled || !zeroRolled) {
		int roll = rand() % 4;
		switch (roll) {
		case 0:
			zeroRolled = true;
			cout << "Zero Rolled on roll: " << rollCount << endl;
			break;
		case 1:
			oneRolled = true;
			cout << "One Rolled on roll: " << rollCount << endl;
			break;
		case 2:
			twoRolled = true;
			cout << "Two Rolled on roll: " << rollCount << endl;
			break;
		case 3:
			threeRolled = true;
			cout << "Three Rolled on roll: " << rollCount << endl;
			break;
		}
		rollCount++;
	}
	cout << "Random Finished after " << rollCount << " rolls." << endl;
#pragma endregion


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
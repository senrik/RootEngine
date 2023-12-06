#include <vector>
#include <iostream>
using namespace std;

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
	
	return 0;
}
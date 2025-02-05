#include <iostream>
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
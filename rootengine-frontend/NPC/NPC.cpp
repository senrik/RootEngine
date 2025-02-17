#include "NPC.hpp"

NPC::NPC()
{
    this->hostile = false;
	this->health = 100;
	this->attack = 10;
	this->defense = 10;
	this->speed = 10;
	this->label = "NPC";
	this->responseDialogue = "Hello!";

	
}
void NPC::GenerateLootTable()
{
	for (int i = 0; i < 4; i++)
	{
		// Roll has to be less than the population chance
		float _lootRoll = rand() % 100;
		//
		float _chance = pow(0.5, (i + 1) - 7.32);
		if (_lootRoll < _chance)
		{			
			auto _item = new Item();
			_item->GenerateEntity();
			//Call generate entity
			this->npcLoot.items.push_back(new Item());
			
		}
		else {
			break;
		}
	}

}

std::string Loot::ToString() {
	std::string _output = "";
	_output += "LootTable:\n";
	
	

	return _output;
}
bool NPC::IsHostile() {
	return hostile;
}

std::string NPC::Response() {
	return responseDialogue;
}

Loot NPC::GetLoot() {
	return npcLoot;
}

NPC::~NPC()
{

}

std::string NPC::ToString() {
	return "I am an NPC, this is a placeholder, doot doot.";
}

void NPC::GenerateEntity()
{
	// Populate Loot Table
	// The chances of items being in the loot table should decrease with every item added
	// 1 - 80%: rand() % 100 > 20 = 100 - 80/i+1 @ 0
	// 2 - 40%: rand() % 100 > 60 = 100 - 80/i+1 @ 1 
	// 3 - 20%: rand() % 100 > 80 = 100 - 80/i+1 @ 2
	// 4 - 10%: rand() % 100 > 90 = 100 - 80/i+1 @ 3
	GenerateLootTable();
	this->_type = EntityType::NPC_Friendly;
}

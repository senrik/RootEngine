#include "NPC.hpp"

NPC::NPC()
{
	this->data = new NPCData();
    this->data->hostile = false;
	this->data->health = 100;
	this->data->attack = 10;
	this->data->defense = 10;
	this->data->speed = 10;
	this->label = "NPC";
	this->data->responseDialogue = "Hello!";
	this->rngSeed = std::chrono::high_resolution_clock::now();
}

NPC::~NPC() {
	delete this->data;
}

void NPC::GenerateLootTable(std::fstream& fs, const std::string& dbName){
	this->data->lootCount = 0;
	fs.open(dbName, std::ios::in | std::ios::binary);
	fs.seekg(0, std::ios::end);
	int dataSize = fs.tellg();
	int dataCount = dataSize/sizeof(ItemData);
	for (int i = 0; i < 4; i++)
	{
		// Roll has to be less than the population chance
		float _lootRoll = rand() % 100;
		//
		float _chance = pow(0.5, (i + 1) - 7.32);
		
		if (_lootRoll < _chance)
		{			
			auto _item = new Item();
			
			fs.seekg((rand()%dataCount)*sizeof(ItemData), std::ios::beg);
			_item->DeserializeEntity(fs);
			//Call generate entity
			this->npcLoot.items.push_back(_item);
			this->data->rawLoot[this->data->lootCount] = _item;
			this->data->lootCount++;
		}
		else {
			break;
		}
		
	}
	fs.close();

}

std::string Loot::ToString() {
	std::string _output = "";
	_output += "LootTable:\n";
	return _output;
}

EntityType NPC::GetType() {
	return this->data->_type;
}

std::string NPC::GetLabel() {
	return this->data->label;
}




bool NPC::IsHostile() {
	return data->hostile;
}

std::string NPC::Response() {
	return data->responseDialogue;
}

Loot NPC::GetLoot() {
	return npcLoot;
}

std::string NPC::ToString() {
    std::string _output = "";
    _output += format("Name: {}\n", this->label);
    _output += this->data->health > 0 ? "|\tHealth:" + std::to_string(this->data->health) + "\n" : "";
    _output += this->data->attack > 0 ? "|\tAttack:" + std::to_string(this->data->attack) + "\n" : "";
    _output += this->data->defense > 0 ? "|\tDefense:" + std::to_string(this->data->defense) + "\n" : "";
    _output += this->data->speed > 0 ? "|\tSpeed:" + std::to_string(this->data->speed) + "\n" : "";
    
	std::string _lootOutput = "";
    for(int i = 0; i < 4; i++) {
        if(this->data->rawLoot[i] != nullptr) {
            _lootOutput += this->data->rawLoot[i]->ToString() + "\n";
        }
    }
	if(_lootOutput.length() > 0) {
		_output += "Loot:\n";
		_output += _lootOutput;
	}
    return _output;
}

void NPC::GenerateEntity()
{
	// Populate Loot Table
	// The chances of items being in the loot table should decrease with every item added
	// 1 - 80%: rand() % 100 > 20 = 100 - 80/i+1 @ 0
	// 2 - 40%: rand() % 100 > 60 = 100 - 80/i+1 @ 1 
	// 3 - 20%: rand() % 100 > 80 = 100 - 80/i+1 @ 2
	// 4 - 10%: rand() % 100 > 90 = 100 - 80/i+1 @ 3
	int _type = ((rand()%2)+6);
	this->data->_type = (EntityType)_type;
	this->data->id = ID;
	ID++;

	switch (this->data->_type)
	{
	case EntityType::NPC_Friendly:
		this->label = "Merchant";
		this->data->health = 100;
		this->data->attack = 10;
		this->data->defense = 5;
		this->data->speed = 5;
		break;
	case EntityType::NPC_Enemy:
		this->label = "Goblin";
		this->data->health = 20;
		this->data->attack = 10;
		this->data->defense = 10;
		this->data->speed = 30;
		break;
	default:
		
		break;
	}
	std::copy(this->label.begin(), this->label.end(), this->data->label);

}

void NPC::SerializeEntity(std::fstream& out) {
	// TODO
	try{
		out.write(reinterpret_cast<char*>(this->data), sizeof(NPCData));
	} catch(std::exception e){

	}
}

void NPC::DeserializeEntity(std::fstream& in) {
		char* buffer = new char[sizeof(NPCData)];

		in.read(buffer, sizeof(NPCData));

		this->data = reinterpret_cast<NPCData*>(buffer);

		this->label =this->data->label;
		// populate loot
		for(int i =0; i < 4; i++) {
			if(this->data->rawLoot != nullptr) {
				this->npcLoot.items.push_back((Entity*)this->data->rawLoot[i]);
			}
		}
}

void NPC::SetData(const NPCData& other) {
	*(this->data) = other;
	this->label = this->data->label;

	for(int i =0; i < 4; i++) {
		if(this->data->rawLoot != nullptr) {
			this->npcLoot.items.push_back((Entity*)this->data->rawLoot[i]);
		}
	}
}
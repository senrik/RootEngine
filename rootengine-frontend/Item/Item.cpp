#include "Item.hpp"

Item::Item() {
	this->data = new ItemData();
	this->data->_type = EntityType::None;
	this->data->stats.modifiers[Statistics::HealthStat] = 0;
	this->data->stats.modifiers[Statistics::AttackStat] = 0;
	this->data->stats.modifiers[Statistics::DefenseStat] = 0;
	this->data->stats.modifiers[Statistics::SpeedStat] = 0;
	this->label = "Item";
	this->rngSeed = std::chrono::high_resolution_clock::now();
}


Item::Item(const EntityType& _type, const StatModifiers& _mods) {
	this->label = "Item";
	this->data->_type = _type;
	this->data->stats.modifiers[Statistics::HealthStat] = _mods.modifiers[Statistics::HealthStat];
	this->data->stats.modifiers[Statistics::AttackStat] = _mods.modifiers[Statistics::AttackStat];
	this->data->stats.modifiers[Statistics::DefenseStat] = _mods.modifiers[Statistics::DefenseStat];
	this->data->stats.modifiers[Statistics::SpeedStat] = _mods.modifiers[Statistics::SpeedStat];
}

Item::~Item() {
	delete this->data;
}

StatModifiers Item::Use() {
	StatModifiers _stats;
	_stats.modifiers[Statistics::HealthStat] = this->data->stats.modifiers[Statistics::HealthStat];
	_stats.modifiers[Statistics::AttackStat] = this->data->stats.modifiers[Statistics::AttackStat];
	_stats.modifiers[Statistics::DefenseStat] = this->data->stats.modifiers[Statistics::DefenseStat];
	_stats.modifiers[Statistics::SpeedStat] = this->data->stats.modifiers[Statistics::SpeedStat];

	return _stats;
}


std::string Item::ToString(){
	std::string _output = "";
	_output+= "Name: " +this->label + "\n";
	switch (this->data->_type) {
	case EntityType::None:
		_output += "|\tType: None\n";
		break;
	case EntityType::Item_Weapon:
		_output += "|\tType: Weapon\n";
		break;
	case EntityType::Item_Armor:
		_output += "|\tType: Armor\n";
		break;
	case EntityType::Item_Consumable:
		_output += "|\tType: Consumable\n";
		break;
	case EntityType::Item_Accessory:
		_output += "|\tType: Accessory\n";
		break;
	}	
	_output += (this->data->stats.modifiers[Statistics::HealthStat] > 0) ? "|\tHealth Modifier: " + std::to_string(this->data->stats.modifiers[Statistics::HealthStat]) + "\n" : "";
	_output += (this->data->stats.modifiers[Statistics::AttackStat] > 0) ? "|\tAttack Modifier: " + std::to_string(this->data->stats.modifiers[Statistics::AttackStat]) + "\n" : "";
	_output += (this->data->stats.modifiers[Statistics::DefenseStat] > 0) ? "|\tDefense Modifier: " + std::to_string(this->data->stats.modifiers[Statistics::DefenseStat]) + "\n" : "";
	_output += (this->data->stats.modifiers[Statistics::SpeedStat] > 0) ? "|\tSpeed Modifier: " + std::to_string(this->data->stats.modifiers[Statistics::SpeedStat]) + "\n" : "";
	
	return _output;
}

EntityType Item::GetType() {
	return this->data->_type;
}

std::string Item::GetLabel() {
	return this->data->label;
}



void Item::GenerateEntity() {
	std::uniform_int_distribution<int> type_dist(2, 5);
	gen.seed((std::chrono::high_resolution_clock::now() - this->rngSeed).count());
	int _type = type_dist(gen);
	this->data->_type = (EntityType)_type;

	StatModifiers _stats;
	std::uniform_int_distribution<int> stat_dist(10, 20);
	switch(this->data->_type){
		case EntityType::Item_Weapon:
			_stats.modifiers[Statistics::HealthStat] = 0;
			_stats.modifiers[Statistics::AttackStat] = stat_dist(gen);
			_stats.modifiers[Statistics::DefenseStat] = 0;
			_stats.modifiers[Statistics::SpeedStat] = 0;
			this->label = "Sword";
			break;
		case EntityType::Item_Armor:
			_stats.modifiers[Statistics::HealthStat] = 0;
			_stats.modifiers[Statistics::AttackStat] = 0;
			_stats.modifiers[Statistics::DefenseStat] = stat_dist(gen);
			_stats.modifiers[Statistics::SpeedStat] = 0;
			this->label = "Armor";
			break;
		case EntityType::Item_Consumable:
			_stats.modifiers[Statistics::HealthStat] = stat_dist(gen);
			_stats.modifiers[Statistics::AttackStat] = 0;
			_stats.modifiers[Statistics::DefenseStat] = 0;
			_stats.modifiers[Statistics::SpeedStat] = 0;
			this->label = "Potion";
			break;
		case EntityType::Item_Accessory:
			_stats.modifiers[Statistics::HealthStat] = 0;
			_stats.modifiers[Statistics::AttackStat] = 0;
			_stats.modifiers[Statistics::DefenseStat] = 0;
			_stats.modifiers[Statistics::SpeedStat] = stat_dist(gen);
			this->label = "Bangle";
			break;
	}
	this->data->stats = _stats;
	std::copy(this->label.begin(), this->label.end(), this->data->label);
	this->data->id = ID;
	ID++;
}

void Item::SerializeEntity(std::fstream& out){
	//TODO

	try {
		out.write(reinterpret_cast<char*>(this->data), sizeof(ItemData));
	} catch (std::exception e) {
		// Silent catch
	}
}

void Item::DeserializeEntity(std::fstream& in) {
	size_t blockSize = sizeof(ItemData);

	char* buffer =  new char[blockSize];
	in.read(buffer, blockSize);

	this->data = reinterpret_cast<ItemData*>(buffer);

	this->label = this->data->label;
}

void Item::SetData(const ItemData& other) {
	*(this->data) = other;
}

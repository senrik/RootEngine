#include "Item.hpp"

Item::Item() {
	this->_type = EntityType::None;
	this->stats.modifiers[Statistics::Health] = 0;
	this->stats.modifiers[Statistics::Attack] = 0;
	this->stats.modifiers[Statistics::Defense] = 0;
	this->stats.modifiers[Statistics::Speed] = 0;
	this->label = "Item";
}


Item::Item(const EntityType& _type, const StatModifiers& _mods) {
	this->label = "Item";
	this->_type = _type;
	this->stats.modifiers[Statistics::Health] = _mods.modifiers[Statistics::Health];
	this->stats.modifiers[Statistics::Attack] = _mods.modifiers[Statistics::Attack];
	this->stats.modifiers[Statistics::Defense] = _mods.modifiers[Statistics::Defense];
	this->stats.modifiers[Statistics::Speed] = _mods.modifiers[Statistics::Speed];
}

StatModifiers Item::Use() {
	StatModifiers _stats;
	_stats.modifiers[Statistics::Health] = this->stats.modifiers[Statistics::Health];
	_stats.modifiers[Statistics::Attack] = this->stats.modifiers[Statistics::Attack];
	_stats.modifiers[Statistics::Defense] = this->stats.modifiers[Statistics::Defense];
	_stats.modifiers[Statistics::Speed] = this->stats.modifiers[Statistics::Speed];

	return _stats;
}


std::string Item::ToString(){
	std::string _output = "";
	_output+= "Name: " +this->label + "\n";
	switch (this->_type) {
	case 0:
		_output += "|\tType: None\n";
		break;
	case 1:
		_output += "|\tType: Weapon\n";
		break;
	case 2:
		_output += "|\tType: Armor\n";
		break;
	case 3:
		_output += "|\tType: Consumable\n";
		break;
	}
	_output += "|\tHealth Modifier: " + std::to_string(this->stats.modifiers[Statistics::Health]) + "\n";
	_output += "|\tAttack Modifier: " + std::to_string(this->stats.modifiers[Statistics::Attack]) + "\n";
	_output += "|\tDefense Modifier: " + std::to_string(this->stats.modifiers[Statistics::Defense]) + "\n";
	_output += "|\tSpeed Modifier: " + std::to_string(this->stats.modifiers[Statistics::Speed]) + "\n";
	
	return _output;
}
void Item::GenerateEntity() {
	int _type = (rand() % (3)) + 1;
	StatModifiers _stats;
	_stats.modifiers[Statistics::Health] = rand() % 20 + 20;
	_stats.modifiers[Statistics::Attack] = rand() % 5 + 5;
	_stats.modifiers[Statistics::Defense] = rand() % 5 + 5;
	_stats.modifiers[Statistics::Speed] = rand() % 5 + 5;
	this->stats = _stats;
}
#include <Player.hpp>

Player::Player(){
    this->data = new PlayerData();
    this->data->stats[Statistics::HealthStat] = 10;
    this->data->stats[Statistics::AttackStat] = 10;
    this->data->stats[Statistics::DefenseStat] = 10;
    this->data->stats[Statistics::SpeedStat] = 10;
    this->data->invCount = 0;
}

Player::~Player() {
    delete this->data;
}

void Player::GenerateEntity() {
    this->data->_type = EntityType::Player_Entity;
}

std::string Player::ToString()
{
    std::string output = "Stats:\n";
    output += std::format("|\tHealth: {}\n", this->data->stats[Statistics::HealthStat]);
    output += std::format("|\tAttack: {}\n", this->data->stats[Statistics::AttackStat]);
    output += std::format("|\tDefense: {}\n", this->data->stats[Statistics::DefenseStat]);
    output += std::format("|\tSpeed: {}\n", this->data->stats[Statistics::SpeedStat]);
    return output;
}

EntityType Player::GetType() {
	return this->data->_type;
}
std::string Player::GetLabel() {
	return this->data->label;
}

void Player::SerializeEntity(std::fstream& out) {
    try {
        out.write(reinterpret_cast<char*>(this->data), sizeof(PlayerData));
    }catch(std::exception e) {

    }
}
void Player::DeserializeEntity(std::fstream& in) {
    try {
        char* buffer = new char[sizeof(PlayerData)];
        in.read(buffer, sizeof(PlayerData));
        this->data = reinterpret_cast<PlayerData*>(buffer);
    } catch(std::exception e){

    }
}

void Player::Pickup(const Item& _item){
    // Add item to inventory
    if(this->data->invCount < 7){
        this->data->inventory[this->data->invCount] = const_cast<Item*>(&_item);
        this->data->invCount++;
    } else {
        // add command to update queue to ask player to replace item
    }
    
}
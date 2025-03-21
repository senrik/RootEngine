#ifndef PLAYER_H
#define PLAYER_H
#include <Entity.hpp>
#include <Item.hpp>
#include <vector>


struct PlayerData : public EntityData {
    size_t invCount;
    Item* inventory[8];
    int stats[4];
    int currentHealth;
};


// Stats, inventory, actions
// Not a singleton to account for multiple players (network)
class Player : public Entity {
    public:
        Player();
        Player(const Player&);
        ~Player();
        void GenerateEntity() override;
        void SerializeEntity(std::fstream&) override;
        std::string ToString() override;
        void Pickup(const Item&);
        EntityType GetType() override;
        std::string GetLabel() override;
        inline int GetID() override { return this->data->id; }
        void DeserializeEntity(std::fstream&) override;
    private:
        PlayerData* data;
};
#endif
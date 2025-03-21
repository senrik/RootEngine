#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
#include <format>
#include <fstream>
#include <random>
#include <chrono>
enum EntityType {
	None = 0,
    Player_Entity = 1,
	Item_Weapon = 2,
	Item_Armor = 3,
	Item_Consumable = 4,
    Item_Accessory = 5,
    NPC_Friendly = 6,
    NPC_Enemy = 7,
};

enum Statistics {
    NoneStat = 4,
    HealthStat = 0,
    AttackStat = 1,
    DefenseStat = 2,
    SpeedStat = 3
};
constexpr int LABEL_LIMIT = 24;

struct EntityData {
    // Primary key for database
    unsigned int id;
    EntityType _type;
    char label[LABEL_LIMIT];
};

class Entity {
    public:
        virtual std::string ToString() = 0;
        virtual void GenerateEntity() = 0;
        virtual void SerializeEntity(std::fstream&) = 0;
        virtual EntityType GetType() = 0;
        virtual std::string GetLabel() = 0;
        virtual void DeserializeEntity(std::fstream&) = 0;
        virtual int GetID() = 0;
    protected:
        static unsigned int ID;
        static std::default_random_engine gen;
        std::chrono::time_point<std::chrono::system_clock> rngSeed;
        std::string label;
    private:
        EntityData* data;
};

#endif
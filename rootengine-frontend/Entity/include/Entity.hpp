#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
enum EntityType {
	None = 0,
    Player = 1,
	Item_Weapon = 2,
	Item_Armor = 3,
	Item_Consumable = 4,
    NPC_Friendly = 5,
    NPC_Enemy = 6,
};

enum Statistics {
    None = 4,
    Health = 0,
    Attack = 1,
    Defense = 2,
    Speed = 3
};

class Entity {
    public:
        virtual std::string ToString() = 0;
        virtual void GenerateEntity() = 0;
        inline EntityType GetType() { return _type; };
    protected:
        
        static unsigned int ID;
        // Primary key for database
        unsigned int id;
        EntityType _type = EntityType::None;
};
#endif
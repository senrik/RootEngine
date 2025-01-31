#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
enum EntityType {
	None = 0,
	Item_Weapon = 1,
	Item_Armor = 2,
	Item_Consumable = 3,
    NPC_Friendly = 4,
    NPC_Enemy = 5,
};

class Entity {
    public:
        virtual ~Entity() = 0;
        virtual std::string ToString() = 0;
        virtual void GenerateEntity() = 0;
        virtual EntityType GetType() = 0;
    protected:
        
        static unsigned int ID;
        // Primary key for database
        unsigned int id;
        EntityType _type = EntityType::None;
};
#endif
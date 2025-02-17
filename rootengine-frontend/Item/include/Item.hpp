#ifndef ITEM_H
#define ITEM_H
#include <Entity.hpp>


// 0- healthMod, 1- attackMod, 2- defenseMod, 3- speedMod
struct StatModifiers {
	unsigned char modifiers[4];
};

class Item : public Entity{
public:
	Item();
	Item(const Item&);
	Item(const EntityType&, const StatModifiers&);
	~Item();
	StatModifiers Use();
	void GenerateEntity() override;
    std::string ToString() override;

private:
	std::string label;
	StatModifiers stats;
};
#endif
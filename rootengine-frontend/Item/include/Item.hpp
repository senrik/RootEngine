#ifndef ITEM_H
#define ITEM_H
#include <Entity.hpp>


// 0- healthMod, 1- attackMod, 2- defenseMod, 3- speedMod
struct StatModifiers {
	unsigned char modifiers[4];
};
// Used for serialization of the item
struct ItemData : public EntityData {
	StatModifiers stats;
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
	void SerializeEntity(std::fstream&) override;
	EntityType GetType() override;
	std::string GetLabel() override;
	void DeserializeEntity(std::fstream&) override;
	inline int GetID() override { return this->data->id; }
	void SetData(const ItemData&);
	ItemData GetData() {return *(this->data);}
protected:
	ItemData* data;
};
#endif
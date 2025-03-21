#ifndef NPC_H
#define NPC_H
#include <Entity.hpp>
#include <Item.hpp>
#include <vector>
#include <cmath>

struct Loot {
	std::vector<Entity*> items;
	std::string ToString();
};

struct NPCData : public EntityData {
	bool hostile;
	size_t health;
	size_t attack;
	size_t defense;
	size_t speed;
	std::string responseDialogue;
	size_t lootCount;
	Item* rawLoot[4]; 
};

class NPC : public Entity {
public:
    void GenerateLootTable(std::fstream&, const std::string&);
	NPC();
	bool IsHostile();
	std::string Response();
	Loot GetLoot();
	~NPC();
	std::string ToString() override;
	void GenerateEntity() override;
	void SerializeEntity(std::fstream&) override;
	EntityType GetType() override;
	std::string GetLabel() override;
	void DeserializeEntity(std::fstream&) override;
	void SetData(const NPCData&);
	inline int GetID() override { return this->data->id; }
	NPCData GetData() {return *(this->data);}
protected:
	NPCData* data;
	Loot npcLoot;
};

#endif
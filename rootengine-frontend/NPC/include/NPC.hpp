#ifndef NPC_H
#define NPC_H
#include <Entity.hpp>
#include <Item.hpp>
#include <vector>
#include <cmath>

class Loot {
	public:
		std::vector<Entity*> items;
		std::string ToString();
};

class NPC : public Entity {
public:
    void GenerateLootTable();
	NPC();
	bool IsHostile();
	std::string Response();
	Loot GetLoot();
	~NPC();
	std::string ToString() override;
	void GenerateEntity() override;
private:
	bool hostile;
	size_t health;
	size_t attack;
	size_t defense;
	size_t speed;
	std::string responseDialogue;
	std::string label;
	Loot npcLoot;
};

#endif
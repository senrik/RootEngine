#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <format>
#include <NPC.hpp>
#include <Item.hpp>
#include <random>
using namespace std;
const int ITEMS_PER_AREA = 3;
const int NPCS_PER_AREA = 3;
const int MAX_REGIONS = 5;
const int MIN_REGIONS = 1;
const int MAX_AREAS_IN_REGION = 15;
const int MIN_AREAS_IN_REGION = 3;
const int MAX_NEIGHBORS = 4;

enum CompassEnum {

	North = 0,
	South = 1,
	East = 2,
	West = 3,
};

ostream& operator <<(ostream& strm, CompassEnum compass);

struct ZoneData{
	int id;
	char label[24];
};

class Zone {
public:
	virtual void SerializeZone(std::fstream&) = 0;
	virtual void DeserializeZone(std::fstream&) = 0;
protected:
	static int zoneID;
	string label;
private:
	ZoneData* data;
};

struct AreaData : public ZoneData {
	size_t number;
	int posLat;
	int posLong;
	int npcIDs[NPCS_PER_AREA];
	int itemIDs[ITEMS_PER_AREA];
	int neighborIDs[4];
	char rawDescription[128];
};

class Area : public Zone {
public:
	Area();
	Area(const string&);
	Area(const string&, const string&);
	string DescribeArea();
	void SetDescription(const string&);
	void SetNeighbor(const size_t&, Area*);
	Area* GetNeighbor(const size_t&);
	int GetNumber() const;
	int GetNeighborID(const size_t& i) const {return this->data->neighborIDs[i];};
	void AddItem(Entity*);
	Entity* PopItem(string);
	string PeekItem(string);
	string ListItems();
	void AddNPC(Entity*);
	inline void SetPosition(const int& lat, const int& lon) {
		this->data->posLat = lat;
		this->data->posLong = lon;
	};
	inline void SetNumber(const size_t& num) { this->data->number = num; }
	inline int GetLat() const { return this->data->posLat; }
	inline int GetLong() const { return this->data->posLong; }
	inline int GetID() const { return this->data->id; }
	void SerializeZone(std::fstream&) override;
	void DeserializeZone(std::fstream&) override;
private:
	void RetreiveItem();
	void RetreiveNPC();
	string description;
	vector<Entity*> items;
	vector<Entity*> npcs;
	AreaData* data;
	Area* neighbors[4]; // N, S, E, W
	friend ostream& operator<<(ostream&, const Area&);
};

struct RegionData : public ZoneData {
	size_t areaNum;	
};

class Region : public Zone {
public:
	Region();
	Region(const string&);
	string ListAreas();
	size_t AreaNum();
	void AddArea(const Area&);
	string DescribeRegion();
	inline void SetRoot(const Area& a) {this->root = const_cast<Area*>(&a);};
	inline Area& GetRoot() { return *this->root; };
	void SerializeZone(std::fstream&) override;
	void DeserializeZone(std::fstream&) override;
	Area& GetArea(const size_t& i){ return this->areas[i];}
	size_t GetAreaNum() const {return this->data->areaNum;}
protected:
	vector<Area> areas;
	Area* root;
	Area* neighbors[4]; // N, S, E, W
	RegionData* data;

};

struct WorldData : public ZoneData {
	size_t regionNum;
};

class World : public Zone {
public:
	World();
	World(const string&);
	//World(const size_t&, const size_t&, const size_t&);
	void AddRegion(const Region&);
	void AddItem(Item*);
	void AddNPC(NPC*);
	string DescribeWorld();
	inline Area& GetStartingArea() { return this->regions[0].GetRoot(); };
	void SerializeZone(std::fstream&) override;
	void DeserializeZone(std::fstream&) override;
	Region& GetRegion(const size_t& i) { return this->regions[i]; }
	size_t GetRegionNum() const {return this->data->regionNum;}
protected:
	vector<Region> regions;
	vector<Item*> items;
	vector<NPC*> npcs;
	WorldData* data;
};

class GameWorld {
public:
	static string GAME_TITLE;
	GameWorld(const string&, const string&);
	void PopulateGameWorld();
	void PopulateRegion(Region&, const size_t&);
	void PopulateArea(Area&);
	Item* GenerateItem(const int&);
	NPC* GenerateNPC(const int&);
	string ToString();
	void SaveWorld(const string&);
	void LoadWorld(const string&);
	inline Area& GetStart() { return this->world->GetStartingArea(); };
	inline void SetCurrentArea(const Area& _a) { this->currentArea = _a; };
	inline Area& GetCurrentArea() { return currentArea; };
	inline void SetDBReferences(const string& itemDB, const string& npcDB) { this->itemDatabase=itemDB; this->npcDatabase=npcDB; };
	inline bool IsInitialized() {return this->initialized;}
private:
	World* world;
	Area currentArea;
	bool initialized;
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist;
	string itemDatabase, npcDatabase;
};

struct AreaLink {
	Area* parent, * area;
	CompassEnum parentDirection;

	friend ostream& operator<<(ostream&, const AreaLink&);
};

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

vector<AreaLink>& AddAreaLinks(vector<AreaLink>&, const AreaLink&);

void PopulateArea(Area&);

void PopulateRegion(Region&, const size_t&);
#endif
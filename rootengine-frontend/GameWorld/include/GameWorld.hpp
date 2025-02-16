#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <iostream>
#include <vector>
#include <format>
#include <NPC.hpp>
#include <Item.hpp>
#include <random>
using namespace std;
constexpr int ITEMS_PER_AREA = 3;
constexpr int NPCS_PER_AREA = 3;
constexpr int MAX_REGIONS = 5;
constexpr int MIN_REGIONS = 1;
constexpr int MAX_AREAS_IN_REGION = 15;
constexpr int MIN_AREAS_IN_REGION = 3;

enum CompassEnum {

	North = 0,
	South = 1,
	East = 2,
	West = 3,
};

ostream& operator <<(ostream& strm, CompassEnum compass);


class Area {
public:
	Area();
	Area(const string&);
	Area(const string&, const string&);
	string DescribeArea();
	void SetDescription(const string&);
	void SetNeighbor(const size_t&, Area*);
	Area* GetNeighbor(const size_t&);
	int GetNumber() const;
	void AddItem(Entity*);
	void AddNPC(Entity*);
	inline void SetPosition(const int& lat, const int& lon) {
		this->posLat = lat;
		this->posLong = lon;
	};
	inline void SetNumber(const size_t& num) { this->number = num; }
	inline int GetLat() const { return this->posLat; }
	inline int GetLong() const { return this->posLong; }
private:
	string description;
	string label;
	vector<Entity*> items;
	vector<Entity*> npcs;
	int posLat;
	int posLong;
	size_t number;
	Area* neighbors[4]; // N, S, E, W
	friend ostream& operator<<(ostream&, const Area&);
};

class Region {
public:
	Region();
	Region(const string&);
	string ListAreas();
	size_t AreaNum();
	void AddArea(const Area&);
	string DescribeRegion();
	inline void SetRoot(const Area& a) {this->root = const_cast<Area*>(&a);};
	inline Area& GetRoot() { return *this->root; };
protected:
	vector<Area> areas;
	Area* root;
	string label;
	Area* neighbors[4]; // N, S, E, W

};

class World {
public:
	World();
	World(const string&);
	//World(const size_t&, const size_t&, const size_t&);
	void AddRegion(const Region&);
	string DescribeWorld();
	inline Area& GetStartingArea() { return this->regions[0].GetRoot(); };
protected:
	vector<Region> regions;
	string label;
};

class GameWorld {
public:
	GameWorld();
	void PopulateGameWorld();
	void PopulateRegion(Region&, const size_t&);
	void PopulateArea(Area&);
	string ToString();
	inline Area& GetStart() { return this->world->GetStartingArea(); };
	inline void SetCurrentArea(const Area& _a) { this->currentArea = _a; };
	inline Area& GetCurrentArea() { return currentArea; };
private:
	World* world;
	Area currentArea;
	std::default_random_engine gen;
	std::uniform_int_distribution<int> dist;
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
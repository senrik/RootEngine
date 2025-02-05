#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include <iostream>
#include <vector>
#include <format>
#include <NPC.hpp>
#include <Item.hpp>
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
	void AddItem(Entity*);
	void AddNPC(Entity*);
private:
	string description;
	string label;
	vector<Entity*> items;
	vector<Entity*> npcs;
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
protected:
	vector<Area> areas;
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
protected:
	vector<Region> regions;
	string label;
};

class GameWorld {
public:
	GameWorld();
	void PopulateGameWorld();
	string ToString();
private:
	World* world;
};

struct AreaLink {
	Area* parent, * area;
	CompassEnum parentDirection;

	friend ostream& operator<<(ostream&, const AreaLink&);
};

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

void PopulateArea(Area&);

void PopulateRegion(Region&, const size_t&);
#endif
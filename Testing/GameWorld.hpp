#pragma once
#include <iostream>
#include <format>
#include <string>
#include <vector>
using namespace std;
constexpr size_t REGION_AREA_NUM = 15;

enum CompassEnum {

	North = 0,
	South = 1,
	East = 2,
	West = 3,
};



struct Area {
	int number;
	Area* neighbors[4];
	int posLat, posLong;
	void InitializeArea();

	friend ostream& operator<<(ostream&, const Area&);
};


struct AreaLink {
	Area* parent, * area;
	CompassEnum parentDirection;


	friend ostream& operator<<(ostream&, const AreaLink&);
};



struct Region {
	int number;
	int areaCount;
	Area* areas[REGION_AREA_NUM], * northernExits[100], * southernExits[100], * eastExits[100], * westExits[100];
	Area* root;
	void InitializeRegion();
	friend ostream& operator<<(ostream&, const Region&);
};

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

vector<AreaLink>& AddAreaLinks(vector<AreaLink>&, const AreaLink&);

int TraverseWorld(Region*);
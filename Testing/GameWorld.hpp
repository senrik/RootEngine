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

ostream& operator <<(ostream& strm, CompassEnum compass) {
	const string nameCompass[] = { "North", "South", "East", "West" };

	return strm << nameCompass[compass];
}

struct Area {
	int number;
	Area* neighbors[4];
	int posLat, posLong;
	void InitializeArea();

	friend ostream& operator<<(ostream&, const Area&);
};

ostream& operator <<(ostream& out, const Area& _area) {
	/*       [0]
	*         ^
	*         |
	* [3] < - O - > [2]
	*         |
	*         v
	*        [1]
	*
	*/
	out << format("       {}       \n       ^\n       |\n{} < - {} - > {}\n       |\n       v\n       {}\n",
		(_area.neighbors[0] != nullptr) ? _area.neighbors[0]->number : -1,
		(_area.neighbors[3] != nullptr) ? _area.neighbors[3]->number : -1,
		_area.number,
		(_area.neighbors[2] != nullptr) ? _area.neighbors[2]->number : -1,
		(_area.neighbors[1] != nullptr) ? _area.neighbors[1]->number : -1);
	out << format("Position: ({}, {})\n", _area.posLat, _area.posLong);
	return out;
}

struct AreaLink {
	Area* parent, * area;
	CompassEnum parentDirection;


	friend ostream& operator<<(ostream&, const AreaLink&);
};

ostream& operator <<(ostream& out, const AreaLink& _link) {

	out << ((_link.area == nullptr) ? "nullptr" : to_string(_link.area->number));
	out << format(" connects to {}", _link.parent->number);
	out << " " << _link.parentDirection << "ward" << endl;
	return out;

}

struct Region {
	int number;
	int areaCount;
	Area* areas[REGION_AREA_NUM], * northernExits[100], * southernExits[100], * easternExits[100], * westernExits[100];
	Area* root;
	int minLat, maxLat, minLong, maxLong, northExitCount, southExitCount, eastExitCount, westExitCount;
	void InitializeRegion();
	friend ostream& operator<<(ostream&, const Region&);
};

ostream& operator<<(ostream& out, const Region& _region) {

	out << format("Region {} has {} areas", _region.number, _region.areaCount) << endl;

	return out;
}

AreaLink Dequeue(vector<AreaLink>&);

AreaLink Pop(vector<AreaLink>&);

AreaLink& LinkParentAndArea(AreaLink&, const size_t&);

vector<AreaLink>& AddAreaLinks(vector<AreaLink>&, const AreaLink&);
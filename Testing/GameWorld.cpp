#include "GameWorld.hpp"

AreaLink& LinkParentAndArea(AreaLink& link, const size_t& areaCount) {
	link.area = new Area();
	link.area->number = areaCount;
	link.area->posLat = link.parent->posLat;
	link.area->posLong = link.parent->posLong;
	// link area to parent

	link.area->neighbors[link.parentDirection] = link.parent;
	// link parent and set position
	switch (link.parentDirection) {
	case CompassEnum::North:
		link.parent->neighbors[CompassEnum::South] = link.area;
		link.area->posLong--;
		break;
	case CompassEnum::South:
		link.parent->neighbors[CompassEnum::North] = link.area;
		link.area->posLong++;
		break;
	case CompassEnum::East:
		link.parent->neighbors[CompassEnum::West] = link.area;
		link.area->posLat--;
		break;
	case CompassEnum::West:
		link.parent->neighbors[CompassEnum::East] = link.area;
		link.area->posLat++;
		break;
	}

	return link;
}

vector<AreaLink>& AddAreaLinks(vector<AreaLink>& f, const AreaLink& prev) {
	// TO-DO: find a way to randomize this seleciton
	for (int i = 0; i < 4; i++) {
		AreaLink _newTemp;
		if (prev.area->neighbors[i] == nullptr) {
			_newTemp.parent = prev.area;
			if (i % 2 == 0) {
				if (i > 0) {
					_newTemp.parentDirection = CompassEnum::West;
				}
				else {
					_newTemp.parentDirection = CompassEnum::South;
				}
			}
			else {
				if (i > 1) {
					_newTemp.parentDirection = CompassEnum::East;
				}
				else {
					_newTemp.parentDirection = CompassEnum::North;
				}
			}
			_newTemp.area = prev.area->neighbors[i];

			// add to collection
			f.push_back(_newTemp);
		}
	}

	return f;
}

void Region::InitializeRegion() {
	vector<AreaLink> frontier;
	// Initialize the root area for the region
	this->root = new Area();
	this->root->number = 0;
	this->root->posLat = 0;
	this->root->posLong = 0;
	this->areas[0] = this->root;
	int areaCount = 1;
	for (int i = 0; i < 4; i++) {
		AreaLink _temp;
		if (this->root->neighbors[i] == nullptr) {
			_temp.parent = this->root;
			if (i % 2 == 0) {
				if (i > 0) {
					_temp.parentDirection = CompassEnum::West;
				}
				else {
					_temp.parentDirection = CompassEnum::South;
				}
			}
			else {
				if (i > 1) {
					_temp.parentDirection = CompassEnum::East;
				}
				else {
					_temp.parentDirection = CompassEnum::North;
				}
			}
			_temp.area = this->root->neighbors[i];

			frontier.push_back(_temp);
		}
	}

	// keep adding areas to the region until we are done.
	while (areaCount <= REGION_AREA_NUM) {
		float threshold = (40 / -areaCount) + 70;

		AreaLink _tempLink;
		// depth first
		if (rand() % 100 > threshold) {
			cout << "Popping with threshold: " << threshold << endl;
			_tempLink = Pop(frontier);

		}// breadth first
		else {
			cout << "Dequeuing with threshold: " << threshold << endl;
			_tempLink = Dequeue(frontier);
		}

		// link parent to area and area to parent
		_tempLink = LinkParentAndArea(_tempLink, areaCount);

		this->areas[areaCount] = _tempLink.area;

		// add new possible areas to the collection
		frontier = AddAreaLinks(frontier, _tempLink);

		areaCount++;
	}
}

AreaLink Pop(vector<AreaLink>& v) {
	AreaLink _tempLink;

	_tempLink = v.back();
	v.pop_back();

	return _tempLink;

}

AreaLink Dequeue(vector<AreaLink>& v) {
	AreaLink _tempLink;

	vector<AreaLink>::const_iterator _iter = v.begin();
	_tempLink = v.front();
	v.erase(_iter);

	return _tempLink;
}
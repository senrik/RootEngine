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

	
	// Holds possible areas we have not initialized yet.
	vector<AreaLink> frontier;
	// Initialize the root area for the region
	this->root = new Area();
	this->root->number = 0;
	this->root->posLat = 0;
	this->root->posLong = 0;
	this->areas[0] = this->root;
	this->minLat = 0;
	this->maxLat = 0;
	this->minLong = 0;
	this->maxLong = 0;
	this->northExitCount = 0;
	this->southExitCount = 0;
	this->eastExitCount = 0;
	this->westExitCount = 0;;
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
			//cout << "Popping with threshold: " << threshold << endl;
			_tempLink = Pop(frontier);

		}// breadth first
		else {
			//cout << "Dequeuing with threshold: " << threshold << endl;
			_tempLink = Dequeue(frontier);
		}

		// link parent to area and area to parent
		_tempLink = LinkParentAndArea(_tempLink, areaCount);

		this->areas[areaCount] = _tempLink.area;
		// update the region's borders here

		// southern exits
		if (this->minLat > _tempLink.area->posLat) {
			// need to remove any previous entries
			for (int i = 0; i < this->southExitCount; i++)
			{
				this->southernExits[i] = nullptr;
			}
			this->southernExits[0] = _tempLink.area;
			this->southExitCount = 1;

		}
		else if (this->minLat == _tempLink.area->posLat) {
			this->southernExits[this->southExitCount] = _tempLink.area;
			this->southExitCount++;
		}
		// northern exits
		if (this->maxLat < _tempLink.area->posLat) {
			// need to remove any previous entries
			for (int i = 0; i < this->northExitCount; i++)
			{
				this->northernExits[i] = nullptr;
			}
			this->northernExits[0] = _tempLink.area;
			this->northExitCount = 1;
		}
		else if (this->maxLat == _tempLink.area->posLat) {
			this->northernExits[this->northExitCount] = _tempLink.area;
			this->northExitCount++;
		}
		// eastern exits
		if (this->minLong < _tempLink.area->posLong) {
			// need to remove any previous entries
			for (int i = 0; i < this->westExitCount; i++)
			{
				this->westernExits[i] = nullptr;
			}
			this->westernExits[0] = _tempLink.area;
			this->westExitCount = 1;
		}
		else if (this->minLong == _tempLink.area->posLong) {
			this->westernExits[this->westExitCount] = _tempLink.area;
			this->westExitCount++;
		}
		// western exists
		if (this->maxLong < _tempLink.area->posLong) {
			// need to remove any previous entries
			for (int i = 0; i < this->eastExitCount; i++)
			{
				this->easternExits[i] = nullptr;
			}
			this->easternExits[0] = _tempLink.area;
			this->eastExitCount = 1;
		}
		else if (this->maxLong == _tempLink.area->posLong) {
			this->easternExits[this->eastExitCount] = _tempLink.area;
			this->eastExitCount++;
		}

		// add new possible areas to the collection
		frontier = AddAreaLinks(frontier, _tempLink);

		areaCount++;
	}

	cout << "Northern exit Count: " << this->northExitCount << endl;
	for (int i = 0; i < this->northExitCount; i++) {
		cout << "|\t" << this->northernExits[i] << endl;
	}
	cout << ", Southern exit Count: " << this->southExitCount << endl;
	for (int i = 0; i < this->southExitCount; i++) {
		cout << "|\t" << this->southernExits[i] << endl;
	}
	cout << ", Eastern exit Count: " << this->eastExitCount << endl;
	for (int i = 0; i < this->eastExitCount; i++) {
		cout << "|\t" << this->easternExits[i] << endl;
	}
	cout << ", Western exit Count: " << this->westExitCount << endl;
	for (int i = 0; i < this->westExitCount; i++) {
		cout << "|\t" << this->westernExits[i] << endl;
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
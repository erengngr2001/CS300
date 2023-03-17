#pragma once
#include <string>
#include <vector>

using namespace std;

struct Coord
{
	int XCOORD;
	int height;
	bool isLeft;

	Coord():
		XCOORD(0), height(0), isLeft(true)
	{};

	Coord(int x, int h, bool is) :
		XCOORD(x), height(h), isLeft(is)
	{}

	void operator=(const Coord& a)
	{
		this->XCOORD = a.XCOORD;
		this->height = a.height;
		this->isLeft = a.isLeft;
	}
};

struct BuildingInfo
{
	Coord value;
	int label;

	BuildingInfo():
		label(0)
	{
		Coord c(-1, -1, true);
		value = c;
	}

	BuildingInfo(Coord coord, int buildingLabel):
		value(coord), label(buildingLabel)
	{}

	bool operator<(const BuildingInfo& a) const
	{
		//return this->value.XCOORD  < a.value.XCOORD;
		if (this->value.XCOORD < a.value.XCOORD)
			return true;
		else if (this->value.XCOORD == a.value.XCOORD)
			return this->value.height < a.value.height;
	}

	void operator=(const BuildingInfo& a)
	{
		this->value = a.value;
		this->label = a.label;
	}

	bool operator>(const BuildingInfo& a) const
	{
		return this->value.height > a.value.height;
	}
};


class Modified_Priority_Queue
{
public:
	Modified_Priority_Queue();
	void insert(Coord value, int label);
	BuildingInfo remove(int label);
	BuildingInfo getMax();
	bool isEmpty();
	void setLocationArr(int numOfBuildings);

private:
	//apply delete, find and insert operations depending on its value or label(identifier)
	vector<BuildingInfo> infoHeap; //keeps all building-coordinate nodes
	vector<int> location;
	void percolateDown(int hole, vector<BuildingInfo>& vec);
	void percolateUp(int hole);
	int currentSize;
};


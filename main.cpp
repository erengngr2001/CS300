#include <iostream>
#include <string>
#include "Modified_Priority_Queue.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

int partition(vector<BuildingInfo> &vec, int start, int end)
{

	BuildingInfo pivot = vec[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (vec[i].value.XCOORD < pivot.value.XCOORD || (vec[i].value.XCOORD == pivot.value.XCOORD && vec[i].value.height >= pivot.value.height))
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	/*BuildingInfo temp = vec[pivotIndex];
	vec[pivotIndex] = vec[start];
	vec[start] = temp;*/
	swap(vec[pivotIndex], vec[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (vec[i].value.XCOORD < pivot.value.XCOORD || (vec[i].value.XCOORD == pivot.value.XCOORD && vec[i].value.height >= pivot.value.height)) {
			i++;
		}

		while (vec[j].value.XCOORD > pivot.value.XCOORD || (vec[j].value.XCOORD == pivot.value.XCOORD && vec[i].value.height < pivot.value.height)) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(vec[i++], vec[j--]);
			/*temp = vec[i];
			vec[i] = vec[j];
			vec[j] = vec[i];
			i++; j--;*/
		}
	}

	return pivotIndex;
}

void quickSort(vector<BuildingInfo> &vec, int start, int end)
{
	if (start >= end)
		return;

	int p = partition(vec, start, end);

	quickSort(vec, start, p - 1);
	quickSort(vec, p + 1, end);
}


int main()
{
	string filename, line;
	ifstream file;

	Modified_Priority_Queue MPQ;
	int numOfBuildings, xstart, xend, height;
	int buildingID = 1;
	int currentMaxHeight = 0, maxHeightOccurence = 0, prevMaxHeight = 0;
	vector<BuildingInfo> landscape;
	Coord dummy(-1, 0, true);
	/*landscape.push_back(dumm);*/
	
	filename = "input2.txt";
	file.open(filename.c_str());
	getline(file, line);
	istringstream ssLine(line);
	ssLine >> numOfBuildings;
	MPQ.setLocationArr(numOfBuildings);

	while (getline(file, line))
	{
		istringstream ssLine(line);
		ssLine >> xstart >> height >> xend;
		Coord c1(xstart, height, true);
		Coord c2(xend, -height, false);
		BuildingInfo b1(c1, buildingID);
		BuildingInfo b2(c2, buildingID);
		landscape.push_back(b1);
		landscape.push_back(b2);
		buildingID++;
	}
	file.close();

	//sort(landscape.begin(), landscape.end());
	quickSort(landscape, 0, landscape.size() - 1); //düzelt
	quickSort(landscape, 0, landscape.size() - 1);

	if (0 != landscape[0].value.XCOORD)
	{
		cout << "0 0\n";
	}
	
	for (int i = 0; i < landscape.size() - 1; i++)
	{
		if (landscape[i].value.isLeft)
		{
			prevMaxHeight = MPQ.getMax().value.height; //ilk eleman yokken patlar
			MPQ.insert(landscape[i].value, landscape[i].label);
			currentMaxHeight = MPQ.getMax().value.height;

			if (currentMaxHeight > prevMaxHeight)
			{
				cout << MPQ.getMax().value.XCOORD << " " << MPQ.getMax().value.height << endl;
			}
		}
		else
		{
			prevMaxHeight = MPQ.getMax().value.height;
			BuildingInfo prev = landscape[i];
			MPQ.remove(landscape[i].label);
			currentMaxHeight = MPQ.getMax().value.height;

			if (currentMaxHeight < prevMaxHeight && prev.value.XCOORD == -1)
			{
				cout << MPQ.getMax().value.XCOORD << " " << MPQ.getMax().value.height << endl;
			}
			else if (currentMaxHeight < prevMaxHeight && prev.value.XCOORD != -1)
			{
				cout << prev.value.XCOORD << " " << MPQ.getMax().value.height << endl;
			}
		}
	}

	return 0;
}
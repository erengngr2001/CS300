#include <iostream>
#include <string>
#include "QuadTree.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	QuadTree myTree;
	string filename, line, cityName, comma, citiesInRegion = "", citiesVisited = "";
	ifstream file;
	int rightCornerX, rightCornerY, Xcoord, Ycoord, radius;

	//Read citiex.txt and create the tree.
	filename = "cities1.txt";
	file.open(filename.c_str());
	getline(file, line);
	istringstream ssLine(line);
	ssLine >> rightCornerX >> rightCornerY;
	while (getline(file, line))
	{
		istringstream ssLine(line);
		ssLine >> cityName >> Xcoord >> Ycoord; 
		quadTreeNode cityNode(Xcoord, Ycoord, cityName);
		myTree.insert(cityNode);

	}
	file.close();

	myTree.pretty_print(myTree.getRoot());

	filename = "queries1.txt";
	file.open(filename.c_str());
	while (getline(file, line))
	{
		istringstream ssLine(line);
		ssLine >> Xcoord >> comma >> Ycoord >> comma >> radius;
		myTree.regionSearch(Xcoord, Ycoord, radius, myTree.getRoot(), citiesInRegion, citiesVisited);
		cout << endl;
		if ("" == citiesInRegion)
		{
			cout << "<None>" << endl << citiesVisited.substr(0, citiesVisited.length() - 2) << endl;
		}
		else
			cout << citiesInRegion.substr(0, citiesInRegion.length() - 2) << endl << citiesVisited.substr(0, citiesVisited.length() - 2) << endl;
		citiesInRegion = "";
		citiesVisited = "";
		//STRING YERÝNE VECTOR DENE
	}

	file.close();

	return 0;
}
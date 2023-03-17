#pragma once
#include <string>
#include <iostream>

using namespace std;

struct quadTreeNode
{
	quadTreeNode();
	quadTreeNode(int x, int y, string cityName) :
		XCOORD(x), YCOORD(y), NAME(cityName)
	{}

	quadTreeNode* NW = nullptr;
	quadTreeNode* SW = nullptr;
	quadTreeNode* SE = nullptr;
	quadTreeNode* NE = nullptr;
	int XCOORD;
	int YCOORD;
	string NAME;
	//friend class QuadTree;
};


class QuadTree
{
public:
	QuadTree();
	~QuadTree();
	quadTreeNode* getRoot();
	//void setRoot(quadTreeNode* root);
	void regionSearch(int XCOORD, int YCOORD, int radius, quadTreeNode* node, string &citiesInRegion, string &citiesVisited);
	void insert(quadTreeNode& cityNode);
	void pretty_print(quadTreeNode* root);
private:
	quadTreeNode* root;
	void makeEmpty(quadTreeNode*& node) const;
	double calculateDistance(int XCOORD, int YCOORD, quadTreeNode* node);
	void searchCities(int XCOORD, int YCOORD, int radius, quadTreeNode* node, string& citiesInRegion, string& citiesVisited);
	void PT_insert(quadTreeNode& cityNode, quadTreeNode*& node) const;
};


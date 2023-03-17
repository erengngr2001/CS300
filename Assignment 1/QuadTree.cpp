#include "QuadTree.h"
#include <cmath>

QuadTree::QuadTree() 
{
	root = nullptr;
}

QuadTree::~QuadTree()
{
	makeEmpty(root);
}

quadTreeNode* QuadTree::getRoot()
{
	return root;
}

void QuadTree::insert(quadTreeNode& cityNode)
{
	PT_insert(cityNode, root);
}

void QuadTree::PT_insert(quadTreeNode &cityNode, quadTreeNode* &node)const
{
	if (nullptr == node)
	{
		node = new quadTreeNode(cityNode.XCOORD, cityNode.YCOORD, cityNode.NAME);
	}
	else if ((cityNode.XCOORD < node->XCOORD) && (cityNode.YCOORD < node->YCOORD))
	{
		PT_insert(cityNode, node->SW);
	}
	else if ((cityNode.XCOORD >= node->XCOORD) && (cityNode.YCOORD < node->YCOORD))
	{
		PT_insert(cityNode, node->SE);
	}
	else if ((cityNode.XCOORD < node->XCOORD) && (cityNode.YCOORD >= node->YCOORD))
	{
		PT_insert(cityNode, node->NW);
	}
	else if ((cityNode.XCOORD >= node->XCOORD) && (cityNode.YCOORD >= node->YCOORD))
	{
		PT_insert(cityNode, node->NE);
	}
}

void QuadTree::pretty_print(quadTreeNode* root)
{
	if (nullptr != root)
	{
		cout << root->NAME << endl;
		pretty_print(root->SE);
		pretty_print(root->SW);
		pretty_print(root->NE);
		pretty_print(root->NW);
	}
}

void QuadTree::regionSearch(int XCOORD, int YCOORD, int radius, quadTreeNode* node, string &citiesInRegion, string &citiesVisited)
{
	if (nullptr != node)
	{
		searchCities(XCOORD, YCOORD, radius, node, citiesInRegion, citiesVisited);

		if ((node->XCOORD <= (XCOORD - radius)) && (node->YCOORD > (YCOORD + radius))) //1
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);

		}
		else if ((node->YCOORD > (YCOORD + radius)) && (node->XCOORD > (XCOORD - radius)) && (node->XCOORD <= (XCOORD + radius))) //2
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD > (XCOORD + radius)) && (node->YCOORD > (YCOORD + radius))) //3
		{
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD <= (XCOORD - radius)) && (node->YCOORD > (YCOORD - radius)) && (node->YCOORD <= (YCOORD + radius))) //4
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD > (XCOORD + radius)) && (node->YCOORD > (YCOORD - radius)) && (node->YCOORD <= (YCOORD + radius))) //5
		{
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD <= (XCOORD - radius)) && (node->YCOORD <= (YCOORD - radius))) //6
		{
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
		}
		else if ((node->YCOORD <= (YCOORD - radius)) && (node->XCOORD > (XCOORD - radius)) && (node->XCOORD <= (XCOORD + radius))) //7
		{
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD > (XCOORD + radius)) && (node->YCOORD <= (YCOORD - radius))) //8
		{
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD > (XCOORD - radius)) && (node->XCOORD < XCOORD) && (node->YCOORD <= (YCOORD + radius)) && (node->YCOORD > YCOORD) && (calculateDistance(XCOORD, YCOORD, node) > radius)) //9
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD <= (XCOORD + radius)) && (node->XCOORD > XCOORD) && (node->YCOORD <= (YCOORD + radius)) && (node->YCOORD > YCOORD) && (calculateDistance(XCOORD, YCOORD, node) > radius)) //10
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD > (XCOORD - radius)) && (node->XCOORD < XCOORD) && (node->YCOORD > (YCOORD - radius)) && (node->YCOORD < YCOORD) && (calculateDistance(XCOORD, YCOORD, node) > radius)) //11
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else if ((node->XCOORD <= (XCOORD + radius)) && (node->XCOORD > XCOORD) && (node->YCOORD > (YCOORD - radius)) && (node->XCOORD < XCOORD) && (calculateDistance(XCOORD, YCOORD, node) > radius)) //12
		{
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
		else //13
		{
			regionSearch(XCOORD, YCOORD, radius, node->SE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->SW, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NE, citiesInRegion, citiesVisited);
			regionSearch(XCOORD, YCOORD, radius, node->NW, citiesInRegion, citiesVisited);
		}
	}
}

void QuadTree::searchCities(int XCOORD, int YCOORD, int radius, quadTreeNode* node, string& citiesInRegion, string& citiesVisited)
{

	if (nullptr != node)
	{
		double distance = calculateDistance(XCOORD, YCOORD, node);
		if (radius >= distance)
		{
			citiesInRegion += node->NAME + ", ";
			citiesVisited += node->NAME + ", ";
		}
		else
		{
			citiesVisited += node->NAME + ", ";
		}
	}
}

double QuadTree::calculateDistance(int XCOORD, int YCOORD, quadTreeNode* node)
{
	double distance;
	int xdif, ydif;
	xdif = node->XCOORD - XCOORD;
	ydif = node->YCOORD - YCOORD;
	distance = sqrt((xdif * xdif) + (ydif * ydif));

	return distance;
}

void QuadTree::makeEmpty(quadTreeNode*& node) const
{
	if (nullptr != node)
	{
		makeEmpty(node->SE);
		makeEmpty(node->SW);
		makeEmpty(node->NE);
		makeEmpty(node->NW);
		delete node;
	}
	node = nullptr;
}
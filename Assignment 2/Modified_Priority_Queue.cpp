#include "Modified_Priority_Queue.h"

int PARENT(int i) {
	return (i - 1) / 2;
}

// return left child
int LEFT(int i) {
	return (2 * i + 1);
}

// return right child
int RIGHT(int i) {
	return (2 * i + 2);
}

Modified_Priority_Queue::Modified_Priority_Queue()
{
	BuildingInfo dummy;
	dummy.value.height = 0;
	this->infoHeap.push_back(dummy);
	currentSize = 0;
}

void Modified_Priority_Queue::setLocationArr(int numOfBuildings)
{
	for (int i = 0; i <= numOfBuildings; i++)
		location.push_back(-1);
}

void Modified_Priority_Queue::insert(Coord value, int label)
{
	BuildingInfo building(value, label);	
	int hole = ++currentSize;
	infoHeap.push_back(building);
	location[building.label] = currentSize;

	for (; hole > 1 && value.height > infoHeap[hole / 2].value.height; hole /= 2)
	{
		infoHeap[hole] = infoHeap[hole / 2];
		location[infoHeap[hole].label] = hole; //düzelt
	}

	infoHeap[hole] = building;
	location[label] = hole;
}

bool Modified_Priority_Queue::isEmpty()
{
	return (1 == this->infoHeap.size());
}

BuildingInfo Modified_Priority_Queue::remove(int label)
{
	BuildingInfo item;
	item = infoHeap[location[label]];
	infoHeap[location[label]] = infoHeap[currentSize];
	int tempLabel = location[label];
	location[infoHeap[currentSize].label] = location[label]; //düzelt
	currentSize--;
	location[label] = -1;
	infoHeap.pop_back();

	if ((currentSize + 1) != tempLabel)
		percolateDown(tempLabel, infoHeap);

	return item;
}

BuildingInfo Modified_Priority_Queue::getMax()
{
	if (isEmpty())
	{
		Coord dum(-1, 0, true);
		BuildingInfo dummy(dum, 0);
		infoHeap.push_back(dummy);
		currentSize++;
		return dummy;
	}
	return infoHeap[1];
}

void Modified_Priority_Queue::percolateDown(int hole, vector<BuildingInfo>& vec)
{
	int child;
	BuildingInfo temp = vec[hole];

	for (; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize && vec[child + 1] > vec[child])
			child++;
		if (vec[child] > temp)
		{
			location[vec[hole].label] = child;
			vec[hole] = vec[child];
			location[vec[child].label] = hole;
			//swap(location[vec[hole].label], location[vec[child].label]);
		}
		else
			break;
	}
	vec[hole] = temp;
}

//void Modified_Priority_Queue::percolateDown(int hole, vector<BuildingInfo>& vec)
//{
//	int left = LEFT(hole);
//	int right = RIGHT(hole);
//
//	int largest = hole;
//
//	if (left < vec.size() && vec[left] > vec[hole]) {
//		largest = left;
//	}
//
//	if (right < vec.size() && vec[right] > vec[largest]) {
//		largest = right;
//	}
//
//	if (largest != hole)
//	{
//		swap(vec[hole], vec[largest]);
//		percolateDown(largest, vec);
//	}
//}

void Modified_Priority_Queue::percolateUp(int hole)
{
	// check if the node at index `i` and its parent violate the heap property
	if (hole && infoHeap[hole] > infoHeap[PARENT(hole)])
	{
		// swap the two if heap property is violated
		swap(infoHeap[hole], infoHeap[PARENT(hole)]);

		// call heapify-up on the parent
		percolateUp(PARENT(hole));
	}
}
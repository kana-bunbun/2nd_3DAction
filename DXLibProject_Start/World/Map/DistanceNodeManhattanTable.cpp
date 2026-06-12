#include "DistanceNodeManhattanTable.h"

DistanceNodeManhattanTable::DistanceNodeManhattanTable():
	goalNode(nullptr),
	openList(),
	closeList()
{
	openList.clear();
	closeList.clear();
}

DistanceNodeManhattanTable::~DistanceNodeManhattanTable()
{

}

void DistanceNodeManhattanTable::Crear()
{
	goalNode = nullptr;
	openList.clear();
	closeList.clear();
}

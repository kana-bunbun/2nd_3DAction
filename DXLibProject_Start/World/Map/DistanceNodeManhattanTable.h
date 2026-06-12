#pragma once
#include"DistanceNodeManhattan.h"
#include<vector>
class DistanceNodeManhattanTable
{
public:
	DistanceNodeManhattanTable();
	~DistanceNodeManhattanTable();

	// テーブルの初期化
	void Crear();
public:
	DistanceNodeManhattan* goalNode;
	std::vector<DistanceNodeManhattan*>openList;
	std::vector<DistanceNodeManhattan*>closeList;
private:

};


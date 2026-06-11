#pragma once
#include"MapConst.h"
class ManhattanMoveData
{
public:

	ManhattanMoveData(int sourceID,int targetID,MapConst::eDirectionFour direction);
	ManhattanMoveData() = default;
	~ManhattanMoveData() = default;

	int m_sourceSquareID = -1;
	int m_targetSquareID = -1;
private:
	MapConst::eDirectionFour m_direction;
};


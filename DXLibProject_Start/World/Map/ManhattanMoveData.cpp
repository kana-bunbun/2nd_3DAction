#include "ManhattanMoveData.h"


ManhattanMoveData::ManhattanMoveData(int sourceID, int targetID, MapConst::eDirectionFour direction):
	m_sourceSquareID(sourceID),
	m_targetSquareID(targetID),
	m_direction(direction)
{

}

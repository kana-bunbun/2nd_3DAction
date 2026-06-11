#include "RouteSearcher.h"

RouteSearcher& RouteSearcher::GetInstance()
{
	static RouteSearcher instance;
	return instance;
}

RouteSearcher::DistanceNode::DistanceNode(int distance, int squareID):
	m_distance(distance),
	m_squareID(squareID)
{}

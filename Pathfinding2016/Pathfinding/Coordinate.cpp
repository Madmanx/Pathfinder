///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 coordinate.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#include "Coordinate.h"
#include <math.h>

namespace Pathfinding
{

	// Public default constructor
	Coordinate::Coordinate()
		: m_x(0)
		, m_y(0)
	{

	}

	// Public constructor with X and Y coordinate definition
	Coordinate::Coordinate(int x, int y)
		: m_x(x)
		, m_y(y)
	{

	}

	// Public accessor : Define X coordinate
	void Coordinate::setX(int x)
	{
		m_x = x;
	}

	// Public accessor : Retrieve X coordinate 
	int Coordinate::getX() const
	{
		return m_x;
	}

	// Public accessor : Define Y coordinate
	void Coordinate::setY(int y)
	{
		m_y = y;
	}

	// Public accessor : Retrieve Y coordinate
	int Coordinate::getY() const
	{
		return m_y;
	}

	// Public method : Converte 2 dimensional coordinates into 1 dimensional coordinate function of the map width 
	int Coordinate::getLinearOffset(const int nMapWidth) const
	{
		return (m_x + (m_y * nMapWidth));
	}

	// Public method: Definition of the equality operator of the coordinate class
	bool Coordinate::equals(Coordinate& b)
	{
		return (m_x == b.getX() && m_y == b.getY());
	}

	// Public method : Heuristic of the remaining distance from a coordinate to another
	double Coordinate::distanceTo(Coordinate& to)
	{
		return (sqrt((m_x - to.getX())*(m_x - to.getX()) + ((m_y - to.getY())*(m_y - to.getY()))));
	}
} // namespace pathfinding
///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 coordinate.h
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#ifndef COORDINATE_H
#define COORDINATE_H

namespace Pathfinding
{
	class Coordinate {

	public:
		// Public default constructor (0,0)
		Coordinate::Coordinate();
		// Public constructor with X and Y coordinate definition
		Coordinate::Coordinate(int x, int y);

		// Public accessor : Define X coordinate
		void Coordinate::setX(int x);
		// Public accessor : Retrieve X coordinate 
		int Coordinate::getX() const;
		// Public accessor : Define Y coordinate
		void Coordinate::setY(int y);
		// Public accessor : Retrieve Y coordinate
		int Coordinate::getY() const;

		// Public method : Converte 2 dimensional coordinates into 1 dimensional coordinate function of the map width 
		int Coordinate::getLinearOffset(const int nMapWidth) const;

		// Public method : Definition of the equality operator of the coordinate class
		bool equals(Coordinate& b);

		// Public method : Heuristic of the remaining distance from a node to another
		double Coordinate::distanceTo(Coordinate& to);

	private:
		int m_x;
		int m_y;
	};
} // namespace pathfinding
#endif

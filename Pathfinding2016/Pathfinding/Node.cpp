///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 node.cpp
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#include "Node.h"

namespace Pathfinding {

	// public constructor (likely used for the first node)
	Node::Node(Coordinate& coordinate, Coordinate& targetCoordinate)
		: m_coordinate(coordinate)
		, m_distanceToStart(0)
		, m_parent(NULL)
		, m_currentState(Node::e_stateNew)
	
	{
		m_estimatedDistanceToEnd = targetCoordinate.distanceTo(coordinate);
	}

	// Public accessor : Define coordinates of this node
	void Node::setCoordinate(Coordinate& coordinate)
	{
		m_coordinate = coordinate;
	}

	// Public accessor : Retrieve coordinates of this node
	Coordinate Node::getCoordinate()
	{
		return m_coordinate;
	}

	// Public accessor : Define traveled distance of the this node
	void Node::setDistanceToStart(int distanceToStart)
	{
		m_distanceToStart = distanceToStart;
	}

	// Public accessor : Retrieve traveled distance of the this node
	int Node::getDistanceToStart()
	{
		return m_distanceToStart;
	}

	// Public accessor : Define the remaining distance of the this node
	void Node::setEstimatedDistanceToEnd(int estimatedDistanceToEnd)
	{
		m_estimatedDistanceToEnd = estimatedDistanceToEnd;
	}

	// Public accessor : Retrieve the remaining distance of the this node
	int Node::getEstimatedDistanceToEnd()
	{
		return m_estimatedDistanceToEnd;
	}

	// Public accessor : Define the parent Node of the this node
	// Define the traveled distance of a node with the traveled distance of its parent
	void Node::setParent(Node* parent)
	{
		m_parent = parent;
		m_distanceToStart = parent->m_distanceToStart + 1;
	}

	// Public accessor : Retrieve the parent node of this node
	Node* Node::getParent()
	{
		return m_parent;
	}

	// Public accessor : Define the state of this node
	void Node::setCurrentState(State currentState)
	{
		m_currentState = currentState;
	}

	// Public accessor : Retrieve the current state of this node
	Node::State Node::getCurrentState()
	{
		return m_currentState;
	}

	// Public method :  operator used to compare two nodes
	// return true if the distance traveled plus the remaining distance of the second node is less than the ones of the first node
	bool Node::CompareNode::operator()(Node* firstNode, Node* secondNode)
	{
		return (secondNode->getDistanceToStart() + secondNode->getEstimatedDistanceToEnd() < firstNode->getDistanceToStart() + firstNode->getEstimatedDistanceToEnd());
	}
} // namespace pathfinding
///////////////////////////////////////////////////////////////////////////////
//
//  Last Edition:    16/10/2015
//  Filename:		 node.h
//  Author:			 Remi Boscher
//
//=============================================================================
//
//  purpose:		 Pathfinding exercice for Paradox Interactive
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NODE_H
#define NODE_H

#include <queue>
#include "Coordinate.h"

namespace Pathfinding {

	class Node {

	public:
		// State of a node in its lifecycle during the process
		enum State {
			e_stateNew,
			e_stateQueued,
			e_stateProcessed
		};

		// Subclass
		class CompareNode
		{
		public:
			// Public method :  operator used to compare two nodes
			// return true if the distance traveled plus the remaining distance of the second node is less than the ones of the first node
			bool operator()(Node* firstNode, Node* secondNode);
		};

		// Public defalt constructor
		Node::Node(Coordinate& coordinate, Coordinate& targetCoordinate);

		// Public accessor : Define coordinates of this node
		void Node::setCoordinate(Coordinate& pos);
		// Public accessor : Retrieve coordinates of this node
		Coordinate Node::getCoordinate();
		// Public accessor : Define traveled distance of the this node
		void Node::setDistanceToStart(int distanceTraveled);
		// Public accessor : Retrieve traveled distance of the this node
		int Node::getDistanceToStart();
		// Public accessor : Define traveled distance of the this node
		void Node::setEstimatedDistanceToEnd(int estimatedDistanceToEnd);
		// Public accessor : Retrieve traveled distance of the this node
		int Node::getEstimatedDistanceToEnd();
		// Public accessor : Define the parent Node of the this node
		// Define the traveled distance of a node with the traveled distance of its parent
		void Node::setParent(Node* parent);
		// Public accessor : Retrieve the parent node of this node
		Node* Node::getParent();
		// Public accessor : Define the state of this node
		void Node::setCurrentState(State currentState);
		// Public accessor : Retrieve the current state of this node
		State Node::getCurrentState();

	private:
		Coordinate m_coordinate;
		int m_distanceToStart;
		int m_estimatedDistanceToEnd;
		State m_currentState;
		Node* m_parent;
	};
} // namespace pathfinding
#endif
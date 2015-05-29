/*
 * AStar.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: colman
 */

#include "AStar.h"


AStar::AStar() {
	// TODO Auto-generated constructor stub

}
void AStar::FindPath (int startX, int startY, int goalX, int goalY)
{
	std::list<Point*> openList;
	std::list<Point*> closedList;
	std::vector<Point*> finalPath;
	std::list<Point*>::iterator listIterator;

	Point *startPoint = new Point(startX, startY);
	Point *endPoint = new Point(goalX, goalY);
	Point *currentPoint = new Point(-1, -1);
	Point *adjacentPoint = new Point(-1, -1);

	while (currentPoint != endPoint)
	{
		// Search for point with the smallest F score in the open list
		for (listIterator = openList.begin(); listIterator != openList.end() ;listIterator++)
		{
			if ((listIterator == openList.begin()) ||
				(*listIterator)->getFScore() <= currentPoint->getFScore())
			{
				currentPoint = *listIterator;
			}
		}

		// Stop if we reached the end
		if (currentPoint == endPoint)
			break;

		// Remove the current point from the open list
		openList.remove(currentPoint);
		currentPoint->isOpen = false;

		// Add the current point to the closed list
		openList.push_back(currentPoint);

		// Scan all the adjacent points
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				// If its the current point - then pass
				if (i == 0 && j == 0)
					continue;

				// If we are in a corner - then pass (we don't move in diagonal)
				if (i != 0 && j != 0)
					continue;

				// Get this adjacent point
				adjacentPoint = new Point(currentPoint->x + i, currentPoint->y + j);
			}
		}
	}
}

bool isInList(Point p, std::list<Point> list)
{
	std::list<Point*>::iterator i;

	for (i = list.begin(); i != list.end(); ++i) {


		if (i == p) {
			return true;
		}
	}

	return false;
}

void AStar::FindPath ()
{
	/*
	//this.startX = startX;
	                //this.startY = startY;
	                //this.goalX = goalX;
	                //this.goalY = goalY;

	                //mark start and goal node
	                map->setStartLocation(startX, startY);
	                map.setGoalLocation(goalX, goalY);

	                //Check if the goal node is blocked (if it is, it is impossible to find a path there)
	                if (map.getNode(goalX, goalY).isObstacle) {
	                        return null;
	                }

	                map.getStartNode().setDistanceFromStart(0);
	                closedList.clear();
	                openList.clear();
	                openList.add(map.getStartNode());

	                //while we haven't reached the goal yet
	                while(openList.size() != 0) {

	                        //get the first Node from non-searched Node list, sorted by lowest distance from our goal as guessed by our heuristic
	                        Node current = openList.getFirst();

	                        // check if our current Node location is the goal Node. If it is, we are done.
	                        if(current.getX() == map.getGoalLocationX() && current.getY() == map.getGoalLocationY()) {
	                                return reconstructPath(current);
	                        }

	                        //move current Node to the closed (already searched) list
	                        openList.remove(current);
	                        closedList.add(current);

	                        //go through all the current Nodes neighbors and calculate if one should be our next step
	                        for(Node neighbor : current.getNeighborList()) {
	                                boolean neighborIsBetter;

	                                //if we have already searched this Node, don't bother and continue to the next one
	                                if (closedList.contains(neighbor))
	                                        continue;

	                                //also just continue if the neighbor is an obstacle
	                                if (!neighbor.isObstacle) {

	                                        // calculate how long the path is if we choose this neighbor as the next step in the path
	                                        float neighborDistanceFromStart = (current.getDistanceFromStart() + map.getDistanceBetween(current, neighbor));

	                                        //add neighbor to the open list if it is not there
	                                        if(!openList.contains(neighbor)) {
	                                                openList.add(neighbor);
	                                                neighborIsBetter = true;
	                                                //if neighbor is closer to start it could also be better
	                                        } else if(neighborDistanceFromStart < current.getDistanceFromStart()) {
	                                                neighborIsBetter = true;
	                                        } else {
	                                                neighborIsBetter = false;
	                                        }
	                                        // set neighbors parameters if it is better
	                                        if (neighborIsBetter) {
	                                                neighbor.setPreviousNode(current);
	                                                neighbor.setDistanceFromStart(neighborDistanceFromStart);
	                                                neighbor.setHeuristicDistanceFromGoal(heuristic.getEstimatedDistanceToGoal(neighbor.getX(), neighbor.getY(), map.getGoalLocationX(), map.getGoalLocationY()));
	                                        }
	                                }

	                        }

	                }
	                return null;
*/
}

AStar::~AStar() {
	// TODO Auto-generated destructor stub
}


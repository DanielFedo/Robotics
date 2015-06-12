/*
 * Point.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Point.h"
#include <iostream>
#include <cstdlib>


Point::Point(int x, int y, Point *parent) {
	this->x = x;
	this->y = y;
	this->parent = parent;
}

int Point::getFScore()
{
	return this->fScore;
}

int Point::getGScore()
{
	return this->gScore;
}

int Point::getGScore(Point *parent)
{
	return parent->gScore + 1;
}

int Point::getHScore()
{
	return this->hScore;
}

int Point::getHScore(Point *end)
{
	return (abs(end->x - x) +  abs(end->y - y ));
}

void Point::calculateScores(Point *end)
{
	if (parent != NULL)
		this->gScore = getGScore(parent);
	else
		this->gScore = 0;
	this->hScore = getHScore(end);
	this->fScore = this->gScore + this->hScore;
}

void Point::setParent(Point *parent)
{
	this->parent = parent;
}

bool Point::isEqual(Point *point)
{
	if ((this->x == point->x) && (this->y == point->y))
		return true;
	else
		return false;
}

/*
 * Point.cpp
 *
 *  Created on: May 29, 2015
 *      Author: colman
 */

#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

Point::~Point() {
	// TODO Auto-generated destructor stub
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
	this->gScore = getGScore(parent);
	this->hScore = getHScore(end);
	this->fScore = this->gScore + this->hScore;
}

void Point::setParent(Point *parent)
{
	this->parent = parent;
}


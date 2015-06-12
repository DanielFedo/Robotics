/*
 * Point.h
 *
 *  Created on: May 29, 2015
 *      Author: colman
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	int x;
	int y;
	int gScore;
	int hScore;
	int fScore;

	bool isOpen;

	Point *parent;

	Point(int x, int y, Point *parent);
	virtual ~Point();

	int getGScore();
	int getGScore(Point *parent);
	int getHScore();
	int getHScore(Point *end);
	int getFScore();
	void calculateScores(Point *end);
	void setParent(Point *parent);
	bool isEqual(Point *point);

};

#endif /* POINT_H_ */

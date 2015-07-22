/*
 * Utils.h
 *
 *  Created on: Jun 30, 2015
 *      Author: colman
 */

#ifndef UTILS_H_
#define UTILS_H_

#define PI 3.1415926536

#include "ConfigurationManager.h"
#include <cmath>

class Utils {
public:
 	Utils();
	static ConfigurationManager* configurationManager;

 	static const float DEGREES_INDEX_RATIO = 666 / 270;
 	static const float MIDDLE_INDEX = 666 / 2;

	static const float UNSAFE_DIST = 0.8;
	
	static int IndexToDegrees(int index);
	static int DegreesToIndex(int degrees);
	
	static double IndexToRadians(int index);
	static int RadiansToIndex(double radians);

	static double PixelToMeter(double inPixel);
	static double MeterToPixel(double inMeter);

	static double DegreeToRadian(double degree);
	static double RadianToDegree(double radian);

	// Particles
 	static const int PARTICLES_NUMBER = 150;
	static const double MIN_BELIEF_THRESHOLD = 0.2;
	static const double GOOD_BELIEF_THRESHOLD = 0.7;
};

#endif /* UTILS_H_ */

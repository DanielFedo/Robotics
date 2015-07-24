/*
 * Utils.cpp
 *
 *  Created on: Jun 30, 2015
 *      Author: colman
 */

#include "Utils.h"

ConfigurationManager* Utils::configurationManager = new ConfigurationManager("parameters.txt");

int Utils::DegreesToIndex(int degrees)
{
	int index = degrees * Utils::DEGREES_INDEX_RATIO;
	return Utils::MIDDLE_INDEX + index;
}

int Utils::IndexToDegrees(int index)
{
	int realIndex = index - Utils::MIDDLE_INDEX;
	return realIndex / Utils::DEGREES_INDEX_RATIO;
}

double Utils::IndexToRadians(int index)
{
	int degrees = IndexToDegrees(index);
	return degrees * PI / 180;
}

int Utils::RadiansToIndex(double radians)
{
	int degrees = radians * 180 / PI;
	return DegreesToIndex(degrees);
}

double Utils::DegreeToRadian(double degree){
	 return ((degree) * (M_PI / 180.0));
}

double Utils::RadianToDegree(double radian){
	 return ((radian) * (180.0 / M_PI));
}

double Utils::PixelToMeter(double inPixel)
{
	return inPixel * Utils::configurationManager->mapResolution / 100;
}
double Utils::MeterToPixel(double inMeter)
{
	return inMeter * 100 / Utils::configurationManager->mapResolution;
}

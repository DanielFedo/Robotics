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

float Utils::RobotToPixelX(float Xdelta, float resolution, float mapWidth)
    {
        double halfSize = (mapWidth / 2) * resolution;

        if (Xdelta > 0)
        {
            Xdelta += halfSize;
        }
        else
        {
            Xdelta *= -1;
            Xdelta = halfSize - Xdelta;
        }

        return Xdelta / resolution;
}

float Utils::RobotToPixelY(float Ydelta, float resolution, float mapHeight)
    {
        float halfSize = (mapHeight / 2) * resolution;

        if (Ydelta < 0)
        {
            Ydelta *= -1;
            Ydelta += halfSize;
        }
        else
        {
            Ydelta = halfSize - Ydelta;
        }

        return Ydelta / resolution;
}

float Utils::PixelToRobotX(float Xdelta, float resolution, float mapWidth)
    {
        float halfSize = mapWidth / 2;

        if (Xdelta > halfSize)
        {
            Xdelta -= halfSize;
        }
        else
        {
            Xdelta = halfSize - Xdelta;
            Xdelta *= -1;
        }

        return Xdelta * resolution;
}

float Utils::PixelToRobotY(float Ydelta, float resolution, float mapHeight)
    {
        float halfSize = mapHeight / 2;

        if (Ydelta > halfSize)
        {
            Ydelta -= halfSize;
            Ydelta *= -1;
        }
        else
        {
            Ydelta = halfSize - Ydelta;
        }

        return Ydelta * resolution;
}

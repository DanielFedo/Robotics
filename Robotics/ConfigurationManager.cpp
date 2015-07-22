/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"


ConfigurationManager::ConfigurationManager(const char* configurationFilePath) {
	char attribute_name[200];
	char fileData[10][100];
	std::ifstream inputFile;
	inputFile.open(configurationFilePath, std::ifstream::in);

	int counter = 0;

	// Read from file into attribute name and file data
	while(!inputFile.eof())
	{
		inputFile.getline(attribute_name, 100, ' ');
		inputFile.getline(fileData[counter], 100, '\n');

		counter++;
	}

	inputFile.close();

	std::string map = fileData[0];

	// If map contains data
	if (map[map.size() - 1] == '\r' && !map.empty())
	{
		map.erase(map.size() - 1);
	}

	// Map file path
	this->mapPath = new char[1024];
	strcpy(this->mapPath, map.c_str());

	// x Start location
	std::string startLocation = fileData[1];
	this->xStart = atoi(startLocation.substr(0, startLocation.find_first_of(' ')).c_str());

	// y start location
	startLocation = startLocation.substr(0, startLocation.find_first_of(' ')).c_str();
	this->yStart = atoi(startLocation.c_str());

	// X end location
	std::string goal = fileData[2];
	this->xTarget = atoi(goal.substr(0, goal.find_first_of(' ')).c_str())

	// Y end location
	goal = goal.substr(goal.find_first_of(' ')).c_str();
	this->yTarget = atoi(goal.c_str());

	// Robot size
	std::string robotSize = fileData[3];
	this->robotLength = fileData[3];

	// Robot with
	robotSize = robotSize.substr(robotSize.find_first_of(' ') + 1);
	this->robotWidth = atoi(robotSize.c_str());

	// Map resolution
	std::string mapResolutionCM = fileData[4];
	this->mapResolution = atof(mapResolutionCM.c_str());

	// Fix according to resolution
	this->robotLength = this->robotLength / this->mapResolution;
	this->robotWidth = this->robotWidth / this->mapResolution;
}

ConfigurationManager::~ConfigurationManager() {
	// TODO Auto-generated destructor stub
}


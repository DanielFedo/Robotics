/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <stdlib.h>
#include <string.h>

class ConfigurationManager {
public:
	ConfigurationManager(const char* configurationFilePath);
	virtual ~ConfigurationManager();

	double mapResolution;
	double gridResolution;
	char* mapPath;
	int xStart;
	int yStart;
	int yawStart;
	int xTarget;
	int yTarget;
	int robotLength;
	int robotWidth;

	// not sure about that one..
	double cmInCell();

};

#endif /* CONFIGURATIONMANAGER_H_ */

#include "stdafx.h"
#include "common.h"
#include "Descriptors.h"
#include <opencv2/core/utils/logger.hpp>
#include "Classifier.h"
#include "Descriptors.h"
#include <filesystem>
#include "test.h"


int main() 
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);

	setDistanceFunc(euclidianDistance);
	setSaturationThreshold(170);
	setBins(60);
	setFunc(hueDescriptor);
	setSampleSize(17);

	//train("images/train/cola", TRAINED_FILE, 30, 199, COLA, false);
	//train("images/train/pepsi", TRAINED_FILE, 30, 199, PEPSI, true);

	//testBatch(TRAINED_FILE, "images/test/cola", 0, 29, COLA);
	//testBatch(TRAINED_FILE, "images/test/pepsi", 0, 29, PEPSI);

	classifyDemo(TRAINED_FILE);

	//plotPoints();

	//changeSampleSize();

	//changeSaturation();

	//changeBins();

	//findBest();

	return 0;
}